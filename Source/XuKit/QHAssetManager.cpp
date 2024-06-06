// Fill out your copyright notice in the Description page of Project Settings.


#include "QHAssetManager.h"

#include "AbilitySystemGlobals.h"

UQHAssetManager& UQHAssetManager::Get()
{
	UQHAssetManager* aura_asstet_manager= Cast<UQHAssetManager>(GEngine->AssetManager);
	return *aura_asstet_manager;
}

void UQHAssetManager::StartInitialLoading()
{

	Super::StartInitialLoading();

	//AuraGameplayTags::Get().InitGameplayTags();
	//这是必须的
	UAbilitySystemGlobals::Get().InitGlobalData();
}


