#include "LevelManager.h"

void ULevelManager::Init()
{
	EntityManager = UEntityManager::GetInstance();
	EntityManager->Init();
}

void ULevelManager::GameOver()
{
}

void ULevelManager::GamePassed()
{
}
