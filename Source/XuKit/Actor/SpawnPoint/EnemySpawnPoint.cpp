#include "EnemySpawnPoint.h"

AEnemySpawnPoint::AEnemySpawnPoint()
{
	
}

void AEnemySpawnPoint::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemySpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemySpawnPoint::BeginDestroy()
{
	Super::BeginDestroy();
}

void AEnemySpawnPoint::SpawnEnemy(TSubclassOf<AEnemyCharacter> EnemyClass)
{
	
}
