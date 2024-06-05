// Copyright 2022 bstt, Inc. All Rights Reserved.

#include "ANA_ReleaseNotifier.h"
#include "../Helpers/ANA_CacheHelper.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "../Debug/Log.h"
#include "Subsystems/AssetEditorSubsystem.h"

#define ANA_NEW_RELEASE_VERSION 411

TWeakPtr<SNotificationItem> ANA_ReleaseNotifier::releaseNotifPtr;
CompleteActionType ANA_ReleaseNotifier::completeActionType = CompleteActionType::NONE;

void ANA_ReleaseNotifier::RegisterCheckVersion()
{
	static FDelegateHandle onAssetEditorOpenedHandle;

	if (UAssetEditorSubsystem* assetEditorSubsystem = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>())
		onAssetEditorOpenedHandle = assetEditorSubsystem->OnAssetEditorOpened().AddLambda(
			[assetEditorSubsystem](UObject* Object)
			{
				ANA_ReleaseNotifier::CheckVersion();
				assetEditorSubsystem->OnAssetEditorOpened().Remove(onAssetEditorOpenedHandle);
			});
}

void ANA_ReleaseNotifier::CheckVersion()
{
	FANA_CacheData cacheData = ANA_CacheHelper::GetCacheData();

	if (cacheData.version >= ANA_NEW_RELEASE_VERSION) // if last tested version is anterior to current, reset the executionCount
		return;
	
	ShowNotification(CompleteActionType::ARRANGE_SELECTED_NODES);
}

void ANA_ReleaseNotifier::ShowArrangeSelectedNodesNotification()
{
	if (releaseNotifPtr.IsValid())
		return;
	FString message = FString("Auto Node Arranger\n\nNew Feature: Arrange ONLY Selected Nodes (1/3)");
	FString subText = FString("Step 1: Select multiple nodes\n"
		"Step 2: Use Arrange Command (Shift+Q for example)\n"
		"\n"
		"Only Selected Nodes are arranged");
	float widthOverride = 500.f; // 450.f

	FNotificationInfo releaseNotif(FText::FromString(message));
	releaseNotif.SubText = FText::FromString(subText);
	releaseNotif.WidthOverride = widthOverride;
	releaseNotif.bFireAndForget = false;

	releaseNotif.Hyperlink = FSimpleDelegate::CreateLambda([]() {
		const FString DocsURL = TEXT("https://github.com/bstt/AutoNodeArranger#what-is-new-");
	FPlatformProcess::LaunchURL(*DocsURL, nullptr, nullptr);
		});
	releaseNotif.HyperlinkText = FText::FromString("Go to Documentation...");

	releaseNotif.ButtonDetails.Add(FNotificationButtonInfo(FText::FromString("Dismiss"),
		FText::FromString("Dismiss"),
		FSimpleDelegate::CreateLambda([]() {
				releaseNotifPtr.Pin()->SetFadeOutDuration(1.5f);
				releaseNotifPtr.Pin()->ExpireAndFadeout();
				releaseNotifPtr.Pin()->SetCompletionState(SNotificationItem::ECompletionState::CS_None);
				releaseNotifPtr = nullptr;
				// update cache version
				FANA_CacheData cacheData = ANA_CacheHelper::GetCacheData();
				cacheData.version = ANA_NEW_RELEASE_VERSION;
				ANA_CacheHelper::SetCacheData(cacheData);
			}),
		SNotificationItem::ECompletionState::CS_Pending));

	releaseNotifPtr = FSlateNotificationManager::Get().AddNotification(releaseNotif);

	if (releaseNotifPtr.IsValid())
		releaseNotifPtr.Pin()->SetCompletionState(SNotificationItem::ECompletionState::CS_Pending);

	UE_LOG(LogAutoNodeArranger, Log, TEXT("%s\n%s"), *message, *subText);
}

void ANA_ReleaseNotifier::ShowArrangeConnectedNodesNotification()
{
	static FTimerHandle timerHandle;

	GEditor->GetTimerManager()->SetTimer(timerHandle, FTimerDelegate::CreateLambda([&]
	{
		FString message = FString("Auto Node Arranger\n\nNew Feature: Arrange Connected Nodes (2/3)");
		FString subText = FString("Step 1: Select only 1 node\n"
			"Step 2: Use any Arrange Command (Shift+Q for example)\n"
			"\n"
			"All Connected Nodes are arranged (as it was before)");

		releaseNotifPtr.Pin()->SetText(FText::FromString(message));
		releaseNotifPtr.Pin()->SetSubText(FText::FromString(subText));

		releaseNotifPtr.Pin()->SetCompletionState(SNotificationItem::ECompletionState::CS_Pending);

		UE_LOG(LogAutoNodeArranger, Log, TEXT("%s\n%s"), *message, *subText);

	}), 999.f, false, 1.f);
}


void ANA_ReleaseNotifier::ShowArrangeAllNodesNotification()
{
	static FTimerHandle timerHandle;

	GEditor->GetTimerManager()->SetTimer(timerHandle, FTimerDelegate::CreateLambda([&]
	{
		FString message = FString("Auto Node Arranger\n\nNew Feature: Arrange ALL Nodes (3/3)");
		FString subText = FString("Step 1: Select no node\n"
			"Step 2: Use any Arrange Command (Shift+Q for example)\n"
			"\n"
			"All Nodes are arranged");

		releaseNotifPtr.Pin()->SetText(FText::FromString(message));
		releaseNotifPtr.Pin()->SetSubText(FText::FromString(subText));

		releaseNotifPtr.Pin()->SetCompletionState(SNotificationItem::ECompletionState::CS_Pending);

		UE_LOG(LogAutoNodeArranger, Log, TEXT("%s\n%s"), *message, *subText);

	}), 999.f, false, 1.f);
}

void ANA_ReleaseNotifier::ShowNotification(CompleteActionType completeActionType_)
{
	completeActionType = completeActionType_;

	switch (completeActionType)
	{
	case NONE:
		break;
	case ARRANGE_SELECTED_NODES:
		ShowArrangeSelectedNodesNotification();
		break;
	case ARRANGE_CONNECTED_NODES:
		ShowArrangeConnectedNodesNotification();
		break;
	case ARRANGE_ALL_NODES:
		ShowArrangeAllNodesNotification();
		break;
	default:
		break;
	}
}

void ANA_ReleaseNotifier::CompleteNotification(CompleteActionType completeActionType_)
{
	if (completeActionType_ == completeActionType && releaseNotifPtr.IsValid())
	{
		releaseNotifPtr.Pin()->SetCompletionState(SNotificationItem::ECompletionState::CS_Success);

		switch (completeActionType)
		{
		case NONE:
			break;
		case ARRANGE_SELECTED_NODES:
			ShowNotification(CompleteActionType::ARRANGE_CONNECTED_NODES);
			break;
		case ARRANGE_CONNECTED_NODES:
			ShowNotification(CompleteActionType::ARRANGE_ALL_NODES);
			break;
		case ARRANGE_ALL_NODES:
		{
			releaseNotifPtr.Pin()->SetFadeOutDuration(2.f);
			releaseNotifPtr.Pin()->ExpireAndFadeout();
			completeActionType = CompleteActionType::NONE;
			releaseNotifPtr = nullptr;
			// update cache version
			FANA_CacheData cacheData = ANA_CacheHelper::GetCacheData();
			cacheData.version = ANA_NEW_RELEASE_VERSION;
			ANA_CacheHelper::SetCacheData(cacheData);
			break;
		}
		default:
			break;
		}
	}
}
