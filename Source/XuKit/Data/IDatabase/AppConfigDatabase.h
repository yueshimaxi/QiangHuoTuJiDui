// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "XuKit/Data/XuDataBase.h"
#include "AppConfigDatabase.generated.h"
USTRUCT()
struct FAppConfigData
{
	GENERATED_BODY()
	UPROPERTY()
	FString ip;
};
/**
 * 
 */
UCLASS()
class XUKIT_API UAppConfigDatabase : public UXuDataBase
{
	GENERATED_BODY()
public:
	virtual ::DataBaseType DataBaseType() override;
	virtual FString DataPath() override;
	virtual void OnParse() override;
	virtual void OnSave() override;
	virtual void ClearData() override;


	UPROPERTY()
	FAppConfigData appConfigData;
};
