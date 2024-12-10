// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "XuKit/Character/PlayerCharacter.h"
#include "XuKit/Interface/IInteractionIterface.h"
#include "AmmoBag.generated.h"

UCLASS()
class XUKIT_API AAmmoBag : public AActor, public IIInteractionIterface
{
	GENERATED_BODY()

public:
	AAmmoBag();

	

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AInitInfo")
	int ReSpawnTime;

	UPROPERTY(EditAnywhere,Category="AInitInfo")
	FGameplayTag AmmoTag;

	virtual EInteractionType GetInteractionType_Implementation() override;

	//补充弹药
	void ReplenishAmmo(APlayerCharacter* player_character);

	UFUNCTION(BlueprintNativeEvent)
	void OnAmmoBagPickedUp();
};
