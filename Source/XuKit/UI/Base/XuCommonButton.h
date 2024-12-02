// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "XuCommonButton.generated.h"

/**
 * 
 */
UCLASS()
class  UXuCommonButton : public UCommonButtonBase
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateButtonStyle();
};
