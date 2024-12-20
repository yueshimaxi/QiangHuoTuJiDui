// Fill out your copyright notice in the Description page of Project Settings.


#include "XuKit/UI/Entry/UIRoomItemEntry.h"

#include "XuKit/XuBPFuncLib.h"
#include "XuKit/GameInstance/XuGI.h"
#include "XuKit/UI/UIMgr.h"
#include "XuKit/UI/IUIBase/UIFindSessionPanel.h"

void UUIRoomItemEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	data = Cast<UCustomBlueprintSessionResultData>(ListItemObject);
	if (data)
	{
		room_name_text->SetText(FText::FromString(data->result.roomName));
		room_owner_name_text->SetText(FText::FromString(data->result.roomOwnerName+TEXT("的房间")));
		room_player_num_text->SetText(FText::FromString(FString::FromInt(data->result.CurrentNumberOfPlayers)+"/"+FString::FromInt(data->result.MaxNumberOfPlayers)));
		room_ping_text->SetText(FText::FromString(FString::FromInt(data->result.Ping)));
	}
}
void UUIRoomItemEntry::NativeOnItemSelectionChanged(bool bIsSelected)
{
	IUserObjectListEntry::NativeOnItemSelectionChanged(bIsSelected);
	BG_image->SetColorAndOpacity(bIsSelected?FColor::Yellow:FColor(1,1,1,0));
}

void UUIRoomItemEntry::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	join_room_btn->OnClicked.AddDynamic(this, &UUIRoomItemEntry::OnClickJoinRoomBtn);
}

void UUIRoomItemEntry::OnClickJoinRoomBtn()
{
	if (data)
	{
		UUIFindSessionPanel* uui_find_session_panel = UXuBPFuncLib::GetUIManager(GetWorld())->GetUI<UUIFindSessionPanel>();
		if (UXuGI* xu_net_game_instance = Cast<UXuGI>(GetGameInstance()))
		{
			int index= uui_find_session_panel->room_list_view->GetIndexForItem(data);
			xu_net_game_instance->JoinOnlineGame(index);
		}
	}
}
