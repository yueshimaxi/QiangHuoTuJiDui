// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "QHCharacterBase.generated.h"

UCLASS()
class XUKIT_API AQHCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AQHCharacterBase();

protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	USkeletalMeshComponent* WeaponMesh;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
