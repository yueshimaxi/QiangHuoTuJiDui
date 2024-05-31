#include "UIStart.h"

EUILayer UUIStart::GetUILayer_Implementation() const
{
	return EUILayer::Bottom;
}

EUIType UUIStart::GetUIType_Implementation() const
{
	return EUIType::Normal;
}
