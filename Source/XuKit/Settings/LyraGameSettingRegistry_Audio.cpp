#include "LyraGameSettingRegistry.h"
#include "GameSettingCollection.h"
#include "GameSettingValueScalarDynamic.h"
#include "ULyraSettingsLocal.h"
#include "DataSource/GameSettingDataSourceDynamic.h"
#include "EditCondition/WhenPlayingAsPrimaryPlayer.h"


UGameSettingCollection* ULyraGameSettingRegistry::InitializeAudioSettings(ULocalPlayer* InLocalPlayer)
{
	UGameSettingCollection* screen = NewObject<UGameSettingCollection>();
	screen->SetDevName(TEXT("AudioCollection"));
	screen->SetDisplayName(TEXT("Audio"));
	screen->Initialize(InLocalPlayer);

	{
		UGameSettingCollection* volume = NewObject<UGameSettingCollection>();
		volume->SetDevName(TEXT("VolumeCollection"));
		volume->SetDisplayName(TEXT("Volume"));
		screen->AddSetting(volume);
		{
			UGameSettingValueScalarDynamic* Setting = NewObject<UGameSettingValueScalarDynamic>();
			Setting->SetDevName(TEXT("OverallVolume"));
			Setting->SetDisplayName(TEXT("Overall"));
			Setting->SetDescriptionRichText(TEXT("Adjusts the volume of everything."));

			Setting->SetDynamicGetter(GET_LOCAL_SETTINGS_FUNCTION_PATH(GetOverallVolume));
			Setting->SetDynamicSetter(GET_LOCAL_SETTINGS_FUNCTION_PATH(SetOverallVolume));
			Setting->SetDefaultValue(GetDefault<ULyraSettingsLocal>()->GetOverallVolume());
			Setting->SetDisplayFormat(UGameSettingValueScalarDynamic::ZeroToOnePercent);

			Setting->AddEditCondition(FWhenPlayingAsPrimaryPlayer::Get());

			volume->AddSetting(Setting);
		}
	}
	return screen;
}