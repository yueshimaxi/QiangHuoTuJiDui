// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Prop.h"
#include "AmmoBag.generated.h"

UCLASS()
class XUKIT_API AmmoBag : public AProp
{
	GENERATED_BODY()

public:
	AmmoBag();

	

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
