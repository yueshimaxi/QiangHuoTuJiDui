// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IDatabase/AppConfigDatabase.h"
#include "DataMgr.generated.h"

/**
 * 
 */
UCLASS()
class XUKIT_API UDataMgr : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	UPROPERTY()
	TMap<DataBaseType, UObject*> m_DataBaseDic; 

	UFUNCTION(BlueprintCallable)
	UAppConfigDatabase* GetAppConfigDataBase() { return GetDataBase<UAppConfigDatabase>(DataBaseType::AppConfigData); }
private:
	template <typename T>
	T* GetDataBase(DataBaseType dataBaseType)
	{
		T* t;

		if (m_DataBaseDic.Contains(dataBaseType)) //&& IsValid(m_DataBaseDic[dataBaseType])
			{
			t = Cast<T>(m_DataBaseDic[dataBaseType]);
			}
		else
		{
			t = NewObject<T>(this);
			t->OnParse();
			m_DataBaseDic.Add(dataBaseType, t);
		}
		return t;
	}
};
