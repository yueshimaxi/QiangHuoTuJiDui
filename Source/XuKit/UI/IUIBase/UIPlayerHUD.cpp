#include "UIPlayerHUD.h"

#include "Kismet/GameplayStatics.h"
#include "XuKit/XuBPFuncLib.h"
#include "XuKit/AbilitySystem/QHAttributeSet.h"
#include "XuKit/AbilitySystem/Data/WeaponInfoDataAsset.h"
#include "XuKit/Actor/Weapon/ProjectileWeapon/ProjectionWeapon.h"
#include "XuKit/Event/EventMgr.h"
#include "XuKit/Interface/CombatInterface.h"
#include "XuKit/Interface/PlayerInterface.h"
#include "XuKit/PlayerController/QHPlayerController.h"
#include "XuKit/PlayerState/QHPlayerState.h"


EUILayer UUIPlayerHUD::GetUILayer_Implementation() const
{
	return EUILayer::Bottom;
}

EUIType UUIPlayerHUD::GetUIType_Implementation() const
{
	return EUIType::Normal;
}

void UUIPlayerHUD::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	XuPRINT("UUIPlayerHUD::NativeOnInitialized");
}

void UUIPlayerHUD::NativeConstruct()
{

	Super::NativeConstruct();
	
	fresh_hud_delegate.BindDynamic(this, &UUIPlayerHUD::OnFreshHUDEvent);
	GetWorld()->GetSubsystem<UEventMgr>()->RegistEvent(EXuEventType::FreshHUD, freshhud_EventID, fresh_hud_delegate);
	OnFreshHUDEvent(nullptr);

	XuPRINT("UUIPlayerHUD::NativeConstruct");
}

void UUIPlayerHUD::SetHUDAmmo(int ClipAmmoNum, int AllAmmoNum, FWeaponInfo local_weapon_info)
{
	XuPRINT("UUIPlayerHUD::SetHUDAmmo");
	ClipAmmoNum_Text->SetText(FText::FromString(FString::FromInt(ClipAmmoNum)));
	AllAmmoNum_Text->SetText(FText::FromString(FString::FromInt(AllAmmoNum)));
	WeaponIcon_Image->SetBrushFromTexture(local_weapon_info.weapon_icon);
}

void UUIPlayerHUD::SetHealth(float NewValue)
{
	curHealth = NewValue;
	SetHealthProgress();
}

void UUIPlayerHUD::SetMaxHealth(float NewValue)
{
	curMaxHealth = NewValue;
	SetHealthProgress();
}

void UUIPlayerHUD::SetHealthProgress()
{
	if (curMaxHealth == 0)
	{
		Health_progress_bar->SetPercent(0);
	}
	else
	{
		Health_progress_bar->SetPercent(curHealth / curMaxHealth);
	}
}

void UUIPlayerHUD::testsethealth()
{
	widget_controller_params.qh_AttributeSet->SetHealth(40);
}

void UUIPlayerHUD::OnFreshHUDEvent(UEventData* event_data)
{
	if (!bInit)
	{
		widget_controller_params = UQHAbilityBPLibrary::GetFWidgetControllerParams(GetWorld());

		if (widget_controller_params.qh_PlayerState == nullptr || widget_controller_params.qh_AttributeSet == nullptr || widget_controller_params.qh_PlayerController == nullptr)
		{
			return;
		}
		bInit = true;
		widget_controller_set_delegate.Broadcast();
		XuPRINT(TEXT("widget_controller_set_delegate.Broadcast()"));
	}


	if (ICombatInterface* icombatInterface = Cast<ICombatInterface>(widget_controller_params.qh_PlayerController->GetPawn()))
	{
		AProjectionWeapon* weapon = icombatInterface->Execute_get_cur_projection_weapon(widget_controller_params.qh_PlayerController->GetPawn());
		if (weapon)
		{
			int allBackpackAmmo = widget_controller_params.qh_PlayerState->GetAmmoNum(weapon->weapon_info.Ammo_type);
			SetHUDAmmo(weapon->Ammo, allBackpackAmmo, weapon->weapon_info);
		}
		curMaxHealth = widget_controller_params.qh_AttributeSet->GetMaxHealth();
		curHealth = widget_controller_params.qh_AttributeSet->GetHealth();
		SetHealthProgress();
		testsethealth();
	}
}
