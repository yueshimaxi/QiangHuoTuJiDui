// Fill out your copyright notice in the Description page of Project Settings.


#include "EventMgr.h"

EXuEventType UEventData::GetEventType()
{
	return EXuEventType::FirstEvent;
}

void UEventContain::BroadcastEvent(UEventData* EventData)
{ 
	TArray<int> keys;
	EventFuncMap.GetKeys(keys);
	for (int i = keys.Num() - 1; i >= 0; i--)
	{
		if (EventFuncMap[keys[i]].IsBound())
		{
			EventFuncMap[keys[i]].Execute(EventData);
		}
	}
}

int UEventContain::AddEvent(FXuEventDelegate eventDelegate)
{
	int EventId = ++EventIDCounter;
	EventFuncMap.Add(EventId, eventDelegate);
	return EventId;
}

void UEventContain::RemoveEvent(int EventID)
{
	EventFuncMap.Remove(EventID);
}

void UEventMgr::RegistEvent(EXuEventType EventType, int& EventID, FXuEventDelegate EventDelegate)
{
	if (!EventDictionary.Contains(EventType))
	{
		UEventContain* event_contain = NewObject<UEventContain>();
		event_contain->EventType = EventType;
		EventDictionary.Add(EventType, event_contain);
	}

	EventID = EventDictionary[EventType]->AddEvent(EventDelegate);
}

void UEventMgr::RemoveEvent(EXuEventType EventType, int& EventID)
{
	if (UEventContain** EventContain = EventDictionary.Find(EventType))
	{
		(*EventContain)->RemoveEvent(EventID);
	}
	EventID = 0;
}

void UEventMgr::BroadcastEvent(EXuEventType EventType, UEventData* EventData)
{
	if (UEventContain** EventContain = EventDictionary.Find(EventType))
	{
		(*EventContain)->BroadcastEvent(EventData);
	}
}
