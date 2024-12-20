#pragma once

#include "CoreMinimal.h"
#include "EventMgr.generated.h"
DECLARE_DYNAMIC_DELEGATE_OneParam(FXuEventDelegate, UEventData*, EventData);
UENUM(BlueprintType)
enum class EXuEventType : uint8
{
	FirstEvent,
	FreshRoomList,
	FreshHUD,
	HealthChange,
	UpdateServerTime,
	OnUpdateStackUI,
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



UCLASS(BlueprintType)
class UEventContain : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	EXuEventType EventType;
	
	UPROPERTY()
	TMap<int, FXuEventDelegate> EventFuncMap;

	UPROPERTY()
	int EventIDCounter;

public:
	UFUNCTION(BlueprintCallable, Category = "Event")
	void BroadcastEvent(UEventData* EventData = nullptr);

	UFUNCTION(BlueprintCallable, Category = "Event")
	int AddEvent(FXuEventDelegate eventDelegate);

	UFUNCTION(BlueprintCallable, Category = "Event")
	void RemoveEvent(int EventID);
};

/**
 事件管理系统
 */
UCLASS()
class XUKIT_API UEventMgr : public UGameInstanceSubsystem
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TMap<EXuEventType, UEventContain*> EventDictionary;

public:
	UFUNCTION(BlueprintCallable, Category = "Event")
	void RegistEvent(EXuEventType EventType, int& EventID, FXuEventDelegate EventDelegate);

	UFUNCTION(BlueprintCallable, Category = "GlobalEventSystem")
	void RemoveEvent(EXuEventType EventType, int& EventID);

	UFUNCTION(BlueprintCallable, Category = "GlobalEventSystem")
	void BroadcastEvent(EXuEventType EventType, UEventData* EventData = nullptr);
};
