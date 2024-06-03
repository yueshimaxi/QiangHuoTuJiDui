// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "InputConfigDataAsset.generated.h"

class UInputAction;

USTRUCT(BlueprintType)
struct FQHInputAction
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	FGameplayTag ActionTag;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> InputAction;
};
/**
 * 
 */
UCLASS()
class XUKIT_API UInputConfigDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TArray<FQHInputAction> InputActions;

	UInputAction* FindQHInputActionByTag(FGameplayTag ActionTag, bool bLogError = true);
};
