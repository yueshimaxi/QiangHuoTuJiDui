// Fill out your copyright notice in the Description page of Project Settings.


#include "XuKit/UI/IUIBase/UICreateSessionPanel.h"

#include "XuKit/XuBPFuncLib.h"
#include "XuKit/GameInstance/XuGI.h"
#include "XuKit/UI/UIMgr.h"

EUILayer UUICreateSessionPanel::GetUILayer_Implementation() const
{
	return EUILayer::Low;
}

EUIType UUICreateSessionPanel::GetUIType_Implementation() const
{
	return EUIType::Stack;
}
void UUICreateSessionPanel::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	createRoomBtn->OnClicked.AddDynamic(this, &UUICreateSessionPanel::OnClickCreateRoomBtn);
	backBtn->OnClicked.AddDynamic(this, &UUICreateSessionPanel::OnClickBackBtn);
}

void UUICreateSessionPanel::OnClickCreateRoomBtn()
{
	if (UXuGI* xu_net_game_instance = Cast<UXuGI>(GetGameInstance()))
	{
		xu_net_game_instance->StartOnlineGame(roomNameInput->GetText().ToString(),
			roomOwnerNameInput->GetText().ToString(),
			FCString::Atoi(*maxPlayerInput->GetText().ToString()),
			isLanCheckBox->IsChecked());
	}
}

void UUICreateSessionPanel::OnClickBackBtn()
{
	UXuBPFuncLib::GetUIManager(GetWorld())->HideUI<UUICreateSessionPanel>();
}

