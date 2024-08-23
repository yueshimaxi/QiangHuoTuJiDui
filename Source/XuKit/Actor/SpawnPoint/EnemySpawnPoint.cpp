#include "EnemySpawnPoint.h"
#include "Engine/StaticMeshActor.h"
#include "Kismet/GameplayStatics.h"
#include "XuKit/Character/EnemyCharacter.h"

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
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	GetWorld()->SpawnActor<AEnemyCharacter>(EnemyClass, GetActorTransform(), SpawnParams);
}
