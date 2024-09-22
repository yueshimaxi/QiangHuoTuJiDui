#pragma once
#include "CoreMinimal.h"
#include "EntityManager.h"
#include "LevelManager.generated.h"
UCLASS()
class ULevelManager : public UEngineSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY()
	UEntityManager* EntityManager;

	void Init();


	void GameOver();
	void GamePassed();

	
};
