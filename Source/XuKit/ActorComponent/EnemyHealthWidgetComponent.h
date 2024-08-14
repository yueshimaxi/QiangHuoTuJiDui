// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "EnemyHealthWidgetComponent.generated.h"


/**
 * 
 */
UCLASS()
class XUKIT_API UEnemyHealthWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	virtual void InitWidget() override;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWidgetInitDynamic);
	DECLARE_DELEGATE(FOnWidgetInit);

	FOnWidgetInitDynamic OnDynamicWidgetInit;
	FOnWidgetInit OnWidgetInit;

	bool isInitWidgeted=false;
};
