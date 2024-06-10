// copyright xuzhipeng

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "DamageTextWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class XUKIT_API UDamageTextWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintImplementableEvent)
	void SetDamageText(float damage, bool isCriticalHit, bool isBlockedHit);
};
