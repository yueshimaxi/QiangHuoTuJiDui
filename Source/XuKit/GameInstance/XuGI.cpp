// Fill out your copyright notice in the Description page of Project Settings.


#include "XuKit/GameInstance/XuGI.h"

#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "XuKit/XuBPFuncLib.h"
#include "XuKit/Event/EventMgr.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Online/OnlineSessionNames.h"
#include "XuKit/Event/EventDataDefine.h"


UXuGI::UXuGI()
{
	OnCreateSessionCompleteDelegate.BindUObject(this, &UXuGI::OnCreateSessionComplete);

	OnStartSessionCompleteDelegate.BindUObject(this, &UXuGI::OnStartOnlineGameComplete);

	OnFindSessionsCompleteDelegate.BindUObject(this, &UXuGI::OnFindSessionsComplete);

	OnJoinSessionCompleteDelegate.BindUObject(this, &UXuGI::OnJoinSessionComplete);

	OnDestroySessionCompleteDelegate.BindUObject(this, &UXuGI::OnDestroySessionComplete);

	OnSessionInviteReceivedDelegate.BindUObject(this, &UXuGI::OnSessionInviteReceived);

	OnSessionUserInviteAcceptedDelegate.BindUObject(this, &UXuGI::OnSessionUserInviteAccepted);

	OnReadFriendsListCompleteDelegate.BindUObject(this, &UXuGI::OnReadFriendsListComplete);
}

void UXuGI::Init()
{
	Super::Init();
	if (IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get())
	{
		SessionInterface = OnlineSub->GetSessionInterface();
		if (SessionInterface)
		{
			SessionInterface->AddOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegate);
			SessionInterface->AddOnStartSessionCompleteDelegate_Handle(OnStartSessionCompleteDelegate);
			SessionInterface->AddOnFindSessionsCompleteDelegate_Handle(OnFindSessionsCompleteDelegate);
			SessionInterface->AddOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegate);
			SessionInterface->AddOnDestroySessionCompleteDelegate_Handle(OnDestroySessionCompleteDelegate);
			SessionInterface->AddOnSessionInviteReceivedDelegate_Handle(OnSessionInviteReceivedDelegate);
			SessionInterface->AddOnSessionUserInviteAcceptedDelegate_Handle(OnSessionUserInviteAcceptedDelegate);
		}
	}
}

void UXuGI::StartOnlineGame(FString roomName, FString roomOwnerName, int32 MaxNumPlayers, bool bIsLAN, bool bIsPresence, bool bIsPasswordProtected, FString SessionPassword)
{
	if (SessionInterface.IsValid())
	{
		if (SessionInterface->GetNamedSession(NAME_GameSession))
		{
			SessionInterface->DestroySession(NAME_GameSession);
		}
		SessionSettings = MakeShareable(new FOnlineSessionSettings());
		SessionSettings->bIsLANMatch = bIsLAN;
		SessionSettings->bUsesPresence = bIsPresence;
		SessionSettings->NumPublicConnections = MaxNumPlayers;
		MaxPlayersinSession = MaxNumPlayers;
		SessionSettings->NumPrivateConnections = 0;
		SessionSettings->bAllowInvites = true;
		SessionSettings->bAllowJoinInProgress = true;
		SessionSettings->bShouldAdvertise = true;
		SessionSettings->bAllowJoinViaPresence = true;
		SessionSettings->bAllowJoinViaPresenceFriendsOnly = false;
		SessionSettings->bUseLobbiesIfAvailable = true;
		SessionSettings->bIsDedicated = false;
		SessionSettings->Set(FName("roomName"), roomName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
		SessionSettings->Set(FName("roomOwnerName"), roomOwnerName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

		SessionInterface->CreateSession(*GetFirstGamePlayer()->GetPreferredUniqueNetId(), NAME_GameSession, *SessionSettings);
	}
}

void UXuGI::FindOnlineGames(bool bIsLAN, bool bIsPresence)
{
	ULocalPlayer* const Player = GetFirstGamePlayer();

	FUniqueNetIdPtr UserId = Player->GetPreferredUniqueNetId().GetUniqueNetId();
	if (SessionInterface.IsValid() && UserId.IsValid())
	{
		SessionSearch = MakeShareable(new FOnlineSessionSearch());
		SessionSearch->bIsLanQuery = bIsLAN;
		SessionSearch->MaxSearchResults = 1000;
		SessionSearch->PingBucketSize = 1000;
		// We only want to set this Query Setting if "bIsPresence" is true
		if (bIsPresence)
		{
			SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, bIsPresence, EOnlineComparisonOp::Equals);
		}
		TSharedRef<FOnlineSessionSearch> SearchSettingsRef = SessionSearch.ToSharedRef();

		SessionInterface->FindSessions(*Player->GetPreferredUniqueNetId(), SearchSettingsRef);
	}
	else
	{
		OnFindSessionsComplete(false);
	}
}

void UXuGI::JoinOnlineGame(int32 SessionIndex)
{
	FOnlineSessionSearchResult SearchResult = SessionSearch->SearchResults[SessionIndex];

	SessionInterface->JoinSession(*GetFirstGamePlayer()->GetPreferredUniqueNetId(), NAME_GameSession, SearchResult);
}

void UXuGI::DestroySessionAndLeaveGame()
{
	if (SessionInterface.IsValid())
	{
		SessionInterface->DestroySession(NAME_GameSession);
	}
}

void UXuGI::SendSessionInviteToFriend(APlayerController* InvitingPlayer, const FBPUniqueNetId& Friend)
{
}


void UXuGI::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	XuPRINT(TEXT("OnCreateSessionComplete")+bWasSuccessful?TEXT("true"):TEXT("false"));
	if (bWasSuccessful)
	{
		SessionInterface->StartSession(SessionName);
	}
}

