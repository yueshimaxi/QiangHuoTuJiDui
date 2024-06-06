// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Casing.generated.h"

UCLASS()
class XUKIT_API ACasing : public AActor
{
	GENERATED_BODY()

public:

protected:
	ACasing();
	virtual void BeginPlay() override;

public:

private:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* mesh_component;

	// UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category="AInitInfo")
	// USoundBase* fall_sound;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category="AInitInfo")
	float ShellEjectionImpulse;
	UPROPERTY(EditAnywhere, Category="AInitInfo")
	float lifeTime=3.2f;

	// UFUNCTION()
	// void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	//            FVector NormalImpulse, const FHitResult& Hit);
};
