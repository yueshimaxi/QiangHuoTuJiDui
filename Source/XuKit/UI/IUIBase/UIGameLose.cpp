#include "UIGameLose.h"

EUILayer UUIGameLose::GetUILayer() const
{
	return EUILayer::Low;
}

EUIType UUIGameLose::GetUIType() const
{
	return EUIType::Normal;
}


void UUIGameLose::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UUIGameLose::NativeConstruct()
{
	Super::NativeConstruct();
}

void UUIGameLose::NativeDestruct()
{
	Super::NativeDestruct();
}
