// Fill out your copyright notice in the Description page of Project Settings.


#include "UIGameOverridePanel.h"

#include "Components/Image.h"
#include "XuKit/XuBPFuncLib.h"
#include "XuKit/Actor/Weapon/ProjectileWeapon/ProjectionWeapon.h"
#include "XuKit/ActorComponent/CombatComponent.h"
#include "XuKit/Character/PlayerCharacter.h"
#include "XuKit/UI/UIMgr.h"
#include "XuKit/UI/Base/XuCheckBox.h"

EUILayer UUIGameOverridePanel::GetUILayer() const
{
	return EUILayer::Low;
}

EUIType UUIGameOverridePanel::GetUIType() const
{
	return EUIType::Stack;
}

void UUIGameOverridePanel::OnShowed()
{
	Super::OnShowed();

	InitTopMenu();
	InitWeaponPanel();

	Btn_Exit->OnClicked().AddLambda([&]()
	{
		UXuBPFuncLib::GetUIManager(this)->HideUI<UUIGameOverridePanel>();
	});
}

void UUIGameOverridePanel::InitTopMenu()
{
	TArray<FString> menuStrs = {TEXT("武器"),TEXT("物品"),TEXT("天赋"),TEXT("任务"),TEXT("地图"),TEXT("角色")};
	TileView_TopOverrideMenu->InitScrollView(menuStrs.Num(), FXuOnItemInit::CreateLambda([&, menuStrs](UUserWidget* item, int32 index, bool isSelected)
	{
		UTextBlock* text_Name = Cast<UTextBlock>(item->GetWidgetFromName("text_Name"));
		UWidgetSwitcher* WidgetSwitcher_BG = Cast<UWidgetSwitcher>(item->GetWidgetFromName("WidgetSwitcher_BG"));
		if (text_Name)
		{
			text_Name->SetText(FText::FromString(menuStrs[index]));
		}
		if (isSelected)
		{
			WidgetSwitcher_OverrideMenu->SetActiveWidgetIndex(index);
		}
		WidgetSwitcher_BG->SetActiveWidgetIndex(isSelected ? 1 : 0);
	}));
	TileView_TopOverrideMenu->SetSelectedIndex(0);
}

void UUIGameOverridePanel::InitWeaponPanel()
{
	APlayerCharacter* player_character = Cast<APlayerCharacter>(GetOwningPlayerPawn());
	TArray<AWeapon*> Weapons = player_character->getCombatCom()->Inventory.Weapons;
	int WepaonMaxNum = 4;
	TileView_WeaponList->InitScrollView(WepaonMaxNum, FXuOnItemInit::CreateLambda([&, Weapons,player_character](UUserWidget* item, int32 index, bool isSelected)
	{
		UWidgetSwitcher* WidgetSwitcher_Enable = Cast<UWidgetSwitcher>(item->GetWidgetFromName("WidgetSwitcher_Enable"));
		if (index + 1 > Weapons.Num())
		{
			WidgetSwitcher_Enable->SetActiveWidgetIndex(1);
			item->SetVisibility(ESlateVisibility::HitTestInvisible);
			return;
		}
		
		item->SetVisibility(ESlateVisibility::Visible);
	
		AProjectionWeapon* weapon = Cast<AProjectionWeapon>(Weapons[index]);
		FWeaponInfo weaponInfo = weapon->weapon_info;
		WidgetSwitcher_Enable->SetActiveWidgetIndex(0);
		UXuCheckBox* CheckBox_Weapon = Cast<UXuCheckBox>(item->GetWidgetFromName("XuCheckBox_isEquip"));
		CheckBox_Weapon->SetIsChecked(isSelected);
		UImage* Image_Weaponicon = Cast<UImage>(item->GetWidgetFromName("Image_Weaponicon"));
		Image_Weaponicon->SetBrushFromTexture(weaponInfo.weapon_icon);
		UTextBlock* Text_ReseveAmmo = Cast<UTextBlock>(item->GetWidgetFromName("Text_ReseveAmmo"));
		int num = UQHAttributeSet::GetReserveAmmoAttributeFromTag(weaponInfo.WeaponTag).GetNumericValue(player_character->qh_attribute_set);
		Text_ReseveAmmo->SetText(FText::FromString(FString::FromInt(num)));
		UImage* Image_AmmoType = Cast<UImage>(item->GetWidgetFromName("Image_AmmoType"));
		if (WeaponIconMap.Contains(weaponInfo.WeaponAmmoTag))
		{
			Image_AmmoType->SetBrushFromTexture(WeaponIconMap[weaponInfo.WeaponAmmoTag]);
		}

		if (isSelected)
		{
			text_WeaponName->SetText(FText::FromString(weaponInfo.weapon_name));
			text_WeaponInfo->SetText(FText::FromString(weaponInfo.weapon_description));
			player_character->getCombatCom()->Server_EquipWeapon(weapon);
		}
	}));
}
