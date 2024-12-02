// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TileView.h"
#include "XuTileView.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FXuBPOnItemInitDynamic, UUserWidget*, widget, UObject*, Item);

DECLARE_DELEGATE_ThreeParams(FXuOnItemInit, UUserWidget*, int, bool);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FXuBPOnItemIsHoveredChangedDynamic, UUserWidget*, widget, UObject*, Item, bool, bIsHovered);

DECLARE_DELEGATE_TwoParams(FXuOnItemIsHoveredChanged, UUserWidget*, bool);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FXuBPOnItemSelectedChangedDynamic, UUserWidget*, widget, UObject*, Item, bool, bIsSelected);

DECLARE_DELEGATE_ThreeParams(FXuOnItemSelectedChanged, UUserWidget*, int, bool);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FXuBPOnItemClickedDynamic, UUserWidget*, widget, UObject*, Item);

DECLARE_DELEGATE_TwoParams(FXuOnItemClicked, UUserWidget*, int);


UCLASS()
class UXuEmptyEntryObj : public UObject
{
	GENERATED_BODY()

public:
};

/**
 * 
 */
UCLASS()
class UXuTileView : public UTileView
{
	GENERATED_BODY()

protected:
	virtual UUserWidget& OnGenerateEntryWidgetInternal(UObject* Item, TSubclassOf<UUserWidget> DesiredEntryClass, const TSharedRef<STableViewBase>& OwnerTable) override;


	virtual void HandleListEntryHovered(UUserWidget& EntryWidget) override;
	virtual void HandleListEntryUnhovered(UUserWidget& EntryWidget) override;

	virtual void OnSelectionChangedInternal(UObject* FirstSelectedItem) override;
	virtual void OnItemClickedInternal(UObject* Item) override;

	//virtual void OnItemDoubleClickedInternal(UObject* Item) override;
	//virtual void OnItemScrolledIntoViewInternal(UObject* Item, UUserWidget& EntryWidget) override;

public:
	UPROPERTY(BlueprintAssignable, Category = Events, meta = (DisplayName = "Xu On Item Is Inited"))
	FXuBPOnItemInitDynamic BP_Xu_OnItemInited;
	UPROPERTY(BlueprintAssignable, Category = Events, meta = (DisplayName = "Xu On Item Is Hovered Changed"))
	FXuBPOnItemIsHoveredChangedDynamic BP_Xu_OnItemIsHoveredChanged;

	UPROPERTY(BlueprintAssignable, Category = Events, meta = (DisplayName = "Xu On Item Selection Changed"))
	FXuBPOnItemSelectedChangedDynamic BP_Xu_OnItemSelectionChanged;

	UPROPERTY(BlueprintAssignable, Category = Events, meta = (DisplayName = "Xu On Item Clicked"))
	FXuBPOnItemClickedDynamic BP_Xu_OnItemClicked;


	// UPROPERTY(BlueprintAssignable, Category = Events, meta = (DisplayName = "On Item Double Clicked"))
	// FSimpleListItemEventDynamic BP_OnItemDoubleClicked;

	FXuOnItemInit Xu_OnItemInited;
	FXuOnItemIsHoveredChanged Xu_OnItemIsHoveredChanged;
	FXuOnItemSelectedChanged Xu_OnItemSelectedChanged;
	FXuOnItemClicked Xu_OnItemClicked;


	int xuSelectIndex=0;

	//FXuOnItemInit、FXuOnItemIsHoveredChanged、FXuOnItemSelectedChanged、FXuOnItemClicked
	void InitScrollView(int num, FXuOnItemInit _OnItemInited = nullptr, FXuOnItemSelectedChanged _OnItemSelectedChanged = nullptr, FXuOnItemIsHoveredChanged _OnItemIsHoveredChanged = nullptr, FXuOnItemClicked _OnItemClicked = nullptr);
};
