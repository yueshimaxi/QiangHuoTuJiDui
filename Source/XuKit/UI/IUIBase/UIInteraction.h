// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "XuKit/UI/UIBase.h"
#include "UIInteraction.generated.h"

/**
 * 
 */
UCLASS()
class XUKIT_API UUIInteraction : public UUIBase
{
	GENERATED_BODY()

	

public:
	virtual EUILayer GetUILayer() const override;
	virtual EUIType GetUIType() const override;
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	void UpdateMousePosition(FVector2D MousePosition);
	void Interact();

	UPROPERTY(Transient,meta=(BindWidgetAnim))
	UWidgetAnimation* ShowAnimation;
	UFUNCTION(BlueprintNativeEvent)
	void PlayShowAnim(bool bShow);
	
};

