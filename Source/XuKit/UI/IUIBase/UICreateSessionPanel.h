// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/EditableTextBox.h"
#include "XuKit/UI/UIBase.h"
#include "UICreateSessionPanel.generated.h"

/**
 * 
 */
UCLASS()
class XUKIT_API UUICreateSessionPanel :public UUIBase
{
	GENERATED_BODY()
public:
	virtual EUILayer GetUILayer() const override;
	virtual EUIType GetUIType() const override;
public:
	virtual void NativeOnInitialized() override;


	UPROPERTY(meta=(BindWidget))
	UButton* createRoomBtn;

	UPROPERTY(meta=(BindWidget))
	UButton* backBtn;

	UPROPERTY(meta=(BindWidget))
	UEditableTextBox* roomNameInput;

	UPROPERTY(meta=(BindWidget))
	UEditableTextBox* maxPlayerInput;

	UPROPERTY(meta=(BindWidget))
	UEditableTextBox* roomOwnerNameInput;
	
	UPROPERTY(meta=(BindWidget))
	UCheckBox* isLanCheckBox;
	
	UFUNCTION()
	void OnClickCreateRoomBtn();

	UFUNCTION()
	void OnClickBackBtn();


};
