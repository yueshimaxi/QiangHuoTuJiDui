// Fill out your copyright notice in the Description page of Project Settings.


#include "XuTileView.h"


UUserWidget& UXuTileView::OnGenerateEntryWidgetInternal(UObject* Item, TSubclassOf<UUserWidget> DesiredEntryClass, const TSharedRef<STableViewBase>& OwnerTable)
{
	UUserWidget& widget = Super::OnGenerateEntryWidgetInternal(Item, DesiredEntryClass, OwnerTable);
	int index = GetIndexForItem(Item);
	bool isSelected = xuSelectIndex == index;
	BP_Xu_OnItemInited.Broadcast(&widget, Item);
	Xu_OnItemInited.ExecuteIfBound(&widget, index, isSelected);
	return widget;
}

void UXuTileView::HandleListEntryHovered(UUserWidget& EntryWidget)
{
	Super::HandleListEntryHovered(EntryWidget);
	if (UObject* const* ListItem = ItemFromEntryWidget(EntryWidget))
	{
		BP_Xu_OnItemIsHoveredChanged.Broadcast(&EntryWidget, *ListItem, true);
		Xu_OnItemIsHoveredChanged.ExecuteIfBound(&EntryWidget, true);
	}
}

void UXuTileView::HandleListEntryUnhovered(UUserWidget& EntryWidget)
{
	Super::HandleListEntryUnhovered(EntryWidget);
	if (UObject* const* ListItem = ItemFromEntryWidget(EntryWidget))
	{
		BP_Xu_OnItemIsHoveredChanged.Broadcast(&EntryWidget, *ListItem, false);
		Xu_OnItemIsHoveredChanged.ExecuteIfBound(&EntryWidget, false);
	}
}

void UXuTileView::OnSelectionChangedInternal(UObject* FirstSelectedItem)
{
	Super::OnSelectionChangedInternal(FirstSelectedItem);
	int index = GetIndexForItem(FirstSelectedItem);
	if (index < 0)
	{
		index = 0;
		if (ListItems.Num() > 0)
		{
			FirstSelectedItem = ListItems[xuSelectIndex];
		}
	}
	int lastSelectIndex = xuSelectIndex;
	xuSelectIndex = index;
	if (UUserWidget* EntryWidget = GetEntryWidgetFromItem(FirstSelectedItem))
	{
		BP_Xu_OnItemSelectionChanged.Broadcast(EntryWidget, FirstSelectedItem, FirstSelectedItem != nullptr);
		Xu_OnItemSelectedChanged.ExecuteIfBound(EntryWidget, index, FirstSelectedItem != nullptr);

		if (lastSelectIndex != xuSelectIndex)
		{
			UObject* obj = ListItems[lastSelectIndex];
			UUserWidget* OldEntryWidget = GetEntryWidgetFromItem(obj);
			if (OldEntryWidget)
			{
				BP_Xu_OnItemSelectionChanged.Broadcast(OldEntryWidget, OldEntryWidget, false);
				Xu_OnItemSelectedChanged.ExecuteIfBound(OldEntryWidget, lastSelectIndex, false);
			}
		}
	}
}

void UXuTileView::OnItemClickedInternal(UObject* Item)
{
	Super::OnItemClickedInternal(Item);
	int index = GetIndexForItem(Item);

	if (UUserWidget* EntryWidget = GetEntryWidgetFromItem(Item))
	{
		BP_Xu_OnItemClicked.Broadcast(EntryWidget, Item);
		Xu_OnItemClicked.ExecuteIfBound(EntryWidget, index);
	}
}

void UXuTileView::InitScrollView(int num, FXuOnItemInit _OnItemInited, FXuOnItemSelectedChanged _OnItemSelectedChanged, FXuOnItemIsHoveredChanged _OnItemIsHoveredChanged, FXuOnItemClicked _OnItemClicked)
{
	xuSelectIndex = 0;
	Xu_OnItemInited = _OnItemInited;
	Xu_OnItemIsHoveredChanged = _OnItemIsHoveredChanged;
	Xu_OnItemSelectedChanged = _OnItemSelectedChanged;
	Xu_OnItemClicked = _OnItemClicked;
	TArray<UObject*> objs;
	for (int i = 0; i < num; ++i)
	{
		UXuEmptyEntryObj* item = NewObject<UXuEmptyEntryObj>();
		objs.Add(item);
	}
	SetListItems(objs);
}
