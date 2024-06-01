// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "QHPlayerController.generated.h"

class UInputAction;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class XUKIT_API AQHPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AQHPlayerController();

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void PlayerTick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> inputMap;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> input_action_move;

	UFUNCTION()
	void OnMove(const FInputActionValue& input_action_value);
};
