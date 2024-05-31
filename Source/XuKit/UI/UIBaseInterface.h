// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UIBaseInterface.generated.h"
UENUM(BlueprintType)
enum class EUILayer :uint8
{
	Low = 0 UMETA(DisplayName="low"),
	Bottom = 10 UMETA(DisplayName="bottom"),
	Middle = 20 UMETA(DisplayName="middle"),
	Tips = 30 UMETA(DisplayName="tips"),
	GM = 40 UMETA(DisplayName="gm"),
};

UENUM(BlueprintType)
enum class EUIType :uint8
{
	Normal = 0 UMETA(DisplayName="Normal"),
	Stack = 10 UMETA(DisplayName="Stack"),
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UUIBaseInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class XUKIT_API IUIBaseInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "UIBase")
	EUILayer GetUILayer() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "UIBase")
	EUIType GetUIType() const;

};
