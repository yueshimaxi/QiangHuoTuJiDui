#include "UIPlayerHUD.h"

#include "Kismet/GameplayStatics.h"
#include "XuKit/XuBPFuncLib.h"
#include "XuKit/AbilitySystem/Data/WeaponInfoDataAsset.h"
#include "XuKit/Actor/Weapon/ProjectileWeapon/ProjectionWeapon.h"
#include "XuKit/Interface/CombatInterface.h"
#include "XuKit/Interface/PlayerInterface.h"
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
	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (playerController)
	{
		if (ICombatInterface* icombatInterface = Cast<ICombatInterface>(playerController->GetPawn()))
		{
			AQHPlayerState *playerState = playerController->GetPlayerState<AQHPlayerState>();
			AProjectionWeapon* weapon = icombatInterface->Execute_get_cur_projection_weapon(playerController->GetPawn());
			int allBackpackAmmo = playerState->GetAmmoNum(weapon->weapon_info.Ammo_type);
			SetHUDAmmo(weapon->Ammo, allBackpackAmmo, weapon->weapon_info);
		}
	}

	XuPRINT("UUIPlayerHUD::NativeConstruct");
}

void UUIPlayerHUD::SetHUDAmmo(int ClipAmmoNum, int AllAmmoNum,FWeaponInfo local_weapon_info)
{
	XuPRINT("UUIPlayerHUD::SetHUDAmmo");
	ClipAmmoNum_Text->SetText(FText::FromString(FString::FromInt(ClipAmmoNum)));
	AllAmmoNum_Text->SetText(FText::FromString(FString::FromInt(AllAmmoNum)));
	WeaponIcon_Image->SetBrushFromTexture(local_weapon_info.weapon_icon);
}

