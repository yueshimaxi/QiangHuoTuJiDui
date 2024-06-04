// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "QHAbilityBPLibrary.generated.h"

/**
 * 
 */
UCLASS()
class XUKIT_API UQHAbilityBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category="AuraAbilityLibrary", meta=(WorldContext="WorldContextObject"))
	static bool IsNotFriendly(AActor* ActorA, AActor* ActorB);
};
