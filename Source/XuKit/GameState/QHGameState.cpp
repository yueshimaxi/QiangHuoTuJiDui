#include "QHGameState.h"

#include "XuKit/XuBPFuncLib.h"
#include "XuKit/Event/EventDataDefine.h"

void AQHGameState::MulticastSyncTime_Implementation(float time)
{
	CurrentServerTime = time;
	ENetRole role = GetLocalRole();
	FString roleStr=UXuBPFuncLib::EnumToFString<ENetRole>(TEXT("ENetRole"),role);
	//XuPRINT(FString::Printf(TEXT("roleStr:%s ,currentTime:%f"), *roleStr, CurrentServerTime));
	UUpdateSeverTimeEventData* updateSeverTimeEventData = NewObject<UUpdateSeverTimeEventData>();
	updateSeverTimeEventData->serverTime = CurrentServerTime;
	UXuBPFuncLib::GetEventManager(this)->BroadcastEvent(EXuEventType::UpdateServerTime,updateSeverTimeEventData);
}
