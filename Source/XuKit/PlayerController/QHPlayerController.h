// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "XuKit/AbilitySystem/QHAbilitySystemComponent.h"
#include "QHPlayerController.generated.h"

class UDamageTextWidgetComponent;
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
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> inputMap;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> input_action_move;
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> ic_ESC;
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> ic_Tab;



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



	UPROPERTY(ReplicatedUsing=OnRep_CurorHitResult)
	FHitResult CurorHitResult;

	UFUNCTION()
	void OnRep_CurorHitResult(FHitResult oldCurorHitResult);

	UFUNCTION(Server,Reliable)
	void ServerSetCurorHitResult(FHitResult hitResult);
	
	void TraceMouseCuror();

public:
	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UDamageTextWidgetComponent>	DamageTextWidgetComponentClass;
	UFUNCTION(Client,Reliable)
	void ShowDamageText(float damage, ACharacter* targetCharacter, bool bIsCriticalHit, bool bIsBlockedHit);	


	UFUNCTION(Client,Reliable)
	void GameLose();
	UFUNCTION(Client,Reliable)
	void GameWin();

	void OnESC();
	void OnTab();

};





