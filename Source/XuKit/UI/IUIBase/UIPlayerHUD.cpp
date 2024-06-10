#include "UIPlayerHUD.h"

#include "XuKit/XuBPFuncLib.h"


EUILayer UUIPlayerHUD::GetUILayer_Implementation() const
{
	return EUILayer::Bottom;
}

EUIType UUIPlayerHUD::GetUIType_Implementation() const
{
	return EUIType::Normal;
}

void UUIPlayerHUD::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	XuPRINT("UUIPlayerHUD::NativeOnInitialized");
}

void UUIPlayerHUD::NativeConstruct()
{
	Super::NativeConstruct();
	XuPRINT("UUIPlayerHUD::NativeConstruct");
}

void UUIPlayerHUD::SetHUDAmmo(int ClipAmmoNum, int AllAmmoNum)
{
	XuPRINT("UUIPlayerHUD::SetHUDAmmo");
	ClipAmmoNum_Text->SetText(FText::FromString(FString::FromInt(ClipAmmoNum)));
	AllAmmoNum_Text->SetText(FText::FromString(FString::FromInt(AllAmmoNum)));
}
