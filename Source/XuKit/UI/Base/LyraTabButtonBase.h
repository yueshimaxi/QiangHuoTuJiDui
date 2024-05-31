// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "LyraButtonBase.h"
#include "LyraTabListWidgetBase.h"
#include "LyraTabButtonBase.generated.h"

class UCommonLazyImage;
class UObject;
struct FFrame;
struct FSlateBrush;

UCLASS(Abstract, Blueprintable, meta = (DisableNativeTick))
class XUKIT_API ULyraTabButtonBase : public ULyraButtonBase, public ILyraTabButtonInterface
{
	GENERATED_BODY()

public:

	void SetIconBrush(const FSlateBrush& Brush);

protected:

	UFUNCTION()
	virtual void SetTabLabelInfo_Implementation(const FLyraTabDescriptor& TabLabelInfo) override;

private:


};
