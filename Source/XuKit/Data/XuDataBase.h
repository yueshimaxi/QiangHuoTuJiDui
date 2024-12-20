#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "XuDataBase.generated.h"

UENUM()
enum class DataBaseType:uint8 //设置uint8类型
{
	None,
	AppConfigData,
	WeaponConfigData,
};

/**
 * 
 */
UCLASS()
class XUKIT_API UXuDataBase : public UObject
{
	GENERATED_BODY()

public:
	virtual DataBaseType DataBaseType();
	virtual FString DataPath();
	virtual void OnParse();
	UFUNCTION(BlueprintCallable)
	virtual void OnSave();
	virtual void ClearData();
};
