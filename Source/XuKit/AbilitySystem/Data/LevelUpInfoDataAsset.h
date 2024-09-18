// copyright xuzhipeng

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LevelUpInfoDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FAuraLevelUpInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	int RequiredExp;

	UPROPERTY(EditDefaultsOnly)
	int AttributePointAward = 1;

	UPROPERTY(EditDefaultsOnly)
	int SpellPointAward = 1;
};

/**
 * 
 */
UCLASS()
class  ULevelUpInfoDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TArray<FAuraLevelUpInfo> LevelUpInfos;

	UFUNCTION(BlueprintCallable)
	int FindLevelByXP(int32 xp);
};


