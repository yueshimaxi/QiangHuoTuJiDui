// Copyright Epic Games, Inc. All Rights Reserved.

#include "LyraTabButtonBase.h"

struct FSlateBrush;


void ULyraTabButtonBase::SetIconBrush(const FSlateBrush& Brush)
{
	// if (LazyImage_Icon)
	// {
	// 	LazyImage_Icon->SetBrush(Brush);
	// }
}

void ULyraTabButtonBase::SetTabLabelInfo_Implementation(const FLyraTabDescriptor& TabLabelInfo)
{
	SetButtonText(TabLabelInfo.TabText);
	SetIconBrush(TabLabelInfo.IconBrush);
}

