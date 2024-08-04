// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "QHAIController.generated.h"

class UBehaviorTreeComponent;
/**
 * 
 */
UCLASS()
class XUKIT_API AQHAIController : public AAIController
{
	AQHAIController();
	GENERATED_BODY()

	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;
};
