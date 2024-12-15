// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop.h"

#include "XuKit/AbilitySystem/QHGameplayTags.h"


// Sets default values
AProp::AProp()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AProp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FGameplayTag AProp::GetInteractionType_Implementation()
{
	return 	FGameplayTag::RequestGameplayTag(FName("Interact_Prop"));
}

