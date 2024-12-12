// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "XuKit/UI/UIBase.h"
#include "XuKit/UI/Base/XuCommonButton.h"
#include "XuKit/UI/Base/XuTileView.h"
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

	virtual void OnShowed() override;

	UPROPERTY(meta=(BindWidget))
	UWidgetSwitcher* WidgetSwitcher_OverrideMenu;

	UPROPERTY(meta=(BindWidget))
	UXuTileView* TileView_TopOverrideMenu;


	UPROPERTY(meta=(BindWidget))
	UXuTileView* TileView_WeaponList;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* text_WeaponName;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* text_WeaponInfo;

	UPROPERTY(meta=(BindWidget))
	UXuCommonButton* Btn_Exit;

	UPROPERTY(EditAnywhere, Category="AInitInfo")
	TMap<FGameplayTag, UTexture2D*> WeaponIconMap;
	void InitTopMenu();
	void InitWeaponPanel();
};
