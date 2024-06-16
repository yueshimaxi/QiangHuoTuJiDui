// Fill out your copyright notice in the Description page of Project Settings.


#include "QHAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "QHAbilityBPLibrary.h"
#include "QHGameplayTags.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"
#include "XuKit/XuBPFuncLib.h"
#include "XuKit/Character/QHCharacterBase.h"
#include "XuKit/Interface/CombatInterface.h"
#include "XuKit/Interface/PlayerInterface.h"
#include "XuKit/PlayerController/QHPlayerController.h"

UQHAttributeSet::UQHAttributeSet()
{
}

void UQHAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UQHAttributeSet, Health, ELifetimeCondition::COND_None, ELifetimeRepNotifyCondition::REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UQHAttributeSet, MaxHealth, ELifetimeCondition::COND_None, ELifetimeRepNotifyCondition::REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UQHAttributeSet, Gold, ELifetimeCondition::COND_None, ELifetimeRepNotifyCondition::REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UQHAttributeSet, PisalReserveAmmo, ELifetimeCondition::COND_None, ELifetimeRepNotifyCondition::REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UQHAttributeSet, MaxPisalReserveAmmo, ELifetimeCondition::COND_None, ELifetimeRepNotifyCondition::REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UQHAttributeSet, RifleReserveAmmo, ELifetimeCondition::COND_None, ELifetimeRepNotifyCondition::REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UQHAttributeSet, MaxRifleReserveAmmo, ELifetimeCondition::COND_None, ELifetimeRepNotifyCondition::REPNOTIFY_Always);
	
}

void UQHAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}

void UQHAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties EffectProperties;
	SetEffectProperties(Data, EffectProperties);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
		XuPRINT(FString::Printf(TEXT("changeHealth on %s : Health:%f"),*EffectProperties.TargetAvaterActor->GetName(), GetHealth()));
	}


	if (Data.EvaluatedData.Attribute == GetIncomingDamageAttribute())
	{
		float newHealth = FMath::Max<float>(0, GetHealth() - GetIncomingDamage());
		SetHealth(newHealth);
		XuPRINT(FString::Printf(TEXT("changeHealth on %s : Health:%f"),*EffectProperties.TargetAvaterActor->GetName(), GetHealth()));

		bool isFaught = newHealth <= 0;
		if (isFaught)
		{
			if (ICombatInterface* combat_interface = Cast<ICombatInterface>(EffectProperties.TargetCharacter))
			{
				combat_interface->Die();
			}
			//SendXPEvent(EffectProperties);
		}
		else
		{
			FGameplayTagContainer tag_container;
			tag_container.AddTag(QHGameplayTags::Get().HitReactTag);
			EffectProperties.TargetASC->TryActivateAbilitiesByTag(tag_container);
		}
		bool isBlocked = UQHAbilityBPLibrary::IsBlockedHit(EffectProperties.EffectContextHandle);
		bool isCriticalHit = UQHAbilityBPLibrary::IsCriticalHit(EffectProperties.EffectContextHandle);
		ShowDamageText(EffectProperties, GetIncomingDamage(), isCriticalHit, isBlocked);
		SetIncomingDamage(0);
	}

	if (Data.EvaluatedData.Attribute == GetInComingXPAttribute())
	{
		int inComingXP = GetInComingXP();
		SetInComingXP(0);

		int CurrentLevel = ICombatInterface::Execute_GetPlayerLevel(EffectProperties.TargetCharacter);
		int CurrentXP = IPlayerInterface::Execute_GetXP(EffectProperties.TargetCharacter);
		int Newlevel = IPlayerInterface::Execute_FindLevelForXP(EffectProperties.TargetCharacter, CurrentXP + inComingXP);
		if (Newlevel > CurrentLevel)
		{
			IPlayerInterface::Execute_AddToLevel(EffectProperties.TargetCharacter, Newlevel - CurrentLevel);
			IPlayerInterface::Execute_LevelUp(EffectProperties.TargetCharacter);
			SetHealth(GetMaxHealth());
		}
		IPlayerInterface::Execute_AddXP(EffectProperties.TargetCharacter, inComingXP);
		XuPRINT(FString::Printf(TEXT("changeXP on %s : XP:%d"),*EffectProperties.TargetAvaterActor->GetName(), inComingXP));
	}
}


void UQHAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& EffectProperties)
{
	FGameplayEffectContextHandle Context = Data.EffectSpec.GetContext();
	UAbilitySystemComponent* SourceASC = Context.GetOriginalInstigatorAbilitySystemComponent();
	AController* SourceController = nullptr;
	ACharacter* SourceCharacter = nullptr;
	if (IsValid(SourceASC) && SourceASC->AbilityActorInfo.IsValid() && SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		AActor* Avatar = SourceASC->AbilityActorInfo->AvatarActor.Get();
		SourceController = SourceASC->AbilityActorInfo->PlayerController.Get();
		if (SourceController == nullptr && Avatar != nullptr)
		{
			if (APawn* Pawn = Cast<APawn>(Avatar))
			{
				SourceController = Cast<AController>(Pawn->GetController());
			}
		}

		if (SourceController != nullptr)
		{
			SourceCharacter = Cast<ACharacter>(SourceController->GetPawn());
			EffectProperties.SourceCharacter = SourceCharacter;
		}
	}
	EffectProperties.EffectContextHandle = Context;
	EffectProperties.SourceController = SourceController;
	EffectProperties.SourceCharacter = SourceCharacter;
	EffectProperties.SourceASC = SourceASC;
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		AActor* TargetAvatar = Data.Target.AbilityActorInfo->AvatarActor.Get();
		AController* TargetPC = Data.Target.AbilityActorInfo->PlayerController.Get();
		ACharacter* TargetCharacter = Cast<ACharacter>(TargetAvatar);
		UAbilitySystemComponent* TargetASC = Data.Target.AbilityActorInfo->AbilitySystemComponent.Get();
		EffectProperties.TargetAvaterActor = TargetAvatar;
		EffectProperties.TargetController = TargetPC;
		EffectProperties.TargetCharacter = TargetCharacter;
		EffectProperties.TargetASC = TargetASC;
	}
}

void UQHAttributeSet::ShowDamageText(FEffectProperties props, float damage, bool isCriticalHit, bool isBlockedHit) const
{
	if (props.SourceCharacter != props.TargetCharacter)
	{
		if (AQHPlayerController* pc = Cast<AQHPlayerController>(props.SourceCharacter->Controller))
		{
			pc->ShowDamageText(damage, props.TargetCharacter, isCriticalHit, isBlockedHit);
			return;
		}
		if (AQHPlayerController* pc = Cast<AQHPlayerController>(props.TargetCharacter->Controller))
		{
			pc->ShowDamageText(damage, props.TargetCharacter, isCriticalHit, isBlockedHit);
		}
	}
}

void UQHAttributeSet::SendXPEvent(FEffectProperties props)
{
	int targetPlayerLevel = ICombatInterface::Execute_GetPlayerLevel(props.TargetCharacter);
	ECharactorClass targetCharactorClass = ICombatInterface::Execute_GetCharactorClass(props.TargetCharacter);
	int RewardXP = UQHAbilityBPLibrary::GetRewardXPFromCharactorTypeAndLevel(GetWorld(), targetCharactorClass, targetPlayerLevel);
	FGameplayTag gameplaytag = QHGameplayTags::Get().Attributes_Meta_IncomingXPTag;
	FGameplayEventData eventData;
	eventData.EventTag = gameplaytag;
	eventData.EventMagnitude = RewardXP;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(props.SourceCharacter, gameplaytag, eventData);
}



void UQHAttributeSet::OnRep_Health(const FGameplayAttributeData& oldData) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UQHAttributeSet, Health, oldData);
}

void UQHAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& oldData) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UQHAttributeSet, MaxHealth, oldData);
}

void UQHAttributeSet::OnRep_PisalReserveAmmo(const FGameplayAttributeData& oldData) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UQHAttributeSet, PisalReserveAmmo, oldData);
}

void UQHAttributeSet::OnRep_MaxPisalReserveAmmo(const FGameplayAttributeData& oldData) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UQHAttributeSet, MaxPisalReserveAmmo, oldData);
}

void UQHAttributeSet::OnRep_RifleReserveAmmo(const FGameplayAttributeData& oldData) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UQHAttributeSet, RifleReserveAmmo, oldData);
}

void UQHAttributeSet::OnRep_MaxRifleReserveAmmo(const FGameplayAttributeData& oldData) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UQHAttributeSet, MaxRifleReserveAmmo, oldData);
}

void UQHAttributeSet::OnRep_Gold(const FGameplayAttributeData& oldData) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UQHAttributeSet, Gold, oldData);
}

