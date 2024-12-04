// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XuKit/UI/UIBase.h"
#include "UIGameOverridePanel.generated.h"

/**
 * 
 */
UCLASS()
class XUKIT_API UUIGameOverridePanel : public UUIBase
{
	GENERATED_BODY()
public:
	
	virtual EUILayer GetUILayer() const override;
	virtual EUIType GetUIType() const override;
};
