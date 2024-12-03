#pragma once
#include "Blueprint/UserWidget.h"
#include "XuKit/UI/UIBase.h"
#include "UIGameWin.generated.h"
UCLASS()
class UUIGameWin : public UUIBase
{
	GENERATED_BODY()
public:
	virtual EUILayer GetUILayer() const override;
	virtual EUIType GetUIType() const override;
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
};
