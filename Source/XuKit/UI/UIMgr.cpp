// Fill out your copyright notice in the Description page of Project Settings.


#include "UIMgr.h"

#include "UIBase.h"
#include "Blueprint/UserWidget.h"
#include "IUIBase/UIGameLose.h"
#include "IUIBase/UIGameMenu.h"
#include "IUIBase/UIGameOverridePanel.h"
#include "IUIBase/UIGameSettingScreen.h"
#include "IUIBase/UIGameWin.h"
#include "IUIBase/UIInteraction.h"
#include "IUIBase/UIMessageBox.h"
#include "IUIBase/UIPlayerHUD.h"
#include "IUIBase/UIStart.h"
#include "IUIBase/UITips.h"
#include "XuKit/XuBPFuncLib.h"


void UUIMgr::Init()
{
	uiActiveList.Empty();
	uiActiveDic.Empty();
	UIStackList.Empty();
	UIPathMap = {
		{UUIMessageBox::StaticClass(), GetUIPath(TEXT("W_UIMessageBox"),TEXT("UIMessageBox"))},
		{UUIStart::StaticClass(), GetUIPath(TEXT("W_UIStart"),TEXT("UIStart"))},
		{UUIGameSettingScreen::StaticClass(), GetUIPath(TEXT("W_UIGameSettingScreen"),TEXT("UIGameSettingScreen"))},
		{UUIPlayerHUD::StaticClass(), GetUIPath(TEXT("W_UIPlayerHUD"),TEXT("/UIPlayerHUD"))},
		{UUIGameWin::StaticClass(), GetUIPath(TEXT("W_UIGameWin"),TEXT("/UIGameEnd"))},
		{UUIGameLose::StaticClass(), GetUIPath(TEXT("W_UIGamLose"),TEXT("/UIGameEnd"))},
		{UUIInteraction::StaticClass(), GetUIPath(TEXT("W_UIInteraction"),TEXT("/UIInteraction"))},
		{UUIGameMenu::StaticClass(), GetUIPath(TEXT("W_UIGameMenu"),TEXT("/UIGameMenu"))},
		{UUIGameOverridePanel::StaticClass(), GetUIPath(TEXT("W_UIGameOverridePanel"),TEXT("/UIGameOverridePanel"))},
		{UUITips::StaticClass(), GetUIPath(TEXT("W_UITips"),TEXT("/UITips"))},

	};
	isInit = true;
}


UUserWidget* UUIMgr::ShowUIBP(TSubclassOf<UUserWidget> uiType, bool bHideLast, bool ForceShow)
{
	UUserWidget* uiBase = nullptr;
	UClass* U_TClassType = uiType.Get();
	FString name = U_TClassType->GetName();
	FString str = FString::Printf(TEXT("showui uiType is  %s "), *name);
	XuPRINT(str);

	ensureMsgf(UIPathMap.Contains(U_TClassType), TEXT("uipathMap key not cunzai"));

	UClass* uiclass = LoadClass<UUserWidget>(nullptr, *UIPathMap[U_TClassType]);
	ensureMsgf(uiclass, TEXT("UIclass is NUll"));

	uiBase = CreateWidget<UUserWidget>(GetWorld(), uiclass);

	if (!uiBase)
	{
		XuPRINT("UIBase is NUll");
	}
	check(uiBase);
	uiActiveList.Add(uiBase);

	uiActiveDic.Add(U_TClassType, uiBase);
	if (UUIBase* iui_base_interface = Cast<UUIBase>(uiBase))
	{
		if (iui_base_interface->GetUIType() == EUIType::Stack)
		{
			if (UIStackList.Num() > 0 && bHideLast)
			{
				UIStackList[UIStackList.Num() - 1]->RemoveFromParent();
			}
			UIStackList.Add(uiBase);
			UXuBPFuncLib::GetEventManager(this)->BroadcastEvent(EXuEventType::OnUpdateStackUI);
		}
		int32 layer = static_cast<int32>(iui_base_interface->GetUILayer());

		uiBase->AddToViewport(layer);

		// if (IUITopInterface* iui_top_interface = Cast<IUITopInterface>(uiBase))
		// {
		// 	if (UUITop* ui_top = GetUI<UUITop>())
		// 	{
		// 		ui_top->btnBack->OnClicked.RemoveAll(ui_top);
		// 		//绑定接口iui_top_interface的OnClickTopBackBtn方法
		// 		ui_top->btnBack->OnClicked.AddDynamic(iui_top_interface, &IUITopInterface::OnClickTopBackBtn);
		// 	}
		// }
		return uiBase;
	}
	return nullptr;
}

UUserWidget* UUIMgr::GetUIBP(TSubclassOf<UUserWidget> uiType)
{
	UClass* U_TClassType = uiType.Get();
	if (!uiActiveDic.Contains(U_TClassType))
	{
		return nullptr;
	}
	return uiActiveDic[U_TClassType];
}

void UUIMgr::HideUIBP(TSubclassOf<UUserWidget> uiType)
{
	UClass* U_TClassType = nullptr;
	U_TClassType = uiType.Get();
	if (!uiActiveDic.Contains(U_TClassType))
	{
		return;
	}

	UUserWidget* uIBase = uiActiveDic[U_TClassType];
	uIBase->RemoveFromParent();
	UUIBase* iui_base_interface = Cast<UUIBase>(uIBase);
	if (!iui_base_interface)
	{
		return;
	}

	if (iui_base_interface->GetUIType() == EUIType::Stack)
	{
		if (UIStackList.Num() <= 0)
		{
			return;
		}

		if (UIStackList[UIStackList.Num() - 1] == uIBase)
		{
			UIStackList.Remove(uIBase);
			if (UIStackList.Num()>0)
			{
				UUserWidget* NewUiBase = UIStackList[UIStackList.Num() - 1];
				int32 layer = static_cast<int32>(Cast<UUIBase>(NewUiBase)->GetUILayer());
				NewUiBase->AddToViewport(layer);
			}
			
		}
		else
		{
			UIStackList.Remove(uIBase);
		}
	}
	uiActiveDic.Remove(U_TClassType);
	uiActiveList.Remove(uIBase);
	UXuBPFuncLib::GetEventManager(this)->BroadcastEvent(EXuEventType::OnUpdateStackUI);
	// if (IUITopInterface* iui_top_interface = Cast<IUITopInterface>(uIBase))
	// {
	// 	if (UUITop* ui_top = GetUI<UUITop>())
	// 	{
	// 		ui_top->btnBack->OnClicked.RemoveAll(this);
	// 		ui_top->btnBack->OnClicked.AddDynamic(ui_top, &UUITop::OnclickBackBtn);
	// 	}
	// }
}


void UUIMgr::PopUI()
{
	if (UIStackList.Num() > 0)
	{
		UUserWidget* uiBase = UIStackList[UIStackList.Num() - 1];
		HideUIBP(uiBase->GetClass()->GetSuperClass());
	}
}

int UUIMgr::GetStackUINum()
{
	return UIStackList.Num();
}

FString UUIMgr::GetUIPath(FString uiName, FString dir)
{
	FString uiPath = FString::Format(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/XuAsset/UI/UIBase{0}/{1}.{1}_C'"), {dir, uiName});
	return uiPath;
}
