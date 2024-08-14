// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QHCharacterBase.h"
#include "XuKit/AbilitySystem/QHAttributeSet.h"
#include "EnemyCharacter.generated.h"

class UEnemyHealthWidgetComponent;
/**
 * 
 */
UCLASS()
class XUKIT_API AEnemyCharacter : public AQHCharacterBase
{
	GENERATED_BODY()

public:
	
	AEnemyCharacter();

	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo() override;

	virtual void PossessedBy(AController* NewController) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="AI")
	class UBehaviorTree* BehaviorTree;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="AI")
	class UBlackboardData* BlackboardData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="AI")
	class AQHAIController* AuraAIController ;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UEnemyHealthWidgetComponent* HealthBarWidgetComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CharactorInfo")
	int BaseWalkSpeed=100;
	
	UPROPERTY()
	bool bHitReact;

	UPROPERTY(BlueprintAssignable)
	FAttributeInfoChangeSigntal HealthChange;
	UPROPERTY(BlueprintAssignable)
	FAttributeInfoChangeSigntal MaxHealthChange;
};
