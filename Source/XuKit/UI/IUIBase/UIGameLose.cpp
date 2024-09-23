#include "UIGameLose.h"

EUILayer UUIGameLose::GetUILayer_Implementation() const
{
	return EUILayer::Low;
}

EUIType UUIGameLose::GetUIType_Implementation() const
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
