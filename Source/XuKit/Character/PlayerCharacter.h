// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QHCharacterBase.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
/**
 * 
 */
UCLASS()
class XUKIT_API APlayerCharacter : public AQHCharacterBase
{
	GENERATED_BODY()

	APlayerCharacter();
protected:
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* camera_component;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* spring_arm_component;

};
