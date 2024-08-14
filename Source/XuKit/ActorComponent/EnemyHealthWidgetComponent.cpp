// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyHealthWidgetComponent.h"

void UEnemyHealthWidgetComponent::InitWidget()
{
	Super::InitWidget();
	isInitWidgeted = true;
	if (OnWidgetInit.IsBound())
	{
		OnWidgetInit.Execute();
		
	}
	OnDynamicWidgetInit.Broadcast();
}
