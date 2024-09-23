// Fill out your copyright notice in the Description page of Project Settings.


#include "UIMgr.h"

#include "UIBaseInterface.h"
#include "Blueprint/UserWidget.h"
#include "IUIBase/UIGameLose.h"
#include "IUIBase/UIGameSettingScreen.h"
#include "IUIBase/UIGameWin.h"
#include "IUIBase/UIMessageBox.h"
#include "IUIBase/UIPlayerHUD.h"
#include "IUIBase/UIStart.h"
#include "XuKit/XuBPFuncLib.h"


void UUIMgr::Init()
{
	uiActiveList.Empty();
	uiActiveDic.Empty();
	UIStackList.Empty();
	UIPathMap = {
		{UUIMessageBox::StaticClass(), GetUIPath(TEXT("UIMessageBox_BP"))},
		{UUIStart::StaticClass(), GetUIPath(TEXT("UIStart_BP"))},
		{UUIGameSettingScreen::StaticClass(), GetUIPath(TEXT("UIGameSettingScreen_BP"))},
		{UUIPlayerHUD::StaticClass(), GetUIPath(TEXT("UIPlayerHUD_BP"))},
		{UUIGameLose::StaticClass(), "/Script/UMGEditor.WidgetBlueprint'/Game/XuAsset/BP/UI/UIBaseInterface/GameEnd/UIGamLose_BP.UIGamLose_BP_C'"},
		{UUIGameWin::StaticClass(), "/Script/UMGEditor.WidgetBlueprint'/Game/XuAsset/BP/UI/UIBaseInterface/GameEnd/UIGameWin_BP.UIGameWin_BP_C'"},

	};
	isInit = true;
}


UUserWidget* UUIMgr::ShowUIBP(TSubclassOf<UUserWidget> uiType)
{
	if (isInit == false)
	{
		Init();
	}
	UUserWidget* uiBase = nullptr;
	UClass* U_TClassType = uiType.Get();
	FString name = U_TClassType->GetName();
	FString str = FString::Printf(TEXT("showui uiType is  %s "), *name);
	XuPRINT(str);

	if (!UIPathMap.Contains(U_TClassType))
	{
		XuPRINT(TEXT("uipathMap key not cunzai"));
	}
	UClass* uiclass = LoadClass<UUserWidget>(nullptr, *UIPathMap[U_TClassType]);
	if (!uiclass)
	{
		XuPRINT("UIclass is NUll");
	}
	uiBase = CreateWidget<UUserWidget>(GetWorld(), uiclass);
	XuPRINT("CreateWidget");

	if (!uiBase)
	{
		XuPRINT("UIBase is NUll");
	}
	uiActiveList.Add(uiBase);

	uiActiveDic.Add(U_TClassType, uiBase);
	if (IUIBaseInterface* iui_base_interface = Cast<IUIBaseInterface>(uiBase))
	{
		if (iui_base_interface->GetUIType_Implementation() == EUIType::Stack)
		{
			if (UIStackList.Num() > 0)
			{
				UIStackList[UIStackList.Num() - 1]->RemoveFromParent();
			}
			UIStackList.Add(uiBase);
		}
		int32 layer = static_cast<int32>(iui_base_interface->GetUILayer_Implementation());

		uiBase->AddToViewport(layer);

		return uiBase;
	}
	return nullptr;
}

UUserWidget* UUIMgr::GetUIBP(TSubclassOf<UUserWidget> uiType)
{
	UClass* U_TClassType  = uiType.Get();
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

	if (IUIBaseInterface* iui_base_interface = Cast<IUIBaseInterface>(uIBase))
	{
		if (iui_base_interface->GetUIType_Implementation() == EUIType::Stack)
		{
			UIStackList.Remove(uIBase);
			if (UIStackList.Num() > 0)
			{
				UUserWidget* NewUiBase = UIStackList[UIStackList.Num() - 1];
				int32 layer = static_cast<int32>(Cast<IUIBaseInterface>(NewUiBase)->GetUILayer_Implementation());
				NewUiBase->AddToViewport(layer);
			}
		}
	}
	uiActiveDic.Remove(U_TClassType);
	uiActiveList.Remove(uIBase);
	uIBase->RemoveFromParent();
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

FString UUIMgr::GetUIPath(FString uiName)
{
	FString uiPath = TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/XuAsset/BP/UI/UIBaseInterface/");
	return FString::Printf(TEXT("%s%s.%s_C'"), *uiPath, *uiName, *uiName);
}
