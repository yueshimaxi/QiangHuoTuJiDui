// Copyright 2022 bstt, Inc. All Rights Reserved.

#pragma once

enum CompleteActionType
{
	NONE,
	ARRANGE_SELECTED_NODES,
	ARRANGE_CONNECTED_NODES,
	ARRANGE_ALL_NODES,
};

/**
 * 
 */
class ANA_ReleaseNotifier
{
	ANA_ReleaseNotifier() = delete;
public:
	static void RegisterCheckVersion();
	static void CheckVersion();
	static void ShowNotification(CompleteActionType completedActionType_);
	static void CompleteNotification(CompleteActionType completedActionType_);

private:
	static void ShowArrangeSelectedNodesNotification();
	static void ShowArrangeConnectedNodesNotification();
	static void ShowArrangeAllNodesNotification();
	
	static TWeakPtr<SNotificationItem> releaseNotifPtr;
	static CompleteActionType completeActionType;
};
