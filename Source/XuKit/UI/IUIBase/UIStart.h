#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "XuKit/UI/UIBase.h"
#include "UIStart.generated.h"

/**
 * 
 */
UCLASS()
class XUKIT_API UUIStart : public UUIBase
{
public:
	virtual EUILayer GetUILayer() const override;
	virtual EUIType GetUIType() const override;

private:
	GENERATED_BODY()

public:
	
	
	
	
	

protected:

};