void UXuGI::OnStartOnlineGameComplete(FName SessionName, bool bWasSuccessful)
{
	XuPRINT(TEXT("OnStartOnlineGameComplete")+bWasSuccessful?TEXT("true"):TEXT("false"));
	if (bWasSuccessful)
	{
		//GetWorld()->ServerTravel(TEXT("/Game/ThirdPerson/Maps/ThirdPersonMap?Listen"));
		UGameplayStatics::OpenLevel(GetWorld(), LobbyMapName, true, "Listen");
	}
}

void UXuGI::OnFindSessionsComplete(bool bWasSuccessful)
{
	XuPRINT(TEXT("OnFindSessionsComplete：")+bWasSuccessful?TEXT("true"):TEXT("false"));

	if (!bWasSuccessful)
	{
		return;
	}
	if (SessionInterface.IsValid())
	{
		TArray<FCustomBlueprintSessionResult> CustomSessionResults;
		XuPRINT(FString::Printf(TEXT("find session complete result num is %d"),SessionSearch->SearchResults.Num()));
		// If we have found at least 1 session, we just going to debug them. You could add them to a list of UMG Widgets, like it is done in the BP version!
		if (SessionSearch->SearchResults.Num() > 0)
		{
			for (int32 SearchIdx = 0; SearchIdx < SessionSearch->SearchResults.Num(); SearchIdx++)
			{
				FCustomBlueprintSessionResult TempCustomSeesionResult;
				TempCustomSeesionResult.bIsLan = SessionSearch->SearchResults[SearchIdx].Session.SessionSettings.bIsLANMatch;
				TempCustomSeesionResult.CurrentNumberOfPlayers = SessionSearch->SearchResults[SearchIdx].Session.SessionSettings.NumPublicConnections - SessionSearch->
					SearchResults[SearchIdx].Session.NumOpenPublicConnections;
				TempCustomSeesionResult.MaxNumberOfPlayers = SessionSearch->SearchResults[SearchIdx].Session.SessionSettings.NumPublicConnections;
				TempCustomSeesionResult.Ping = SessionSearch->SearchResults[SearchIdx].PingInMs;
				FString roomName = TEXT("default");
				SessionSearch->SearchResults[SearchIdx].Session.SessionSettings.Get(FName("roomName"), roomName);
				TempCustomSeesionResult.roomName = roomName;

				FString roomOwnerName = TEXT("default");
				SessionSearch->SearchResults[SearchIdx].Session.SessionSettings.Get(FName("roomOwnerName"), roomOwnerName);
				TempCustomSeesionResult.roomOwnerName = roomOwnerName;

				// SessionSearch->SearchResults[SearchIdx].Session.SessionSettings.Get(SETTING_SERVER_NAME, TempCustomSeesionResult.SessionName);
				//
				// // get if the server is password protected
				// SessionSearch->SearchResults[SearchIdx].Session.SessionSettings.Get(SETTING_SERVER_IS_PROTECTED, TempCustomSeesionResult.bIsPasswordProtected);
				//
				//
				// // get the Password if the session is Password Protected
				// if (TempCustomSeesionResult.bIsPasswordProtected)
				// 	SessionSearch->SearchResults[SearchIdx].Session.SessionSettings.Get(SETTING_SERVER_PROTECT_PASSWORD, TempCustomSeesionResult.SessionPassword);


				CustomSessionResults.Add(TempCustomSeesionResult);
			}
		}

		//call UMG to show sessions after the search ends
		UFreshRoomListEventData* fresh_room_list_event_data = NewObject<UFreshRoomListEventData>();
		for (auto custom_session_result : CustomSessionResults)
		{
			UCustomBlueprintSessionResultData* resultData = NewObject<UCustomBlueprintSessionResultData>();
			resultData->result = custom_session_result;
			fresh_room_list_event_data->roomListData.Add(resultData);
			XuPRINT(
				FString::Printf(TEXT("custom_session_result.SessionName:%s,playerNum:%d,maxplayerNum:%d,ping:%d"),*custom_session_result.SessionName,custom_session_result.
					CurrentNumberOfPlayers,custom_session_result.MaxNumberOfPlayers,custom_session_result.Ping ));
		}


		UXuBPFuncLib::GetEventManager(GetWorld())->BroadcastEvent(EXuEventType::FreshRoomList, fresh_room_list_event_data);
	}
}

