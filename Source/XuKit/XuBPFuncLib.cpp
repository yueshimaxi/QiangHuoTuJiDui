#include "XuBPFuncLib.h"

#include "Data/DataMgr.h"
#include "Event/EventMgr.h"
#include "Kismet/GameplayStatics.h"
#include "UI/UIMgr.h"

AActor* UXuBPFuncLib::GetActorByClassAndTag(UObject* WorldContextObject, TSubclassOf<AActor> actor, FString name)
{
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClassWithTag(WorldContextObject, actor, FName(name), actors);
	for (int i = 0; i < actors.Num(); ++i)
	{
		return actors[i];
	}
	FString content = WorldContextObject ? TEXT("is") : TEXT("not");
	XuPRINT(FString::Printf( TEXT("Find obj:%s is null ; WorldContextObject %s exist"),*name,*content));
	return nullptr;
}

UUIMgr* UXuBPFuncLib::GetUIManager(UObject* WorldContextObject)
{
	
	UUIMgr* uiMgr = nullptr;
	if (WorldContextObject)
	{
		UGameInstance* gameInstance = UGameplayStatics::GetGameInstance(WorldContextObject);
		if (gameInstance)
		{
			uiMgr = Cast<UUIMgr>(gameInstance->GetSubsystem<UUIMgr>());
		}
	}
	return uiMgr;
}

UDataMgr* UXuBPFuncLib::GetDataManager(UObject* WorldContextObject)
{
	UDataMgr* dataMgr = nullptr;
	if (WorldContextObject)
	{
		UGameInstance* gameInstance = UGameplayStatics::GetGameInstance(WorldContextObject);
		if (gameInstance)
		{
			dataMgr = Cast<UDataMgr>(gameInstance->GetSubsystem<UDataMgr>());
		}
	}
	return dataMgr;
}

UEventMgr* UXuBPFuncLib::GetEventManager(UObject* WorldContextObject)
{
	UEventMgr* eventMgr = nullptr;
	if (WorldContextObject)
	{
		UGameInstance* gameInstance = UGameplayStatics::GetGameInstance(WorldContextObject);
		if (gameInstance)
		{
			eventMgr = Cast<UEventMgr>(gameInstance->GetSubsystem<UEventMgr>());
		}
	}
	return eventMgr;
}
