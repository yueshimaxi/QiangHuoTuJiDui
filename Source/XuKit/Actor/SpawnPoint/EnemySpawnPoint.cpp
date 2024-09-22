#include "EnemySpawnPoint.h"

#include "NavigationSystem.h"
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

bool AEnemySpawnPoint::SpawnEnemy(TSubclassOf<AEnemyCharacter> EnemyClass)
{
	FTransform SpawnTransform = GetActorTransform();
	FVector SpawnLocation = GetActorLocation();
	float SpawnRadius = 100.f;
	if (FindLocationToSpawnEnemy(SpawnLocation))
	{
		SpawnTransform.SetLocation(SpawnLocation);
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		GetWorld()->SpawnActor<AEnemyCharacter>(EnemyClass, SpawnTransform, SpawnParams);
		return true;
	}
	return false;
}

bool AEnemySpawnPoint::IsOccupied(float SpawnRadius)
{
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	return GetWorld()->OverlapAnyTestByChannel(GetActorLocation(), GetActorQuat(), ECollisionChannel::ECC_Pawn, FCollisionShape::MakeSphere(SpawnRadius), Params);
}

bool AEnemySpawnPoint::FindLocationToSpawnEnemy(FVector& location)
{
	UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
	if (NavSystem)
	{
		FNavLocation ResultLocation;
		if (NavSystem->GetRandomPointInNavigableRadius(GetActorLocation(), 1000.f, ResultLocation))
		{
			location = ResultLocation.Location;
			return true;
		}
	}
	return false;
}
