#pragma once
#include "CoreMinimal.h"
#include "XuKit/Settings/ULyraSettingsLocal.h"
#include "LyraLocalPlayer.generated.h"

UCLASS()
class XUKIT_API ULyraLocalPlayer:public  ULocalPlayer
{
	GENERATED_BODY()

public:
	ULyraLocalPlayer();

	UFUNCTION()	
	ULyraSettingsLocal* GetLocalSettings() const;
};
