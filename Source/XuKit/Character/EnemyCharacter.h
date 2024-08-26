// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QHCharacterBase.h"
#include "XuKit/AbilitySystem/QHAttributeSet.h"
#include "XuKit/Interface/EnemyInterface.h"
#include "EnemyCharacter.generated.h"

class UEnemyHealthWidgetComponent;
/**
 * 
 */
UCLASS()
class XUKIT_API AEnemyCharacter : public AQHCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:
	
	AEnemyCharacter();

	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;


	//Charactor
	virtual void InitAbilityActorInfo() override;
	virtual void InitDefaultAttributesToSelf() override;
	virtual void AddCharactorAbilities() override;

	
	//icomabtinterface
	virtual void Die() override;
	virtual int GetPlayerLevel_Implementation() override;

	//IEnemyInterface
	virtual void SetCombatTarget_Implementation(AActor* CombatTarget) override;
	virtual AActor* GetCombatTarget_Implementation() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="AI")
	class UBehaviorTree* BehaviorTree;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="AI")
	class UBlackboardData* BlackboardData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="AI")
	class AQHAIController* AuraAIController ;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UEnemyHealthWidgetComponent* HealthBarWidgetComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CharactorInfo")
	int PlayerLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CharactorInfo")
	int BaseWalkSpeed=100;
	
	UPROPERTY()
	bool bHitReact;

	UPROPERTY(BlueprintAssignable)
	FAttributeInfoChangeSigntal HealthChange;
	UPROPERTY(BlueprintAssignable)
	FAttributeInfoChangeSigntal MaxHealthChange;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="AI")
	AActor* CombatTargetActor;


	float Lifespawn = 5;



};
