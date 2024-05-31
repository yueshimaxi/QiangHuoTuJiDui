// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineFriendsInterface.h"
#include "Interfaces/OnlineSessionDelegates.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "XuGI.generated.h"

USTRUCT(BlueprintType)
struct FCustomBlueprintSessionResult
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Blueprint Session Result")
	FString SessionName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Blueprint Session Result")
	bool bIsLan;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Blueprint Session Result")
	int32 CurrentNumberOfPlayers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Blueprint Session Result")
	int32 MaxNumberOfPlayers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Blueprint Session Result")
	bool bIsPasswordProtected;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Blueprint Session Result")
	FString SessionPassword;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Blueprint Session Result")
	int32 Ping;

	UPROPERTY()
	FString roomName;

	UPROPERTY()
	FString roomOwnerName;
};

UCLASS()
class UCustomBlueprintSessionResultData : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FCustomBlueprintSessionResult result;
};

USTRUCT(BlueprintType)
struct FBPUniqueNetId
{
	GENERATED_USTRUCT_BODY()

private:
	bool bUseDirectPointer;

public:
	TSharedPtr<const FUniqueNetId> UniqueNetId;
	const FUniqueNetId* UniqueNetIdPtr;

	void SetUniqueNetId(const TSharedPtr<const FUniqueNetId>& ID)
	{
		bUseDirectPointer = false;
		UniqueNetIdPtr = nullptr;
		UniqueNetId = ID;
	}

	void SetUniqueNetId(const FUniqueNetId* ID)
	{
		bUseDirectPointer = true;
		UniqueNetIdPtr = ID;
	}

	bool IsValid() const
	{
		if (bUseDirectPointer && UniqueNetIdPtr != nullptr)
		{
			return true;
		}
		else if (UniqueNetId.IsValid())
		{
			return true;
		}
		else
			return false;
	}

	const FUniqueNetId* GetUniqueNetId() const
	{
		if (bUseDirectPointer && UniqueNetIdPtr != nullptr)
		{
			// No longer converting to non const as all functions now pass const UniqueNetIds
			return /*const_cast<FUniqueNetId*>*/(UniqueNetIdPtr);
		}
		else if (UniqueNetId.IsValid())
		{
			return UniqueNetId.Get();
		}
		else
			return nullptr;
	}

	FBPUniqueNetId()
	{
		bUseDirectPointer = false;
		UniqueNetIdPtr = nullptr;
	}
};

#define SETTING_SERVER_NAME FName(TEXT("SERVERNAMEKEY"))
#define SETTING_SERVER_IS_PROTECTED FName(TEXT("SERVERSERVERISPASSWORDPROTECTEDKEY"))
#define SETTING_SERVER_PROTECT_PASSWORD FName(TEXT("SERVERPROTECTPASSWORDKEY"))

/**
 * 
 */
UCLASS()
class XUKIT_API UXuGI : public UGameInstance
{
	GENERATED_BODY()

public:
	UXuGI();

	virtual void Init() override;
	/** Delegate for searching for sessions */
	FOnFindSessionsCompleteDelegate OnFindSessionsCompleteDelegate;

	FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;

	FOnStartSessionCompleteDelegate OnStartSessionCompleteDelegate;

	FOnJoinSessionCompleteDelegate OnJoinSessionCompleteDelegate;

	FOnDestroySessionCompleteDelegate OnDestroySessionCompleteDelegate;

	FOnSessionInviteReceivedDelegate OnSessionInviteReceivedDelegate;

	FOnSessionUserInviteAcceptedDelegate OnSessionUserInviteAcceptedDelegate;

	FOnReadFriendsListComplete OnReadFriendsListCompleteDelegate;

	IOnlineSessionPtr SessionInterface;

	UFUNCTION(BlueprintCallable, Category = "Network|Sessions")
	void StartOnlineGame(FString roomName,FString roomOwnerName, int32 MaxNumPlayers, bool bIsLAN, bool bIsPresence = true, bool bIsPasswordProtected = false, FString SessionPassword = "");

	UFUNCTION(BlueprintCallable, Category = "Network|Sessions")
	void FindOnlineGames(bool bIsLAN, bool bIsPresence);

	UFUNCTION(BlueprintCallable, Category = "Network|Sessions")
	void JoinOnlineGame(int32 SessionIndex);

	UFUNCTION(BlueprintCallable, Category = "Network|Sessions")
	void DestroySessionAndLeaveGame();

	UFUNCTION(BlueprintCallable, Category = "Network|Friends")
	void SendSessionInviteToFriend(APlayerController* InvitingPlayer, const FBPUniqueNetId& Friend);

	
	TSharedPtr<class FOnlineSessionSettings> SessionSettings;

	TSharedPtr<class FOnlineSessionSearch> SessionSearch;

	int32 MaxPlayersinSession;

	UPROPERTY(EditDefaultsOnly, Category = "Maps")
	FName LobbyMapName=TEXT("LobbyMap");

	UPROPERTY(EditDefaultsOnly, Category = "Maps")
	FName MainMenuMap=TEXT("Login");

	UFUNCTION()
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);

	UFUNCTION()
	void OnStartOnlineGameComplete(FName SessionName, bool bWasSuccessful);

	UFUNCTION()
	void OnFindSessionsComplete(bool bWasSuccessful);

	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);

	void OnSessionInviteReceived(const FUniqueNetId& InvitedPlayer, const FUniqueNetId& FriendInviting, const FString& AppId, const FOnlineSessionSearchResult& SearchResult);

	void OnSessionUserInviteAccepted(bool bWasSuccessful, int32 LocalUserNum, FUniqueNetIdPtr InvitingPlayer, const FOnlineSessionSearchResult& TheSessionInvitedTo);
	
	void OnReadFriendsListComplete(int32 LocalUserNum, bool bWasSuccessful, const FString& ListName, const FString& ErrorString);


	virtual void Shutdown() override;

	
};
