// Fill out your copyright notice in the Description page of Project Settings.


#include "WaitCoolDownChange.h"

#include "AbilitySystemComponent.h"
#include "XuKit/XuBPFuncLib.h"

UWaitCoolDownChange* UWaitCoolDownChange::WaitForCoolDownChange(UAbilitySystemComponent* AbilitySystemComponent, FGameplayTag InCoolDownTag)
{
	UWaitCoolDownChange* WaitForCoolDownChange = NewObject<UWaitCoolDownChange>();
	WaitForCoolDownChange->ASC = AbilitySystemComponent;
	WaitForCoolDownChange->CoolDownTag = InCoolDownTag;

	if (!IsValid(AbilitySystemComponent) || !InCoolDownTag.IsValid())
	{
		WaitForCoolDownChange->EndTask();
		return nullptr;
	}
	XuPRINT(FString::Printf(TEXT("WaitForCoolDownChange %s"), *InCoolDownTag.ToString()));
	AbilitySystemComponent->RegisterGameplayTagEvent(InCoolDownTag, EGameplayTagEventType::NewOrRemoved).AddUObject(WaitForCoolDownChange, &UWaitCoolDownChange::OnGameplayTagChanged);
	return WaitForCoolDownChange;
}

void UWaitCoolDownChange::EndTask()
{
	if (IsValid(ASC) && CoolDownTag.IsValid())
	{
		ASC->RegisterGameplayTagEvent(CoolDownTag, EGameplayTagEventType::NewOrRemoved).RemoveAll(this);
	}
	SetReadyToDestroy();
	MarkAsGarbage();
}

void UWaitCoolDownChange::OnGameplayTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	if (CallbackTag.MatchesTag(CoolDownTag))
	{
		if (NewCount > 0)
		{
			float TimeRemaining = 0.f;
			float CooldownDuration = 0.f;
			if (GetCooldownRemainingForTag(CoolDownTag, TimeRemaining, CooldownDuration))
			{
				StartCoolDown.Broadcast(TimeRemaining);
			}
		}
		else
		{
			EndCoolDown.Broadcast(0);
			//EndTask();
		}
	}
	//XuPRINT(FString::Printf(TEXT("OnGameplayTagChanged %s %d"), *CallbackTag.ToString(), NewCount),true);
}


bool UWaitCoolDownChange::GetCooldownRemainingForTag(FGameplayTag local_CooldownTag, float& TimeRemaining, float& CooldownDuration)
{
	XuPRINT(FString::Printf(TEXT("GetCooldownRemainingForTag %s"), *local_CooldownTag.ToString()));
	bool tagIsValid = local_CooldownTag.IsValid();
	XuPRINT(FString::Printf(TEXT("tagIsValid %d"), tagIsValid));
	if (ASC && local_CooldownTag.IsValid())
	{
		TimeRemaining = 0.f;
		CooldownDuration = 0.f;

		FGameplayEffectQuery const Query = FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(local_CooldownTag.GetSingleTagContainer());
		TArray<TPair<float, float>> DurationAndTimeRemaining = ASC->GetActiveEffectsTimeRemainingAndDuration(Query);
		if (DurationAndTimeRemaining.Num() > 0)
		{
			int32 BestIdx = 0;
			float LongestTime = DurationAndTimeRemaining[0].Key;
			for (int32 Idx = 1; Idx < DurationAndTimeRemaining.Num(); ++Idx)
			{
				if (DurationAndTimeRemaining[Idx].Key > LongestTime)
				{
					LongestTime = DurationAndTimeRemaining[Idx].Key;
					BestIdx = Idx;
				}
			}

			TimeRemaining = DurationAndTimeRemaining[BestIdx].Key;
			CooldownDuration = DurationAndTimeRemaining[BestIdx].Value;

			return true;
		}
	}

	return false;
}
