// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "UIRoomItemEntry.generated.h"

/**
 * 
 */
UCLASS()
class XUKIT_API UUIRoomItemEntry : public UCommonUserWidget,public IUserObjectListEntry
{
	GENERATED_BODY()
public:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	virtual void NativeOnItemSelectionChanged(bool bIsSelected) override;

	UPROPERTY()
	class UCustomBlueprintSessionResultData* data;


	UPROPERTY(BlueprintReadWrite,meta=(BindWidget))
	UTextBlock* room_name_text;
	
	UPROPERTY(BlueprintReadWrite,meta=(BindWidget))
	UTextBlock* room_owner_name_text;
	
	UPROPERTY(BlueprintReadWrite,meta=(BindWidget))
	UTextBlock* room_player_num_text;

	UPROPERTY(BlueprintReadWrite,meta=(BindWidget))
	UTextBlock* room_ping_text;

	UPROPERTY(BlueprintReadWrite,meta=(BindWidget))
	UImage* BG_image;

	UPROPERTY(meta=(BindWidget))
	UButton* join_room_btn;
	virtual void NativeOnInitialized() override;
	UFUNCTION()
	void OnClickJoinRoomBtn();
	
};
