// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "XuKit/AbilitySystem/QHAbilitySystemComponent.h"
#include "XuKit/AbilitySystem/QHAttributeSet.h"

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
}



void AEnemyCharacter::InitAbilityActorInfo()
{
	qh_ability_system_component->InitAbilityActorInfo(this, this);
	

	
}