void UXuGI::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	XuPRINT(*SessionName.ToString());

	if (SessionInterface.IsValid())
	{
		APlayerController* const PlayerController = GetFirstLocalPlayerController();
		
		FString TravelURL;
		if (PlayerController && SessionInterface->GetResolvedConnectString(NAME_GameSession, TravelURL))
		{
			// Finally call the ClientTravel. If you want, you could print the TravelURL to see
			// how it really looks like
			XuPRINT(TEXT("TravelURL:")+TravelURL);
			PlayerController->ClientTravel(TravelURL, ETravelType::TRAVEL_Absolute);
		}
	}
}

void UXuGI::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (SessionInterface.IsValid())
	{
		// If it was successful, we just load another level (could be a MainMenu!)
		if (bWasSuccessful)
		{
			UGameplayStatics::OpenLevel(GetWorld(), MainMenuMap, true);
		}
	}
}

void UXuGI::OnSessionInviteReceived(const FUniqueNetId& InvitedPlayer, const FUniqueNetId& FriendInviting, const FString& AppId,
                                    const FOnlineSessionSearchResult& SearchResult)
{
}

void UXuGI::OnSessionUserInviteAccepted(bool bWasSuccessful, int32 LocalUserNum, FUniqueNetIdPtr InvitingPlayer, const FOnlineSessionSearchResult& TheSessionInvitedTo)
{
	if (bWasSuccessful)
	{
		if (TheSessionInvitedTo.IsValid())
		{
			//JoinASession(LocalUserNum, NAME_GameSession, TheSessionInvitedTo);
		}
	}
}


void UXuGI::OnReadFriendsListComplete(int32 LocalUserNum, bool bWasSuccessful, const FString& ListName, const FString& ErrorString)
{
}

void UXuGI::Shutdown()
{
	Super::Shutdown();

	if (SessionInterface.IsValid())
	{
		// 获取当前会话（如果有的话）
		if (FNamedOnlineSession* Named_Session = SessionInterface->GetNamedSession(NAME_GameSession))
		{
			// 关闭会话
			SessionInterface->DestroySession(NAME_GameSession);
		}
	}
}
