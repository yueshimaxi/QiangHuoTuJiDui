// Fill out your copyright notice in the Description page of Project Settings.


#include "XuCommonButton.h"

void UXuCommonButton::NativePreConstruct()
{
	Super::NativePreConstruct();
	UpdateButtonStyle();
}
