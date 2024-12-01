// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IInteractionIterface.generated.h"

UENUM(Blueprintable,BlueprintType)
enum EInteractionType :uint8
{
	NPC,
	Weapon,
	Door,
	Prop,//道具
};
// This class does not need to be modified.
UINTERFACE()
class UIInteractionIterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class XUKIT_API IIInteractionIterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	EInteractionType GetInteractionType();
};
