// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "XuKit/AbilitySystem/QHAbilitySystemComponent.h"
#include "XuKit/AbilitySystem/QHAttributeSet.h"
#include "XuKit/AI/QHAIController.h"

AEnemyCharacter::AEnemyCharacter()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
 
	qh_ability_system_component = CreateDefaultSubobject<UQHAbilitySystemComponent>(TEXT("QHABS"));
	qh_ability_system_component->SetIsReplicated(true);
	qh_ability_system_component->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	qh_attribute_set = CreateDefaultSubobject<UQHAttributeSet>(TEXT("UAttributeSet"));
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo();
	GetCharacterMovement()->MaxWalkSpeed = bHitReact ? 0 : BaseWalkSpeed;

}



void AEnemyCharacter::InitAbilityActorInfo()
{
	qh_ability_system_component->InitAbilityActorInfo(this, this);
	

	
}

void AEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	AuraAIController = Cast<AQHAIController>(NewController);
	if (AuraAIController)
	{
		AuraAIController->GetBlackboardComponent()->InitializeBlackboard(*BlackboardData);
		AuraAIController->RunBehaviorTree(BehaviorTree);
		AuraAIController->GetBlackboardComponent()->SetValueAsBool(FName("IsHitReacting"), false);
		//AuraAIController->GetBlackboardComponent()->SetValueAsBool(FName("IsRanger"), CharactorClass != ECharactorClass::Warrior);
	}
}
