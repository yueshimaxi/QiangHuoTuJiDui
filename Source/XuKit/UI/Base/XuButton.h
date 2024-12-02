#pragma once
#include "Components/Button.h"
#include "CoreMinimal.h"
#include "XuButton.generated.h"
DECLARE_DELEGATE(FXuButtonClicked);

UCLASS(BlueprintType,Blueprintable)
class UXuButton:public UButton
{
	GENERATED_BODY()
public:
	UXuButton();
	FXuButtonClicked XuButtonClicked;
	
	UFUNCTION()
	void OnClickBtn();

	
	UFUNCTION(BlueprintNativeEvent)
	void XuNativeOnClickBtn();
	UFUNCTION(BlueprintNativeEvent)
	void XuNativeOnHorverBtn();
};
