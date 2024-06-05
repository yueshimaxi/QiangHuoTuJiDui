// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "XuKit/AbilitySystem/QHAbilitySystemComponent.h"
#include "QHPlayerController.generated.h"

class UInputConfigDataAsset;
struct FInputActionValue;
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



	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputConfigDataAsset> inputConfigDataAsset;
	
	UFUNCTION()
	void OnMove(const FInputActionValue& input_action_value);

	UPROPERTY()
	UQHAbilitySystemComponent* abilitySystemComponent;
	
	void OnAbliityInputTagPressed(FGameplayTag inputActionTag);
	void OnAbliityInputTagHeld(FGameplayTag inputActionTag);
	void OnAbliityInputTagReleased(FGameplayTag inputActionTag);
	UQHAbilitySystemComponent* GetABS();
	
public:
	float horInputValue;
	float verInputValue;

	FHitResult CurorHitResult;

	void TraceMouseCuror();

	


};
