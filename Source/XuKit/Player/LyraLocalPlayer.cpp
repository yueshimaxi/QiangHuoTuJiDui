#include "LyraLocalPlayer.h"

ULyraLocalPlayer::ULyraLocalPlayer()
{
	
}

ULyraSettingsLocal* ULyraLocalPlayer::GetLocalSettings() const
{
	return ULyraSettingsLocal::Get();

}
