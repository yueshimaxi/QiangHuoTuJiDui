#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Components/CheckBox.h"
#include "XuCheckBox.generated.h"
DECLARE_DELEGATE_OneParam(FXuOnCheckBoxStateChanged, bool);

UCLASS()
class UXuCheckBox:public UCheckBox
{
	GENERATED_BODY()
public:
	UXuCheckBox();
	FXuOnCheckBoxStateChanged XuOnCheckStateChanged;
	UFUNCTION()
	void OnCheckBoxStateChanged(bool b_is_checked);
};
