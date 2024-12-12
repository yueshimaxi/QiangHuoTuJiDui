// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TextBlock.h"
#include "XuKit/UI/UIBase.h"
#include "UITips.generated.h"

/**
 * 
 */
UCLASS()
class XUKIT_API UUITips : public UUIBase
{
public:
	virtual EUILayer GetUILayer() const override;
	virtual EUIType GetUIType() const override;

private:
	GENERATED_BODY()

public:
	virtual void OnShowed() override;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_Tips;

	void SetTipsText(FString tips);

	FTimerHandle TimerHandle;

	void WaitForDestroy();
};

