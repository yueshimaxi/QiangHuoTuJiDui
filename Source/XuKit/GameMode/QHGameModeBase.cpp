// Fill out your copyright notice in the Description page of Project Settings.

#include "QHGameModeBase.h"
#include "XuKit/AbilitySystem/Data/EnemySpawnInfoAsset.h"

#include "Kismet/GameplayStatics.h"
#include "XuKit/XuBPFuncLib.h"
#include "XuKit/Actor/SpawnPoint/EnemySpawnPoint.h"
#include "XuKit/Character/EnemyCharacter.h"
#include "XuKit/Character/PlayerCharacter.h"
#include "XuKit/PlayerController/QHPlayerController.h"
#include "XuKit/PlayerState/QHPlayerState.h"

FTimerHandle UpdateTimeTimerHandle;

void AQHGameModeBase::BeginPlay()
{
	Super::BeginPlay();


	InitSpawnPointData();

	GetWorld()->GetTimerManager().SetTimer(UpdateTimeTimerHandle, this, &AQHGameModeBase::SyncTimeToAllClient, 1.0f, true);
}

void AQHGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (bGameEnd)
	{
		return;
	}
	CurrentTime += DeltaSeconds;
	SpawnEnemy();


	//check TimeOut
	if (CurrentTime > SuccessTime)
	{
		GameWin();
	}

	if (!CheckHasAlivePlayer())
	{
		GameLose();
	}
}

void AQHGameModeBase::InitSpawnPointData()
{
	TArray<AActor*> localEnemySpawnPoints;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemySpawnPoint::StaticClass(), localEnemySpawnPoints);
	for (auto element : localEnemySpawnPoints)
	{
		EnemySpawnPoints.Add(Cast<AEnemySpawnPoint>(element));
	}
	for (int i = 0; i < EnemySpawnInfoAsset->EnemySpawnInfos.Num(); ++i)
	{
		EnemySpawnInfoAsset->EnemySpawnInfos[i].spawned = false;
	}
	SuccessTime = EnemySpawnInfoAsset->SuccessTime;
}

void AQHGameModeBase::SpawnEnemy()
{
	for (int i = 0; i < EnemySpawnInfoAsset->EnemySpawnInfos.Num(); ++i)
	{
		FEnemySpawnInfo& info = EnemySpawnInfoAsset->EnemySpawnInfos[i];
		if (info.spawned)
		{
			continue;
		}
		if (CurrentTime < info.time)
		{
			continue;
		}
		for (int j = 0; j < info.count; ++j)
		{
			ReadSpawnEnemy.Add(info.EnemyClass);
		}
		info.spawned = true;
	}

	TArray<UClass*> newReadSpawnEnemy;
	for (int i = 0; i < ReadSpawnEnemy.Num(); ++i)
	{
		int32 index = FMath::RandRange(0, EnemySpawnPoints.Num() - 1);
		if (!EnemySpawnPoints[index]->SpawnEnemy(ReadSpawnEnemy[i]))
		{
			newReadSpawnEnemy.Add(ReadSpawnEnemy[i]);
		}
	}
	ReadSpawnEnemy = newReadSpawnEnemy;

	//spawn monster
	//spawn miniBoss
	//spawn boss
}

bool AQHGameModeBase::CheckHasAlivePlayer()
{
	//check all player alive
	TArray<APlayerCharacter*> players;
	TArray<AActor*> localPlayers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerCharacter::StaticClass(), localPlayers);
	for (auto element : localPlayers)
	{
		APlayerCharacter* player = Cast<APlayerCharacter>(element);
		if (!ICombatInterface::Execute_IsDead(player))
		{
			return true;
		}
	}
	return false;
}

void AQHGameModeBase::GameLose()
{
	XuPRINT("GameLose");

	AQHPlayerController* aqh_player_controller = Cast<AQHPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	aqh_player_controller->GameLose();
	bGameEnd = true;
}

void AQHGameModeBase::GameWin()
{
	XuPRINT("GameWin");

	AQHPlayerController* aqh_player_controller = Cast<AQHPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	aqh_player_controller->GameWin();
	bGameEnd = true;

}

void AQHGameModeBase::SyncTimeToAllClient()
{
	//sync time to all client

	AQHPlayerState* aqh_player_state = Cast<AQHPlayerState>(UGameplayStatics::GetPlayerState(GetWorld(), 0));
	if (aqh_player_state)
	{
		aqh_player_state->MulticastSyncTime(CurrentTime);
	}
}
