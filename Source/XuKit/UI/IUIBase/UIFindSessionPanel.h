// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/ListView.h"
#include "XuKit/Event/EventMgr.h"
#include "XuKit/UI/UIBase.h"
#include "UIFindSessionPanel.generated.h"

/**
 * 
 */
UCLASS()
class XUKIT_API UUIFindSessionPanel : public UUIBase
{
	GENERATED_BODY()
public:
	virtual EUILayer GetUILayer() const override;
	virtual EUIType GetUIType() const override;
public:
	virtual void NativeOnInitialized() override;

	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UButton* freshRoomListBtn;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UListView* room_list_view;


	UPROPERTY(meta=(BindWidget))
	UButton* backBtn;

	UPROPERTY(meta=(BindWidget))
	UBorder* noResultBorder;

	UPROPERTY(meta=(BindWidget))
	UImage* loadingImage;
	
	UPROPERTY()
	int fresh_room_list_view_EventID;

	UFUNCTION()
	void OnClickFreshRoomListBtn();
	UFUNCTION()
	void OnClickBackBtn();

	UFUNCTION()
	void OnFreshRoomListEvent(UEventData* event_data);
};
