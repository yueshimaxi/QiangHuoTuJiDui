// Fill out your copyright notice in the Description page of Project Settings.

#include "QHGameModeBase.h"
#include "XuKit/AbilitySystem/Data/EnemySpawnInfoAsset.h"

#include "Kismet/GameplayStatics.h"
#include "XuKit/Actor/SpawnPoint/EnemySpawnPoint.h"

void AQHGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> localEnemySpawnPoints;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemySpawnPoint::StaticClass(), localEnemySpawnPoints);
	for (auto element : localEnemySpawnPoints)
	{
		EnemySpawnPoints.Add(Cast<AEnemySpawnPoint>(element));
	}
}

void AQHGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	CurrentTime += DeltaSeconds;
	SpawnEnemy();
}

void AQHGameModeBase::SpawnEnemy()
{
	for (int i = 0; i < EnemySpawnInfoAsset->EnemySpawnInfos.Num() - 1; ++i)
	{
		FEnemySpawnInfo& info = EnemySpawnInfoAsset->EnemySpawnInfos[i];
		if (info.spawned)
		{
			continue;
		}
		if (CurrentTime >= info.time)
		{
			info.spawned = true;
			for (int j = 0; j < info.count - 1; ++j)
			{
				int32 index = FMath::RandRange(0, EnemySpawnPoints.Num() - 1);
				EnemySpawnPoints[index]->SpawnEnemy(info.EnemyClass);
			}
		}
	}
}
