// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/GameSettingScreen.h"
#include "XuKit/UI/Base/LyraTabListWidgetBase.h"
#include "UIGameSettingScreen.generated.h"

/**
 * 
 */
UCLASS()
class XUKIT_API UUIGameSettingScreen : public UGameSettingScreen
{
	GENERATED_BODY()

protected:
	virtual UGameSettingRegistry* CreateRegistry() override;

public:
	virtual EUILayer GetUILayer() const override;
	virtual EUIType GetUIType() const override;

public:
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	ULyraTabListWidgetBase* TopSettingsTabs;

	virtual void NativeOnInitialized() override;

	UFUNCTION()
	void OnToptabSelect(FName selectTabId);

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UCommonButtonBase* ApplyButton;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UCommonButtonBase* CancelButton;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UCommonButtonBase* ResetButton;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UCommonButtonBase* BackButton;

	UFUNCTION()
	void OnApplyButtonClicked();
	UFUNCTION()
	void OnCancelButtonClicked();
	UFUNCTION()
	void OnResetButtonClicked();
	UFUNCTION()
	void OnBackButtonClicked();
};
