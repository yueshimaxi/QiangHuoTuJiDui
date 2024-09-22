#pragma once
#include "CoreMinimal.h"
#include "EntityManager.h"
#include "LevelManager.generated.h"
UCLASS()
class ULevelManager : public UEngineSubsystem
{
public:
	UPROPERTY()
	UEntityManager* EntityManager;

	void Init();

	void 
	void GameOver();
	void GamePassed();

	
};
