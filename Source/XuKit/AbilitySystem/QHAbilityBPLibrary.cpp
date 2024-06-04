// Fill out your copyright notice in the Description page of Project Settings.


#include "QHAbilityBPLibrary.h"

bool UQHAbilityBPLibrary::IsNotFriendly(AActor* ActorA, AActor* ActorB)
{
	bool isPlayer = ActorA->ActorHasTag("Player") && ActorB->ActorHasTag("Player");
	bool isEnemy = ActorA->ActorHasTag("Enemy") && ActorB->ActorHasTag("Enemy");
	return !(isPlayer || isEnemy);
}
