// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "XuKit/AbilitySystem/AuraAbilityLibrary.h"
#include "XuKit/AbilitySystem/QHAbilitySystemComponent.h"
#include "XuKit/AbilitySystem/QHAttributeSet.h"
#include "XuKit/ActorComponent/EnemyHealthWidgetComponent.h"
#include "XuKit/AI/QHAIController.h"
#include "XuKit/UI/IUIBase/UIEnemyHealthBar.h"

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
	HealthBarWidgetComponent= CreateDefaultSubobject<UEnemyHealthWidgetComponent>(TEXT("HealthBarWidgetComponent"));
	HealthBarWidgetComponent->SetupAttachment(RootComponent);
	AutoPossessAI= EAutoPossessAI::PlacedInWorldOrSpawned;
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
	Cast<UQHAbilitySystemComponent>(qh_ability_system_component)->AbilitySystemComponentInfoSet();
	UQHAttributeSet* QH_AS = Cast<UQHAttributeSet>(GetAttributeSet());
	qh_ability_system_component->GetGameplayAttributeValueChangeDelegate(QH_AS->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& data)
		{
			HealthChange.Broadcast(data.NewValue);
		}
	);
	qh_ability_system_component->GetGameplayAttributeValueChangeDelegate(QH_AS->GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& data)
		{
			MaxHealthChange.Broadcast(data.NewValue);
		}
	);


	if (HasAuthority())
	{
		InitDefaultAttributesToSelf();
		AddCharactorAbilities();
	}
	
	if (HealthBarWidgetComponent->isInitWidgeted)
	{
		UUIEnemyHealthBar* health_bar= Cast<UUIEnemyHealthBar>(HealthBarWidgetComponent->GetWidget());
		health_bar->InitEnemyData(this);
	}else
	{
		HealthBarWidgetComponent->OnWidgetInit.BindLambda([&]()
		{
			UUIEnemyHealthBar* health_bar = Cast<UUIEnemyHealthBar>(HealthBarWidgetComponent->GetWidget());
			health_bar->InitEnemyData(this);
			HealthChange.Broadcast(QH_AS->GetHealth());
			MaxHealthChange.Broadcast(QH_AS->GetMaxHealth());
		});
	}

	
	HealthChange.Broadcast(QH_AS->GetHealth());
	MaxHealthChange.Broadcast(QH_AS->GetMaxHealth());
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

void AEnemyCharacter::InitDefaultAttributesToSelf()
{
	UAuraAbilityLibrary::InitDefaultAttributeActorInfo(this, GetPlayerLevel_Implementation(), CharactorClass, GetAbilitySystemComponent());
}


void AEnemyCharacter::SetCombatTarget_Implementation(AActor* CombatTarget)
{
	CombatTargetActor = CombatTarget;
}

AActor* AEnemyCharacter::GetCombatTarget_Implementation()
{
	return CombatTargetActor;
}

int AEnemyCharacter::GetPlayerLevel_Implementation()
{
	return PlayerLevel;
}

void AEnemyCharacter::AddCharactorAbilities()
{
	UAuraAbilityLibrary::GiveStartAbilities(this, GetPlayerLevel_Implementation(), CharactorClass, GetAbilitySystemComponent());

}
