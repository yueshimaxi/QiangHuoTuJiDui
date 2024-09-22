#include "EntityManager.h"

#include "XuKit/XuBPFuncLib.h"
UEntityManager* UEntityManager::Instance = nullptr;
UEntityManager* UEntityManager::GetInstance()
{
	if (Instance == nullptr)
	{
		Instance = NewObject<UEntityManager>();
	}
	return Instance;
}

void UEntityManager::Init()
{
	XuPRINT(TEXT("EntityManager Init"));
}
