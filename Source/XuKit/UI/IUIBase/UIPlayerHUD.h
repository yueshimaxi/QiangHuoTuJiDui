#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "XuKit/UI/UIBaseInterface.h"
#include "UIPlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class XUKIT_API UUIPlayerHUD : public UUserWidget,public  IUIBaseInterface
{
public:
	virtual EUILayer GetUILayer_Implementation() const override;
	virtual EUIType GetUIType_Implementation() const override;

private:
	GENERATED_BODY()

public:
	
	
	
	
	

protected:

};
