// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"
#include "XuKit/AbilitySystem/QHGameplayTags.h"
#include "XuKit/Actor/Weapon/ProjectileWeapon/ProjectionWeapon.h"
#include "XuKit/ActorComponent/CombatComponent.h"
#include "XuKit/HUD/QHHUD.h"
#include "XuKit/Input/QHEnhancedInputComponent.h"
#include "XuKit/PlayerController/QHPlayerController.h"
#include "XuKit/PlayerState/QHPlayerState.h"
#include "XuKit/UI/UIMgr.h"
#include "XuKit/UI/IUIBase/UIPlayerHUD.h"

APlayerCharacter::APlayerCharacter()
{
	bReplicates = true;

	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0, 500, 0);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	//CharactorClass = ECharactorClass::Elementalist;


	spring_arm_component = CreateDefaultSubobject<USpringArmComponent>(TEXT("spring_arm_component"));
	spring_arm_component->SetupAttachment(RootComponent);
	spring_arm_component->bDoCollisionTest = false;
	spring_arm_component->bUsePawnControlRotation = false;
	spring_arm_component->bInheritYaw = false;
	spring_arm_component->bInheritPitch = false;
	spring_arm_component->bInheritRoll = false;

	camera_component = CreateDefaultSubobject<UCameraComponent>(TEXT("camera_component"));
	camera_component->SetupAttachment(spring_arm_component, USpringArmComponent::SocketName);

	combat_component = CreateDefaultSubobject<UCombatComponent>(TEXT("combat_component"));
	combat_component->SetIsReplicated(true);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);


	SetPawnRotatorToMouseCursor();
}


void APlayerCharacter::InitAbilityActorInfo()
{
	AQHPlayerState* player_state = GetPlayerState<AQHPlayerState>();
	qh_ability_system_component = player_state->GetAbilitySystemComponent();
	qh_attribute_set = player_state->GetAttributeSet();
	qh_ability_system_component->InitAbilityActorInfo(player_state, this);

	AddCharactorAbilities();
	InitDefaultAttributesToSelf();
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitAbilityActorInfo();
	InitDefaultProjectionWeapon();
	FreshHUD();
}

AProjectionWeapon* APlayerCharacter::get_cur_projection_weapon_Implementation()
{
	return combat_component->GetCurProjectionWeapon();
}

void APlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	combat_component->owner_character = this;
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UQHEnhancedInputComponent* input_component = CastChecked<UQHEnhancedInputComponent>(InputComponent);

	input_component->BindAction(input_action_equipWeapon, ETriggerEvent::Started, this, &APlayerCharacter::OnEquipWeaponPress);
	input_component->BindAction(input_action_dropWeapon, ETriggerEvent::Started, this, &APlayerCharacter::OnDropWeaponPress);
	input_component->BindAction(input_action_swapWeapon, ETriggerEvent::Started, this, &APlayerCharacter::OnSwapWeaponPress);

	//攻击
	input_component->BindAction(input_action_attack, ETriggerEvent::Triggered, this, &APlayerCharacter::OnAttackHold);

	//换弹
	input_component->BindAction(input_action_reload, ETriggerEvent::Started, this, &APlayerCharacter::OnReloadPress);
}

void APlayerCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlayerCharacter, overlaping_weapon);
}

void APlayerCharacter::ReloadAmmo_Implementation()
{
	if (AProjectionWeapon* projection_weapon = get_cur_projection_weapon_Implementation())
	{
		projection_weapon->ReloadAmmo();
	}
}

void APlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
}

void APlayerCharacter::InitDefaultProjectionWeapon()
{
	AProjectionWeapon* projection_weapon = GetWorld()->SpawnActor<AProjectionWeapon>(default_projection_weapon_class);
	projection_weapon->InitData();
	getCombatCom()->EquipWeapon(projection_weapon);
}

void APlayerCharacter::SetPawnRotatorToMouseCursor()
{
	if (AQHPlayerController* player_controller = Cast<AQHPlayerController>(GetController()))
	{
		FVector hit_location = player_controller->CurorHitResult.ImpactPoint;
		FRotator look_at = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), hit_location);
		FRotator new_rot = FRotator(0, look_at.Yaw, 0);
		SetActorRotation(new_rot);
	}
}


void APlayerCharacter::OnEquipWeaponPress()
{
	if (overlaping_weapon)
	{
		if (AProjectionWeapon* projection_weapon = Cast<AProjectionWeapon>(overlaping_weapon))
		{
			getCombatCom()->EquipWeapon(projection_weapon);
		}
	}
}

void APlayerCharacter::OnDropWeaponPress()
{
	getCombatCom()->DropWeapon();
}

void APlayerCharacter::OnSwapWeaponPress()
{
}

void APlayerCharacter::Set_Overlap_Weapon(AWeapon* weapon)
{
	overlaping_weapon = weapon;
}


void APlayerCharacter::OnAttackHold()
{
	//如果弹夹子弹大于零则激活攻击Ability，否则换弹Ability
	if (AProjectionWeapon* projection_weapon = get_cur_projection_weapon_Implementation())
	{
		UQHAbilitySystemComponent* qh_ABS = Cast<UQHAbilitySystemComponent>(qh_ability_system_component);
		if (projection_weapon->GetCurAmmo() > 0)
		{
			qh_ABS->AbilityInputTagHeld(QHGameplayTags::Get().FireTag);
		}
		else
		{
			qh_ABS->AbilityInputTagHeld(QHGameplayTags::Get().ReloadTag);
		}
	}
}

void APlayerCharacter::OnReloadPress()
{
	UQHAbilitySystemComponent* qh_ABS = Cast<UQHAbilitySystemComponent>(qh_ability_system_component);
	qh_ABS->AbilityInputTagPressed(QHGameplayTags::Get().ReloadTag);
}

void APlayerCharacter::InitDefaultAttributesToSelf()
{
	ApplyEffectToSelf(DefaultPrimaryAttributeEffect);
}

void APlayerCharacter::FreshHUD()
{
	if (AQHPlayerState* playerState = GetPlayerState<AQHPlayerState>())
	{
		if (UUIPlayerHUD* playerHUD = GetWorld()->GetGameInstance()->GetSubsystem<UUIMgr>()->GetUI<UUIPlayerHUD>())
		{
			AProjectionWeapon* weapon = get_cur_projection_weapon();

			int allBackpackAmmo = playerState->GetAmmoNum(weapon->weapon_info.Ammo_type);
			playerHUD->SetHUDAmmo(weapon->Ammo, allBackpackAmmo, weapon->weapon_info);
		}
	}
}


UCombatComponent* APlayerCharacter::getCombatCom()
{
	return combat_component;
}
