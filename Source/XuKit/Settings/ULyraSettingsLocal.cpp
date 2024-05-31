#include "ULyraSettingsLocal.h"

ULyraSettingsLocal::ULyraSettingsLocal()
{
	
}

ULyraSettingsLocal* ULyraSettingsLocal::Get()
{
	return GEngine ? CastChecked<ULyraSettingsLocal>(GEngine->GetGameUserSettings()) : nullptr;
}

float ULyraSettingsLocal::GetOverallVolume() const
{
	return OverallVolume;
}

void ULyraSettingsLocal::SetOverallVolume(float InVolume)
{
	// Cache the incoming volume value
	OverallVolume = InVolume;

}

