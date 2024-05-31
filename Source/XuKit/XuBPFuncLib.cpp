#include "XuBPFuncLib.h"

#include "Kismet/GameplayStatics.h"

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
