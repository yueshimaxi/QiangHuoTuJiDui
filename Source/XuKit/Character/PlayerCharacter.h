// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QHCharacterBase.h"
#include "XuKit/Interface/CombatInterface.h"
#include "PlayerCharacter.generated.h"

class UCombatComponent;
class USpringArmComponent;
class UCameraComponent;
/**
 * 
 */
UCLASS()
class XUKIT_API APlayerCharacter : public AQHCharacterBase
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	virtual void InitAbilityActorInfo() override;
	virtual void PossessedBy(AController* NewController) override;

	virtual AProjectionWeapon* get_cur_projection_weapon_Implementation() override;

protected:
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* camera_component;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* spring_arm_component;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCombatComponent* combat_component;


	void SetPawnRotatorToMouseCursor();

	UCombatComponent* getCombatCom();



};
