// Fill out your copyright notice in the Description page of Project Settings.


#include "ANPC.h"

#include "XuKit/AbilitySystem/QHGameplayTags.h"


ANPC::ANPC()
{
}

FGameplayTag ANPC::GetInteractionType_Implementation()
{
	return QHGameplayTags::Get().Interact_NPC;
}

void ANPC::Interaction_Implementation(APlayerCharacter* playerCharacter)
{
	playerCharacter->StartDialogue(DialogueAsset);
}

