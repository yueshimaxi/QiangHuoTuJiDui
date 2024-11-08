// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "EnhancedInputSubsystems.h"
#include "NiagaraComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"
#include "XuKit/QiangHuoTuJiDui.h"
#include "XuKit/XuBPFuncLib.h"
#include "XuKit/AbilitySystem/QHAttributeSet.h"
#include "XuKit/AbilitySystem/QHGameplayTags.h"
#include "XuKit/AbilitySystem/Data/LevelUpInfoDataAsset.h"
#include "XuKit/Actor/Weapon/ProjectileWeapon/ProjectionWeapon.h"
#include "XuKit/ActorComponent/CombatComponent.h"
#include "XuKit/Event/EventDataDefine.h"
#include "XuKit/Event/EventMgr.h"
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

	level_up_niagara_component = CreateDefaultSubobject<UNiagaraComponent>(TEXT("level_up_niagara_component"));
	level_up_niagara_component->SetupAttachment(RootComponent);
	level_up_niagara_component->bAutoActivate = false;

	bASCInputBound = false;
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
	Cast<UQHAbilitySystemComponent>(qh_ability_system_component)->AbilitySystemComponentInfoSet();
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	ENetRole role = GetLocalRole();
	XuPRINT(FString::Printf(TEXT("role:%d"), role));
	InitAbilityActorInfo();
	AddCharactorAbilities();
	InitDefaultAttributesToSelf();
	InitDefaultProjectionWeapon();
	if (IsLocallyControlled())
	{
		FreshHUD();
	}
}

void APlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	InitAbilityActorInfo();
	if (IsLocallyControlled())
	{
		AQHPlayerController* qhPC = Cast<AQHPlayerController>(GetController());
		AQHPlayerState* qhPS = qhPC->GetPlayerState<AQHPlayerState>();
		AQHPlayerState* sencondPS = GetPlayerState<AQHPlayerState>();
		if (qhPS == sencondPS)
		{
			XuPRINT(TEXT("zzzz"));
		}
		FreshHUD();
	}
}

AProjectionWeapon* APlayerCharacter::get_cur_projection_weapon_Implementation()
{
	return Cast<AProjectionWeapon>(combat_component->GetCurProjectionWeapon());
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


	BindASCInput();
}

void APlayerCharacter::BindASCInput()
{
	if (!bASCInputBound && IsValid(qh_ability_system_component) && IsValid(InputComponent))
	{
		qh_ability_system_component->BindAbilityActivationToInputComponent(InputComponent, FGameplayAbilityInputBinds(FString("ConfirmTarget"),
		                                                                                                              FString("CancelTarget"),
		                                                                                                              FTopLevelAssetPath(GetPathNameSafe(UClass::TryFindTypeSlow<UEnum>("EQHAbilityInputID"))),
		                                                                                                              static_cast<int32>(EQHAbilityInputID::Confirm), static_cast<int32>(EQHAbilityInputID::Cancel)));

		bASCInputBound = true;
	}
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


void APlayerCharacter::SwapWeapon_Implementation(bool swapWeaponForward)
{
	getCombatCom()->SwapWeapon(swapWeaponForward);
}

void APlayerCharacter::AddXP_Implementation(int xp)
{
	AQHPlayerState* player_state = GetPlayerState<AQHPlayerState>();
	player_state->AddToXP(xp);
}

int APlayerCharacter::GetXP_Implementation()
{
	AQHPlayerState* player_state = GetPlayerState<AQHPlayerState>();
	return player_state->GetXP();
}

void APlayerCharacter::LevelUp_Implementation()
{
	MulticastLevelUpNiagara();
}

int APlayerCharacter::FindLevelForXP_Implementation(int XP)
{
	AQHPlayerState* player_state = GetPlayerState<AQHPlayerState>();
	int level = player_state->LevelUpInfoDataAsset->FindLevelByXP(XP);

	return level;
}

int APlayerCharacter::GetPlayerLevel_Implementation()
{
	AQHPlayerState* player_state = GetPlayerState<AQHPlayerState>();
	return player_state->GetPlayerLevel();
}

void APlayerCharacter::AddToLevel_Implementation(int AddLevel)
{
	AQHPlayerState* player_state = GetPlayerState<AQHPlayerState>();
	return player_state->AddPlayerLevel(AddLevel);
}

void APlayerCharacter::Interact_Implementation()
{
	if (overlaping_weapon)
	{
		getCombatCom()->AddWeaponToInventory(overlaping_weapon, getCombatCom()->Inventory.Weapons.Num() == 0);
	}
}

void APlayerCharacter::DropWeapon_Implementation()
{
	getCombatCom()->RemoveWeaponFromInventory(get_cur_projection_weapon());
}

void APlayerCharacter::InitDefaultProjectionWeapon()
{
	AProjectionWeapon* projection_weapon = GetWorld()->SpawnActor<AProjectionWeapon>(default_projection_weapon_class);
	projection_weapon->InitData();
	getCombatCom()->AddWeaponToInventory(projection_weapon, true);
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


void APlayerCharacter::Set_Overlap_Weapon(AWeapon* weapon)
{
	overlaping_weapon = weapon;
}


void APlayerCharacter::InitDefaultAttributesToSelf()
{
	ApplyEffectToSelf(DefaultPrimaryAttributeEffect);
}

void APlayerCharacter::AddCharactorAbilities()
{
	UQHAbilitySystemComponent* ABS = Cast<UQHAbilitySystemComponent>(qh_ability_system_component);
	if (!HasAuthority())return;
	ABS->AddCharactorAbilities(DefaultAbilities);
	ABS->AddCharactorPassiveAbilities(StartUpPassiveAbilities);
}

void APlayerCharacter::FreshHUD()
{
	UFreshHUDEventData* fresh_hud_event = NewObject<UFreshHUDEventData>();
	UXuBPFuncLib::GetEventManager(GetWorld())->BroadcastEvent(EXuEventType::FreshHUD, fresh_hud_event);
}


UCombatComponent* APlayerCharacter::getCombatCom()
{
	return combat_component;
}


void APlayerCharacter::MulticastLevelUpNiagara_Implementation()
{
	FVector camera_location = camera_component->GetComponentLocation();
	FVector levelup_niagara_location = level_up_niagara_component->GetComponentLocation();

	FRotator niagaraRotator = (camera_location - levelup_niagara_location).Rotation();
	level_up_niagara_component->SetWorldRotation(niagaraRotator);

	level_up_niagara_component->Activate(true);
}
