// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QHCharacterBase.h"
#include "DlgSystem/DlgDialogue.h"
#include "GameFramework/Character.h"
#include "XuKit/Interface/IInteractionIterface.h"
#include "Anpc.generated.h"

UCLASS()
class XUKIT_API ANPC : public AActor, public IIInteractionIterface
{
	GENERATED_BODY()

public:
	ANPC();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC")
	UDlgDialogue* DialogueAsset;

	virtual FGameplayTag GetInteractionType_Implementation() override;

	virtual void Interaction_Implementation(APlayerCharacter* playerCharacter) override;


};
