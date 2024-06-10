#include "QHAbilitySystemGlobals.h"

#include "QHAbilityTypes.h"

FGameplayEffectContext* UQHAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	
	return new FQHGameplayEffectContext();

}
