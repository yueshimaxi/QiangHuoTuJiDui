// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "UIBase.generated.h"


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


UINTERFACE(MinimalAPI)
class UUITopInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class XUKIT_API IUITopInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "UIBase")
	void OnClickTopBackBtn();

};
/**
 * 
 */
UCLASS()
class XUKIT_API UUIBase : public UCommonActivatableWidget
{
	GENERATED_BODY()

	
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, Category = "UIBase")
	virtual EUILayer GetUILayer() const;

	UFUNCTION(BlueprintCallable, Category = "UIBase")
	virtual EUIType GetUIType() const;

	UPROPERTY(Transient,meta=(BindWidgetAnimOptional))
	UWidgetAnimation* OnActiveAnimation;

	FWidgetAnimationDynamicEvent Event_OnActiveAnimationFinished;

	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

	
	UFUNCTION()
	void OnActiveAnimationFinished();
	
	UFUNCTION()
	virtual void OnShowed();
	UFUNCTION()
	virtual void OnHide();
};
