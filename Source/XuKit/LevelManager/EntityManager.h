#pragma once
#include "CoreMinimal.h"
#include "EntityManager.generated.h"
UCLASS()
class UEntityManager : public UObject
{
	GENERATED_BODY()
public:
	static UEntityManager* Instance;
	static UEntityManager* GetInstance();
	void Init();
	
	
};