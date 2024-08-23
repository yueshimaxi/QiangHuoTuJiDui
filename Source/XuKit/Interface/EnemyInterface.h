// copyright xuzhipeng

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEnemyInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class XUKIT_API IEnemyInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// virtual void Highlight() =0;
	//
	// virtual void UnHighlight() =0;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "EnemyInterface")
	void SetCombatTarget(AActor* CombatTarget);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "EnemyInterface")
	AActor* GetCombatTarget();
};
