#pragma once
#include "Engine/DataAsset.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EnemySpawnInfoAsset.generated.h"

UENUM()
enum class EMyEnum:uint8
{
	monster,
	miniBoss,
	boss
};

USTRUCT(Blueprintable, BlueprintType)
struct FEnemySpawnInfo
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float time;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AEnemyCharacter> EnemyClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 count;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EMyEnum enemyType;	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool spawned = false;
};

UCLASS()

class UEnemySpawnInfoAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemySpawnInfo")
	TArray<FEnemySpawnInfo> EnemySpawnInfos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemySpawnInfo")
	float SuccessTime;
};
