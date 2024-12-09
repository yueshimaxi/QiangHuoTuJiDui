#include "WeaponConfigDatabase.h"

#include "JsonObjectConverter.h"
#include "XuKit/AbilitySystem/Data/WeaponInfoDataAsset.h"

DataBaseType UWeaponConfigDatabase::DataBaseType()
{
	return DataBaseType::WeaponConfigData;
}

FString UWeaponConfigDatabase::DataPath()
{
	return FPaths::Combine(FPaths::ProjectContentDir(), FString("XuAsset/DataAsset/AppConfig.json"));

}

void UWeaponConfigDatabase::OnParse()
{
	Super::OnParse();

	weaponInfoDataAsset=LoadObject<UWeaponInfoDataAsset>(nullptr, TEXT("/Script/XuKit.WeaponInfoDataAsset'/Game/XuAsset/BP/Data/DA_WeaponInfo.DA_WeaponInfo'"));
	
}


void UWeaponConfigDatabase::OnSave()
{
	Super::OnSave();

	
}

void UWeaponConfigDatabase::ClearData()
{
	Super::ClearData();
}

FWeaponInfo UWeaponConfigDatabase::GetWeaponInfo(FGameplayTag weaponTag)
{
	return weaponInfoDataAsset->GetWeaponInfo(weaponTag);
}
