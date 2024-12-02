#include "XuButton.h"

#include "XuKit/XuBPFuncLib.h"

UXuButton::UXuButton()
{
	OnClicked.AddDynamic(this, &UXuButton::OnClickBtn);
	OnClicked.AddDynamic(this, &UXuButton::XuNativeOnClickBtn);
	OnHovered.AddDynamic(this, &UXuButton::XuNativeOnHorverBtn);
}

void UXuButton::OnClickBtn()
{
	XuButtonClicked.ExecuteIfBound();
}

void UXuButton::XuNativeOnClickBtn_Implementation()
{
	XuPRINT(TEXT("XuNativeOnClickBtn_Implementation"));
}

void UXuButton::XuNativeOnHorverBtn_Implementation()
{
	XuPRINT(TEXT("XuNativeOnHorverBtn_Implementation"));

}

