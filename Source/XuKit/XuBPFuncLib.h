// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "XuBPFuncLib.generated.h"

#define XuPRINT(content) \
{ \
FString FunctionName = FString(__FUNCTION__); \
int32 LineNumber = __LINE__; \
FString ContentString = content; \
UE_LOG(LogTemp, Warning, TEXT("XuLog:[%s :%d] %s"), *FunctionName, LineNumber, *ContentString); \
}
class UEventMgr;
class UDataMgr;
class UUIMgr;
/**
 * 
 */
UCLASS()
class XUKIT_API UXuBPFuncLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	template <typename TEnum>
	static FString EnumToFString(FString Name, TEnum EnumValue)
	{
		const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, *Name, true);
		if (!EnumPtr) return FString(TEXT("InValid"));
		return EnumPtr->GetNameStringByIndex(static_cast<int32>(EnumValue));
	}

	template <typename TEnum>
	static TEnum FStringToEnum(FString Name, FString EnumValue)
	{
		const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, *Name, true);
		if (!EnumPtr)
		{
			XuPRINT(TEXT("InValid"));
			return TEnumAsByte<TEnum>();;
		}
		int32 EnumIndex = EnumPtr->GetIndexByName(FName(*EnumValue));

		if (EnumIndex == INDEX_NONE)
		{
			return TEnum::None;
		}
		return static_cast<TEnum>(EnumIndex);
	}

	UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject", DeterminesOutputType="actor"))
	static AActor* GetActorByClassAndTag(UObject* WorldContextObject, TSubclassOf<AActor> actor, FString name);

	UFUNCTION(Blueprintable, BlueprintCallable,meta=(WorldContext="WorldContextObject"), Category = "XuBPFuncLib")
	static UUIMgr* GetUIManager(UObject* WorldContextObject);

	UFUNCTION(Blueprintable, BlueprintCallable,meta=(WorldContext="WorldContextObject"), Category = "XuBPFuncLib")
	static UDataMgr* GetDataManager(UObject* WorldContextObject);

	UFUNCTION(Blueprintable, BlueprintCallable,meta=(WorldContext="WorldContextObject"), Category = "XuBPFuncLib")
	static UEventMgr* GetEventManager(UObject* WorldContextObject);
	
};
