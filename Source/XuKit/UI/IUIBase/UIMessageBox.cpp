// Fill out your copyright notice in the Description page of Project Settings.


#include "UIMessageBox.h"

#include "Components/Button.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "XuKit/UI/UIMgr.h"

EUILayer UUIMessageBox::GetUILayer_Implementation() const
{
	return EUILayer::Tips;
	
}

EUIType UUIMessageBox::GetUIType_Implementation() const
{
	return EUIType::Normal;
}

void UUIMessageBox::InitOne(FString titleStr, FString contentStr,FString leftBtnStr, FMyDelegate leftBtnFunc)
{
	title->SetText(FText::FromString(titleStr));
	content->SetText(FText::FromString(contentStr));
	leftBtnText->SetText(FText::FromString(leftBtnStr));
	left_btn_delegate=leftBtnFunc;
	rightSizeBox->SetVisibility(ESlateVisibility::Collapsed);
	
}

void UUIMessageBox::InitTwo(FString titleStr, FString contentStr,FString leftBtnStr, FMyDelegate leftBtnFunc, FString rightBtnStr, FMyDelegate rightBtnFunc)
{
	title->SetText(FText::FromString(titleStr));
	content->SetText(FText::FromString(contentStr));
	leftBtnText->SetText(FText::FromString(leftBtnStr));
	rightBtnText->SetText(FText::FromString(rightBtnStr));
	left_btn_delegate=leftBtnFunc;
	right_btn_delegate=rightBtnFunc;
	rightSizeBox->SetVisibility(ESlateVisibility::Visible);

}



void UUIMessageBox::OnClickLeftBtn()
{
	if (left_btn_delegate.IsBound())
	{
		left_btn_delegate.Execute();
	}
	GetWorld()->GetGameInstance()->GetSubsystem<UUIMgr>()->HideUI<UUIMessageBox>();
}

void UUIMessageBox::OnClickRightBtn()
{
	if (right_btn_delegate.IsBound())
	{
		right_btn_delegate.Execute();
	}
	GetWorld()->GetGameInstance()->GetSubsystem<UUIMgr>()->HideUI<UUIMessageBox>();
}



void UUIMessageBox::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	leftBtn->OnClicked.AddDynamic(this,&UUIMessageBox::OnClickLeftBtn);
	rightBtn->OnClicked.AddDynamic(this,&UUIMessageBox::OnClickRightBtn);
}
