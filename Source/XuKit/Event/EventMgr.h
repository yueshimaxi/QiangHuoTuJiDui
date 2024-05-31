#pragma once

#include "CoreMinimal.h"
#include "EventMgr.generated.h"

UENUM(BlueprintType)
enum class EXuEventType : uint8
{
	FirstEvent,
	FreshRoomList,
	DefaultEvent = FirstEvent
};

UCLASS(BlueprintType)
class UEventData : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual EXuEventType GetEventType();
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FEventDelegate, UEventData*, EventData);

UCLASS(BlueprintType)
class UEventContain : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	EXuEventType EventType;
	
	UPROPERTY()
	TMap<int, FEventDelegate> EventFuncMap;

	UPROPERTY()
	int EventIDCounter;

public:
	UFUNCTION(BlueprintCallable, Category = "Event")
	void BroadcastEvent(UEventData* EventData = nullptr);

	UFUNCTION(BlueprintCallable, Category = "Event")
	int AddEvent(FEventDelegate eventDelegate);

	UFUNCTION(BlueprintCallable, Category = "Event")
	void RemoveEvent(int EventID);
};

/**
 事件管理系统
 */
UCLASS()
class XUKIT_API UEventMgr : public UWorldSubsystem
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TMap<EXuEventType, UEventContain*> EventDictionary;

public:
	UFUNCTION(BlueprintCallable, Category = "GlobalEventSystem")
	void RegistEvent(EXuEventType EventType, int& EventID, FEventDelegate EventDelegate);

	UFUNCTION(BlueprintCallable, Category = "GlobalEventSystem")
	void RemoveEvent(EXuEventType EventType, int& EventID);

	UFUNCTION(BlueprintCallable, Category = "GlobalEventSystem")
	void BroadcastEvent(EXuEventType EventType, UEventData* EventData = nullptr);
};
