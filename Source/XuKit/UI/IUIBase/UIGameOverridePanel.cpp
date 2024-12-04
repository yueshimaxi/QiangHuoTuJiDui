// Fill out your copyright notice in the Description page of Project Settings.


#include "UIGameOverridePanel.h"

EUILayer UUIGameOverridePanel::GetUILayer() const
{
	return EUILayer::Low;
}

EUIType UUIGameOverridePanel::GetUIType() const
{
	return EUIType::Stack;
}
