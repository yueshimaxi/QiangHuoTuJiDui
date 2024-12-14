// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "ANPC.h"
#include "EnhancedInputSubsystems.h"
#include "NiagaraComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"
#include "XuKit/QiangHuoTuJiDui.h"
#include "XuKit/XuBPFuncLib.h"
#include "XuKit/AbilitySystem/QHAttributeSet.h"
#include "XuKit/AbilitySystem/QHGameplayTags.h"
#include "XuKit/AbilitySystem/Data/LevelUpInfoDataAsset.h"
#include "..\Actor\AmmoBag\AmmoBag.h"
#include "XuKit/Actor/Weapon/ProjectileWeapon/ProjectionWeapon.h"
#include "XuKit/ActorComponent/CombatComponent.h"
#include "XuKit/Event/EventDataDefine.h"
#include "XuKit/Event/EventMgr.h"
#include "XuKit/HUD/QHHUD.h"
#include "XuKit/Input/QHEnhancedInputComponent.h"
#include "XuKit/Interface/IInteractionIterface.h"
#include "XuKit/PlayerController/QHPlayerController.h"
#include "XuKit/PlayerState/QHPlayerState.h"
#include "XuKit/UI/UIMgr.h"
#include "XuKit/UI/IUIBase/UIInteraction.h"
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


	area_component = CreateDefaultSubobject<USphereComponent>(TEXT("area_component"));
	area_component->SetupAttachment(RootComponent);


	bASCInputBound = false;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	area_component->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnInteractionShpereOverlapBegin);
	area_component->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacter::OnInteractionShpereOverlapEnd);


	decal_ring = GetWorld()->SpawnActor<ADecalActor>(decal_ring_class);
	decal_ring->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void APlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);


	SetPawnRotatorToMouseCursor();
	UpdateInteractionUIMousePosition();
}


void APlayerCharacter::InitAbilityActorInfo()
{
	AQHPlayerState* player_state = GetPlayerState<AQHPlayerState>();
	qh_ability_system_component = player_state->GetAbilitySystemComponent();
	qh_attribute_set = Cast<UQHAttributeSet>(player_state->GetAttributeSet());
	// qh_attribute_set->SetPisalReserveAmmo(90);
	// qh_attribute_set->SetMaxPisalReserveAmmo(90);
	// qh_attribute_set->SetRifleReserveAmmo(360);
	// qh_attribute_set->SetMaxRifleReserveAmmo(360);
	// qh_attribute_set->SetShotgunReserveAmmo(45);
	// qh_attribute_set->SetMaxShotgunReserveAmmo(45);
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
		FGameplayAbilityInputBinds input_binds("ConfirmTarget", "CancelTarget", "EQHAbilityInputID", static_cast<int32>(EQHAbilityInputID::Confirm), static_cast<int32>(EQHAbilityInputID::Cancel));
		qh_ability_system_component->BindAbilityActivationToInputComponent(InputComponent,input_binds);

		bASCInputBound = true;
	}
}

void APlayerCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
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
	if (cur_interaction_actor == nullptr)
	{
		return;
	}

	EInteractionType interactType = IIInteractionIterface::Execute_GetInteractionType(cur_interaction_actor);
	switch (interactType)
	{
	case NPC:
		if (ANPC* npc = Cast<ANPC>(cur_interaction_actor))
		{
			StartDialogue(npc->DialogueAsset);
		}
		break;
	case Weapon:
		if (AWeapon* weapon = Cast<AWeapon>(cur_interaction_actor))
		{
			getCombatCom()->AddWeaponToInventory(weapon, getCombatCom()->Inventory.Weapons.Num() == 0);
		}

		break;
	case Door:
		break;
	case Prop:
		break;
	case Ammo:
		if (AAmmoBag* ammo_bag = Cast<AAmmoBag>(cur_interaction_actor))
		{
			ammo_bag->ReplenishAmmo(this);
		}
		break;
	default: ;
	}
}

void APlayerCharacter::DropWeapon_Implementation()
{
	getCombatCom()->RemoveWeaponFromInventory(Execute_get_cur_projection_weapon(this));
}

void APlayerCharacter::EquipWeapon_Implementation(AWeapon* weapon)
{
	getCombatCom()->Server_EquipWeapon(weapon);
}

void APlayerCharacter::Dash_Implementation()
{
	FVector DashDirection = GetLastMovementInputVector().GetSafeNormal();
	if (DashDirection.IsNearlyZero())
	{
		return;
	}

	LaunchCharacter(DashDirection * DashStrength, false, false);
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

void APlayerCharacter::OnInteractionShpereOverlapBegin(UPrimitiveComponent* overlapped_component, AActor* other_actor, UPrimitiveComponent* other_comp, int32 other_body_index, bool b_from_sweep, const FHitResult& sweep_result)
{
	if (IIInteractionIterface* interaction_interface = Cast<IIInteractionIterface>(other_actor))
	{
		cur_interaction_interface_actor_array.Add(other_actor);
	}
}

void APlayerCharacter::OnInteractionShpereOverlapEnd(UPrimitiveComponent* overlapped_component, AActor* other_actor, UPrimitiveComponent* other_comp, int32 other_body_index)
{
	if (IIInteractionIterface* interaction_interface = Cast<IIInteractionIterface>(other_actor))
	{
		cur_interaction_interface_actor_array.Remove(other_actor);
	}
}

void APlayerCharacter::UpdateInteractionUIMousePosition()
{
	if (cur_interaction_interface_actor_array.Num() <= 0)
	{
		cur_interaction_actor = nullptr;
		if (cur_uui_interaction)
		{
			//cur_uui_interaction->PlayShowAnim(false);
			UXuBPFuncLib::GetUIManager(this)->HideUI<UUIInteraction>();
			cur_uui_interaction = nullptr;
		}
		last_interaction_actor = nullptr;
		return;
	}
	APlayerController* player_controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	FHitResult hit_result;
	player_controller->GetHitResultUnderCursor(ECC_Visibility, false, hit_result);
	AActor* curorActor = hit_result.GetActor();

	//如果Interaction_array中有对象在鼠标下，那么优先交互这个对象，否则交互第一个Inter

	for (auto element : cur_interaction_interface_actor_array)
	{
		if (element == curorActor)
		{
			cur_interaction_actor = element;
			break;
		}
	}
	if (cur_interaction_actor == nullptr || !cur_interaction_interface_actor_array.Contains(cur_interaction_actor))
	{
		cur_interaction_actor = cur_interaction_interface_actor_array[0];
	}

	if (!cur_uui_interaction)
	{
		cur_uui_interaction = UXuBPFuncLib::GetUIManager(this)->ShowUI<UUIInteraction>();
	}

	FVector location = cur_interaction_actor->GetActorLocation();
	FVector2D mouse_location;
	//cur_interaction_actor空间坐标转换屏幕坐标
	if (player_controller->ProjectWorldLocationToScreen(location, mouse_location))
	{
		cur_uui_interaction->UpdateMousePosition(mouse_location);

		if (last_interaction_actor != cur_interaction_actor)
		{
			cur_uui_interaction->PlayShowAnim(true);
		}
	}
	else
	{
		cur_uui_interaction->PlayShowAnim(false);
	}


	last_interaction_actor = cur_interaction_actor;
}

void APlayerCharacter::StartDialogue_Implementation(UDlgDialogue* dialogueAsset)
{
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
