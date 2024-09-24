#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "QHGameState.generated.h"

UCLASS()
class XUKIT_API AQHGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	float CurrentServerTime;
	UFUNCTION(NetMulticast,Reliable)
	void MulticastSyncTime(float time);
};
