#include "LyraGameSettingRegistry.h"
#include "GameSettingCollection.h"
#include "GameSettingValueScalarDynamic.h"
#include "ULyraSettingsLocal.h"
#include "DataSource/GameSettingDataSourceDynamic.h"
#include "EditCondition/WhenPlayingAsPrimaryPlayer.h"

ULyraGameSettingRegistry::ULyraGameSettingRegistry()
{
}

ULyraGameSettingRegistry* ULyraGameSettingRegistry::Get(ULyraLocalPlayer* InLocalPlayer)
{
	ULyraGameSettingRegistry* registry = FindObject<ULyraGameSettingRegistry>(InLocalPlayer,TEXT("LyraGameSettingRegistry"), true);
	if (registry==nullptr)
	{
		registry=NewObject<ULyraGameSettingRegistry>();
		registry->Initialize(InLocalPlayer);
	}
	return registry;
}

void ULyraGameSettingRegistry::OnInitialize(ULocalPlayer* InLocalPlayer)
{
	ULyraLocalPlayer* LyraLocalPlayer = Cast<ULyraLocalPlayer>(InLocalPlayer);

	Video_collection = InitializeVideoSettings(LyraLocalPlayer);
	RegisterSetting(Video_collection);
	
	audio_collection = InitializeAudioSettings(LyraLocalPlayer);
	RegisterSetting(audio_collection);
}

void ULyraGameSettingRegistry::SaveChanges()
{
	Super::SaveChanges();
	if (ULyraLocalPlayer* LocalPlayer = Cast<ULyraLocalPlayer>(OwningLocalPlayer))
	{
		// Game user settings need to be applied to handle things like resolution, this saves indirectly
		LocalPlayer->GetLocalSettings()->ApplySettings(false);
		
		// LocalPlayer->GetSharedSettings()->ApplySettings();
		// LocalPlayer->GetSharedSettings()->SaveSettings();
	}
}




