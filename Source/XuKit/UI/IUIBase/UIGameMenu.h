// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "XuKit/UI/UIBase.h"
#include "UIGameMenu.generated.h"

/**
 * 
 */
UCLASS()
class XUKIT_API UUIGameMenu : public UUIBase
{
	GENERATED_BODY()

public:
	virtual EUILayer GetUILayer() const override;
	virtual EUIType GetUIType() const override;
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
};
