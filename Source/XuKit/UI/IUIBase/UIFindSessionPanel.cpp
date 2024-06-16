// Fill out your copyright notice in the Description page of Project Settings.


#include "XuKit/UI/IUIBase/UIFindSessionPanel.h"
#include "XuKit/Event/EventDataDefine.h"
#include "XuKit/UI/UIMgr.h"

EUILayer UUIFindSessionPanel::GetUILayer_Implementation() const
{
	return EUILayer::Low;
}

EUIType UUIFindSessionPanel::GetUIType_Implementation() const
{
	return EUIType::Stack;
}
void UUIFindSessionPanel::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	freshRoomListBtn->OnClicked.AddDynamic(this, &UUIFindSessionPanel::OnClickFreshRoomListBtn);
	backBtn->OnClicked.AddDynamic(this, &UUIFindSessionPanel::OnClickBackBtn);
}

void UUIFindSessionPanel::NativeConstruct()
{
	Super::NativeConstruct();
	FXuEventDelegate fresh_room_list_eventDelegate;
	fresh_room_list_eventDelegate.BindDynamic(this, &UUIFindSessionPanel::OnFreshRoomListEvent);
	GetWorld()->GetSubsystem<UEventMgr>()->RegistEvent(EXuEventType::FreshRoomList, fresh_room_list_view_EventID, fresh_room_list_eventDelegate);
	loadingImage->SetVisibility(ESlateVisibility::Collapsed);
	noResultBorder->SetVisibility(ESlateVisibility::Collapsed);
	OnClickFreshRoomListBtn();
}

void UUIFindSessionPanel::NativeDestruct()
{
	Super::NativeDestruct();
	GetWorld()->GetSubsystem<UEventMgr>()->RemoveEvent(EXuEventType::FreshRoomList, fresh_room_list_view_EventID);

}

void UUIFindSessionPanel::OnClickFreshRoomListBtn()
{
	if (UXuGI* xu_net_game_instance = Cast<UXuGI>(GetGameInstance()))
	{
		xu_net_game_instance->FindOnlineGames(false, true);
		loadingImage->SetVisibility(ESlateVisibility::Visible);
		noResultBorder->SetVisibility(ESlateVisibility::Collapsed);

	}
	freshRoomListBtn->SetIsEnabled(false);

}

void UUIFindSessionPanel::OnClickBackBtn()
{
	GetWorld()->GetGameInstance()->GetSubsystem<UUIMgr>()->HideUI<UUIFindSessionPanel>();
}

void UUIFindSessionPanel::OnFreshRoomListEvent(UEventData* event_data)
{
	freshRoomListBtn->SetIsEnabled(true);
	loadingImage->SetVisibility(ESlateVisibility::Collapsed);
	if (UFreshRoomListEventData* fresh_room_list_event_data = Cast<UFreshRoomListEventData>(event_data))
	{
		room_list_view->SetListItems(fresh_room_list_event_data->roomListData);
		if (fresh_room_list_event_data->roomListData.Num()<=0)
		{
			noResultBorder->SetVisibility(ESlateVisibility::Visible);
		}
	}
	else
	{
		noResultBorder->SetVisibility(ESlateVisibility::Visible);

	}
}
