#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "XuKit/UI/UIBaseInterface.h"
#include "UIStart.generated.h"

/**
 * 
 */
UCLASS()
class XUKIT_API UUIStart : public UUserWidget,public  IUIBaseInterface
{
public:
	virtual EUILayer GetUILayer_Implementation() const override;
	virtual EUIType GetUIType_Implementation() const override;

private:
	GENERATED_BODY()

public:
	
	
	
	
	

protected:

};
