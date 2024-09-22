#pragma once

class EnemySpawnPoint
{
public:
	
};
#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EnemySpawnPoint.generated.h"

UCLASS()
class AEnemySpawnPoint : public AActor
{
	GENERATED_BODY()
public:
	AEnemySpawnPoint();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void BeginDestroy() override;



	bool SpawnEnemy(TSubclassOf<class AEnemyCharacter> EnemyClass);
private:
	bool IsOccupied(float SpawnRadius);

	bool FindLocationToSpawnEnemy(FVector& location);
};
