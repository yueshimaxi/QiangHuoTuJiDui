#include "UIGameWin.h"


EUILayer UUIGameWin::GetUILayer() const
{
	return EUILayer::Low;
}

EUIType UUIGameWin::GetUIType() const
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
