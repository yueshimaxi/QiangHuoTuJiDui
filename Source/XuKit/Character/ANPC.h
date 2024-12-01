// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QHCharacterBase.h"
#include "DlgSystem/DlgDialogue.h"
#include "GameFramework/Character.h"
#include "Anpc.generated.h"

UCLASS()
class XUKIT_API ANPC : public AActor, public IIInteractionIterface
{
	GENERATED_BODY()

public:
	ANPC();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC")
	UDlgDialogue* DialogueAsset;

	virtual EInteractionType GetInteractionType_Implementation() override;


};
