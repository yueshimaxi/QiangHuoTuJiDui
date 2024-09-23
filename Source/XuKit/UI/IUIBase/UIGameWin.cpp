#include "UIGameWin.h"


EUILayer UUIGameWin::GetUILayer_Implementation() const
{
	return EUILayer::Low;
}

EUIType UUIGameWin::GetUIType_Implementation() const
{
	return EUIType::Normal;
}

void UUIGameWin::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UUIGameWin::NativeConstruct()
{
	Super::NativeConstruct();
}

void UUIGameWin::NativeDestruct()
{
	Super::NativeDestruct();
}
