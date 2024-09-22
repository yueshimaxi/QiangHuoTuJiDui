// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "QHGameModeBase.generated.h"

class AEnemySpawnPoint;
class UEnemySpawnInfoAsset;
class UWeaponInfoDataAsset;
class UCharactorClassInfo;
/**
 * 
 */
UCLASS()
class XUKIT_API AQHGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="AInitInfo")
	TObjectPtr<UCharactorClassInfo> EnemyInitDataAsset;


	UPROPERTY(EditAnywhere, Category="AInitInfo")
	TObjectPtr<UEnemySpawnInfoAsset> EnemySpawnInfoAsset;


	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;


	UPROPERTY(EditAnywhere)
	TArray<AEnemySpawnPoint*> EnemySpawnPoints;
	UPROPERTY(EditAnywhere)
	TArray<UClass*> ReadSpawnEnemy;

	bool bGameEnd = false;

	UPROPERTY(EditAnywhere)
	float CurrentTime;
	UPROPERTY(EditAnywhere)
	float SuccessTime;

	UPROPERTY(EditAnywhere)
	float SpawnRidus;

	void InitSpawnPointData();

	void SpawnEnemy();

	bool CheckHasAlivePlayer();
	void GameLose();
	void GameWin();
};
