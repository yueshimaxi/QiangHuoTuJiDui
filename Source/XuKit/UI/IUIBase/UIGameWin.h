#pragma once
#include "Blueprint/UserWidget.h"
#include "XuKit/UI/UIBaseInterface.h"
#include "UIGameWin.generated.h"
UCLASS()
class UUIGameWin : public UUserWidget, public IUIBaseInterface
{
	GENERATED_BODY()
public:
	virtual EUILayer GetUILayer_Implementation() const override;
	virtual EUIType GetUIType_Implementation() const override;
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
};
