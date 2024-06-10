// copyright xuzhipeng

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "QHAbilitySystemGlobals.generated.h"

/**
 * 
 */
UCLASS()
class XUKIT_API UQHAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()

	virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;
};
