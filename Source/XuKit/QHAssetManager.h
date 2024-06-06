// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "QHAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class XUKIT_API UQHAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:
	static UQHAssetManager& Get();
	virtual void StartInitialLoading() override;
};
