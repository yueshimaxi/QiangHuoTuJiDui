
#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "TargetDataTask.h"
#include "SwapweaponDirTargetDataTask.generated.h"


/**
 * 
 */
UCLASS()
class XUKIT_API USwapweaponDirTargetDataTask : public UAbilityTask
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static USwapweaponDirTargetDataTask* CreateSwapweaponDirTargetDataTask(UGameplayAbility* OwningAbility);


	virtual void Activate() override;
	UPROPERTY(BlueprintAssignable)
	FTargetDataSignature ValidData;

	void SendSwapWeaponDirData();

	void OnSwapWeaponDirDataReplicatedCallBack(const FGameplayAbilityTargetDataHandle& Data, FGameplayTag ActivationTag);
};
