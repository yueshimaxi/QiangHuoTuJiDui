#pragma once
#include "CoreMinimal.h"
#include "GameSettingRegistry.h"
#include "XuKit/Player/LyraLocalPlayer.h"
#include "LyraGameSettingRegistry.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogLyraGameSettingRegistry, Log, Log);

#define GET_SHARED_SETTINGS_FUNCTION_PATH(FunctionOrPropertyName)							\
MakeShared<FGameSettingDataSourceDynamic>(TArray<FString>({								\
GET_FUNCTION_NAME_STRING_CHECKED(ULyraLocalPlayer, GetSharedSettings),				\
GET_FUNCTION_NAME_STRING_CHECKED(ULyraSettingsShared, FunctionOrPropertyName)		\
}))

#define GET_LOCAL_SETTINGS_FUNCTION_PATH(FunctionOrPropertyName)	 						\
MakeShared<FGameSettingDataSourceDynamic>(TArray<FString>({								\
GET_FUNCTION_NAME_STRING_CHECKED(ULyraLocalPlayer, GetLocalSettings),				\
GET_FUNCTION_NAME_STRING_CHECKED(ULyraSettingsLocal, FunctionOrPropertyName)		\
}))


UCLASS()
class XUKIT_API ULyraGameSettingRegistry : public UGameSettingRegistry
{
	GENERATED_BODY()

public:
	ULyraGameSettingRegistry();

	static ULyraGameSettingRegistry* Get(ULyraLocalPlayer* InLocalPlayer);
	
	virtual void OnInitialize(ULocalPlayer* InLocalPlayer) override;


	virtual void SaveChanges() override;
	
	UPROPERTY()
	UGameSettingCollection* Video_collection;
	UPROPERTY()
	UGameSettingCollection* audio_collection;

	UGameSettingCollection* InitializeVideoSettings(ULocalPlayer* InLocalPlayer);

	UGameSettingCollection* InitializeAudioSettings(ULocalPlayer* InLocalPlayer);
};
