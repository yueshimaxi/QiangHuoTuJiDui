#pragma once
#include "Blueprint/UserWidget.h"
#include "XuKit/UI/UIBase.h"
#include "UIGameLose.generated.h"
UCLASS()
class UUIGameLose :public UUIBase
{
	GENERATED_BODY()
public:
	virtual EUILayer GetUILayer() const override;
	virtual EUIType GetUIType() const override;
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
};
