// copyright xuzhipeng

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "Engine/DataAsset.h"
#include "CharactorClassInfo.generated.h"


UENUM(BlueprintType)
enum class ECharactorClass:uint8
{
	Warrior,
	Ranger,
	Elementalist,
};

USTRUCT(BlueprintType)
struct FCharactorInfo
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UGameplayEffect> GE_InitPrimaryAttributeClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	FScalableFloat RewardXP =FScalableFloat();
	
};
/**
 * 
 */
UCLASS(Blueprintable)
class XUKIT_API UCharactorClassInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TMap<ECharactorClass,FCharactorInfo> CharactorClassInfoMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UGameplayEffect> GE_InitSecondAttributeClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UGameplayEffect> GE_InitVitalAttributeClass;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<UGameplayAbility>> CommonAbilities;
	
	FCharactorInfo GetCharactorInfo(ECharactorClass CharactorClass);

	UPROPERTY(EditAnywhere)
	TObjectPtr<UCurveTable> CT_DamageCalcCoefficients;
};
