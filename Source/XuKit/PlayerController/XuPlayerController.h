// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "XuPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class XUKIT_API AXuPlayerController : public APlayerController
{
	GENERATED_BODY()
	AXuPlayerController();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
public:
	UPROPERTY()
	bool isWundering=false;



	FTransform GetCurViewTran();
};
