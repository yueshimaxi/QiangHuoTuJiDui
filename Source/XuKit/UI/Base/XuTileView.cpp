// Fill out your copyright notice in the Description page of Project Settings.


#include "XuTileView.h"


UUserWidget& UXuTileView::OnGenerateEntryWidgetInternal(UObject* Item, TSubclassOf<UUserWidget> DesiredEntryClass, const TSharedRef<STableViewBase>& OwnerTable)
{
	UUserWidget& widget = Super::OnGenerateEntryWidgetInternal(Item, DesiredEntryClass, OwnerTable);
	int index = GetIndexForItem(Item);
	bool isSelected = xuSelectIndex == index;
	Xu_OnItemInited.ExecuteIfBound(&widget, index, isSelected);
	return widget;
}

void UXuTileView::HandleListEntryHovered(UUserWidget& EntryWidget)
{
	Super::HandleListEntryHovered(EntryWidget);
	if (UObject* const* ListItem = ItemFromEntryWidget(EntryWidget))
	{
		Xu_OnItemIsHoveredChanged.ExecuteIfBound(&EntryWidget, true);
	}
}

void UXuTileView::HandleListEntryUnhovered(UUserWidget& EntryWidget)
{
	Super::HandleListEntryUnhovered(EntryWidget);
	if (UObject* const* ListItem = ItemFromEntryWidget(EntryWidget))
	{
		Xu_OnItemIsHoveredChanged.ExecuteIfBound(&EntryWidget, false);
	}
}

void UXuTileView::OnSelectionChangedInternal(UObject* FirstSelectedItem)
{ 
	Super::OnSelectionChangedInternal(FirstSelectedItem);
	if(FirstSelectedItem == nullptr)
	{
		return;
	}
	int index = GetIndexForItem(FirstSelectedItem);

	int lastSelectIndex = xuSelectIndex;
	xuSelectIndex = index;
	if (UUserWidget* EntryWidget = GetEntryWidgetFromItem(FirstSelectedItem))
	{
		Xu_OnItemInited.ExecuteIfBound(EntryWidget, index, FirstSelectedItem != nullptr);
	}
	if (lastSelectIndex != xuSelectIndex && lastSelectIndex >= 0 && lastSelectIndex < ListItems.Num())
	{
		UObject* obj = ListItems[lastSelectIndex];
		UUserWidget* OldEntryWidget = GetEntryWidgetFromItem(obj);
		if (OldEntryWidget)
		{
			Xu_OnItemInited.ExecuteIfBound(OldEntryWidget, lastSelectIndex, false);
		}
	}
}

void UXuTileView::OnItemClickedInternal(UObject* Item)
{
	Super::OnItemClickedInternal(Item);
	int index = GetIndexForItem(Item);

	if (UUserWidget* EntryWidget = GetEntryWidgetFromItem(Item))
	{
		Xu_OnItemClicked.ExecuteIfBound(EntryWidget, index);
	}
}

void UXuTileView::InitScrollView(int num, FXuOnItemInit _OnItemInited,FXuOnItemIsHoveredChanged _OnItemIsHoveredChanged, FXuOnItemClicked _OnItemClicked, int selectIndex)
{
	xuSelectIndex = selectIndex;
	Xu_OnItemInited = _OnItemInited;
	Xu_OnItemIsHoveredChanged = _OnItemIsHoveredChanged;
	Xu_OnItemClicked = _OnItemClicked;
	TArray<UObject*> objs;
	for (int i = 0; i < num; ++i)
	{
		UXuEmptyEntryObj* item = NewObject<UXuEmptyEntryObj>();
		objs.Add(item);
	}
	SetListItems(objs);
}
