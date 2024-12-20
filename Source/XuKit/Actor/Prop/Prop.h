// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "XuKit/Interface/IInteractionIterface.h"
#include "Prop.generated.h"

UCLASS()
class XUKIT_API AProp : public AActor, public IIInteractionIterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual FGameplayTag GetInteractionType_Implementation() override;
};
