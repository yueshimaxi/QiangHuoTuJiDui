#include "UIPlayerHUD.h"


EUILayer UUIPlayerHUD::GetUILayer_Implementation() const
{
	return EUILayer::Bottom;
}

EUIType UUIPlayerHUD::GetUIType_Implementation() const
{
	return EUIType::Normal;
}
