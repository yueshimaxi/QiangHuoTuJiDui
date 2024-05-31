// Fill out your copyright notice in the Description page of Project Settings.


#include "XuKit/UI//IUIBase/UIGameSettingScreen.h"

#include "CommonButtonBase.h"
#include "XuKit/Settings/LyraGameSettingRegistry.h"
#include "XuKit/UI/UIMgr.h"

UGameSettingRegistry* UUIGameSettingScreen::CreateRegistry()
{
	ULyraGameSettingRegistry* NewRegistry = NewObject<ULyraGameSettingRegistry>();
	ULocalPlayer* ownLocalPlayer = GetOwningLocalPlayer();
	if (ULyraLocalPlayer* LocalPlayer = CastChecked<ULyraLocalPlayer>(ownLocalPlayer))
	{
		NewRegistry->Initialize(LocalPlayer);
	}
	return NewRegistry; 
}

EUILayer UUIGameSettingScreen::GetUILayer_Implementation() const
{
	return EUILayer::Low;
}

EUIType UUIGameSettingScreen::GetUIType_Implementation() const
{
	return EUIType::Stack;
}

void UUIGameSettingScreen::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	TopSettingsTabs->OnTabSelected.AddDynamic(this,&UUIGameSettingScreen::OnToptabSelect);
	ApplyButton->OnClicked().AddUObject(this, &UUIGameSettingScreen::OnApplyButtonClicked);
	CancelButton->OnClicked().AddUObject(this, &UUIGameSettingScreen::OnCancelButtonClicked);
	ResetButton->OnClicked().AddUObject(this, &UUIGameSettingScreen::OnResetButtonClicked);
	BackButton->OnClicked().AddUObject(this, &UUIGameSettingScreen::OnBackButtonClicked);
}

void UUIGameSettingScreen::OnToptabSelect(FName selectTabId)
{
	NavigateToSetting(selectTabId);
}

void UUIGameSettingScreen::OnApplyButtonClicked()
{
	ApplyChanges();

}

void UUIGameSettingScreen::OnCancelButtonClicked()
{
	CancelChanges();
}

void UUIGameSettingScreen::OnResetButtonClicked()
{
}

void UUIGameSettingScreen::OnBackButtonClicked()
{
	ApplyChanges();
	GetWorld()->GetGameInstance()->GetSubsystem<UUIMgr>()->PopUI();
}


