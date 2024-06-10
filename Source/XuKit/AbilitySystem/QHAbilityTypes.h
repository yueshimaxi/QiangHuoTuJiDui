#pragma once

#include "GameplayEffectTypes.h"
#include "QHAbilityTypes.generated.h"

USTRUCT(BlueprintType)
struct  FQHGameplayEffectContext :public FGameplayEffectContext
{
	GENERATED_BODY()
public:
	virtual UScriptStruct* GetScriptStruct() const override
	{
		return FGameplayEffectContext::StaticStruct();
	}

	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess) override;

	bool isBlockedHit() const { return bIsBlockedHit; }
	bool isCriticalHit() const { return bIsCriticalHit; }
	void setBlockedHit(bool b) { bIsBlockedHit = b; }
	void setCriticalHit(bool b) { bIsCriticalHit = b; }
protected:
	UPROPERTY()
	bool bIsBlockedHit = false;
	UPROPERTY()
	bool bIsCriticalHit = false;



};
template<>
struct TStructOpsTypeTraits<FQHGameplayEffectContext> : public TStructOpsTypeTraitsBase2<FQHGameplayEffectContext>
{
	enum
	{
		WithNetSerializer = true,
		withcopy = true,
	};
};