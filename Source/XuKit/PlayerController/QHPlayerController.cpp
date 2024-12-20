// Fill out your copyright notice in the Description page of Project Settings.


#include "QHPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "XuCheatManager.h"
#include "Framework/Application/NavigationConfig.h"
#include "Net/UnrealNetwork.h"
#include "XuKit/XuBPFuncLib.h"
#include "XuKit/ActorComponent/CombatComponent.h"
#include "XuKit/ActorComponent/DamageTextWidgetComponent.h"
#include "XuKit/Character/PlayerCharacter.h"
#include "XuKit/Event/EventDataDefine.h"
#include "XuKit/Event/EventMgr.h"
#include "XuKit/Input/QHEnhancedInputComponent.h"
#include "XuKit/PlayerState/QHPlayerState.h"
#include "XuKit/UI/UIMgr.h"
#include "XuKit/UI/IUIBase/UIGameLose.h"
#include "XuKit/UI/IUIBase/UIGameMenu.h"
#include "XuKit/UI/IUIBase/UIGameOverridePanel.h"
#include "XuKit/UI/IUIBase/UIGameSettingScreen.h"
#include "XuKit/UI/IUIBase/UIGameWin.h"

AQHPlayerController::AQHPlayerController()
{
	CheatClass = UXuCheatManager::StaticClass();
}

void AQHPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	FInputModeGameAndUI input_mode_game_and_ui;
	input_mode_game_and_ui.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	input_mode_game_and_ui.SetHideCursorDuringCapture(false);
	SetInputMode(input_mode_game_and_ui);

	TSharedRef<FNavigationConfig> navigation = MakeShared<FNavigationConfig>();
	navigation->bTabNavigation=false;
	FSlateApplication::Get().SetNavigationConfig(navigation);
}



void AQHPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputLocalPlayerSubsystem* input_local_player_subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	input_local_player_subsystem->AddMappingContext(inputMap, 0);
	UQHEnhancedInputComponent* input_component = CastChecked<UQHEnhancedInputComponent>(InputComponent);
	input_component->BindAction(input_action_move, ETriggerEvent::Triggered, this, &AQHPlayerController::OnMove);
	input_component->BindAction(ic_ESC, ETriggerEvent::Completed, this, &AQHPlayerController::OnESC);
	input_component->BindAction(ic_Tab, ETriggerEvent::Completed, this, &AQHPlayerController::OnTab);
	//input_component->BindActions(inputConfigDataAsset, this, &AQHPlayerController::OnAbliityInputTagPressed, &AQHPlayerController::OnAbliityInputTagHeld, &AQHPlayerController::OnAbliityInputTagReleased);
}

void AQHPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AQHPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	TraceMouseCuror();
}

void AQHPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AQHPlayerController, CurorHitResult);
}

void AQHPlayerController::OnMove(const FInputActionValue& input_action_value)
{
	const FVector2D moveValue = input_action_value.Get<FVector2D>();

	FRotator ratation = GetControlRotation();
	FRotator YawRatation = FRotator(0, ratation.Yaw, 0);

	FVector forwardDir = FRotationMatrix(YawRatation).GetUnitAxis(EAxis::X);
	FVector rightDir = FRotationMatrix(YawRatation).GetUnitAxis(EAxis::Y);

	if (APawn* pawn = GetPawn())
	{
		pawn->AddMovementInput(forwardDir, moveValue.X);
		pawn->AddMovementInput(rightDir, moveValue.Y);
	}
	
}

void AQHPlayerController::OnAbliityInputTagPressed(FGameplayTag inputActionTag)
{
	if (GetABS())
	{
		GetABS()->AbilityInputTagPressed(inputActionTag);
	}
}

void AQHPlayerController::OnAbliityInputTagHeld(FGameplayTag inputActionTag)
{
	if (GetABS())
	{
		GetABS()->AbilityInputTagHeld(inputActionTag);
	}
}

void AQHPlayerController::OnAbliityInputTagReleased(FGameplayTag inputActionTag)
{
	if (GetABS())
	{
		GetABS()->AbilityInputTagReleased(inputActionTag);
	}
}

UQHAbilitySystemComponent* AQHPlayerController::GetABS()
{
	if (abilitySystemComponent == nullptr)
	{
		abilitySystemComponent = Cast<UQHAbilitySystemComponent>(GetPlayerState<AQHPlayerState>()->GetAbilitySystemComponent());
	}
	return abilitySystemComponent;
}

void AQHPlayerController::OnRep_CurorHitResult(FHitResult oldCurorHitResult)
{
}

void AQHPlayerController::ServerSetCurorHitResult_Implementation(FHitResult hitResult)
{
	CurorHitResult = hitResult;
}

void AQHPlayerController::TraceMouseCuror()
{
	FHitResult local_CurorHitResult;
	GetHitResultUnderCursor(ECC_Visibility, true, local_CurorHitResult);
	ServerSetCurorHitResult(local_CurorHitResult);
}


void AQHPlayerController::GameLose_Implementation()
{
	UXuBPFuncLib::GetUIManager(this)->ShowUI<UUIGameLose>();
}

void AQHPlayerController::GameWin_Implementation()
{
	UXuBPFuncLib::GetUIManager(this)->ShowUI<UUIGameWin>();
}


void AQHPlayerController::ShowDamageText_Implementation(float damage, ACharacter* targetCharacter, bool bIsCriticalHit, bool bIsBlockedHit)
{
	if (DamageTextWidgetComponentClass && targetCharacter)
	{
		UDamageTextWidgetComponent* damageTextWidgetComponent = NewObject<UDamageTextWidgetComponent>(targetCharacter, DamageTextWidgetComponentClass);
		damageTextWidgetComponent->RegisterComponent();
		damageTextWidgetComponent->AttachToComponent(targetCharacter->GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
		damageTextWidgetComponent->SetRelativeLocation(FVector::Zero());
		damageTextWidgetComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		damageTextWidgetComponent->SetDamageText(damage, bIsCriticalHit, bIsBlockedHit);
	}
}

void AQHPlayerController::OnESC()
{
	if (UXuBPFuncLib::GetUIManager(this)->GetUI<UUIGameMenu>())
	{
		UXuBPFuncLib::GetUIManager(this)->HideUI<UUIGameMenu>();
	}
	else
	{
		UXuBPFuncLib::GetUIManager(this)->ShowUI<UUIGameMenu>();
	}
}

void AQHPlayerController::OnTab()
{
	if (UXuBPFuncLib::GetUIManager(this)->GetUI<UUIGameOverridePanel>())
	{
		UXuBPFuncLib::GetUIManager(this)->HideUI<UUIGameOverridePanel>();
	}
	else
	{
		UXuBPFuncLib::GetUIManager(this)->ShowUI<UUIGameOverridePanel>();
	}
}
