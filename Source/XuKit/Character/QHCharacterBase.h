// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "XuKit/Interface/CombatInterface.h"
#include "QHCharacterBase.generated.h"

class UGameplayAbility;
class UAttributeSet;

UCLASS()
class XUKIT_API AQHCharacterBase : public ACharacter, public IAbilitySystemInterface,public ICombatInterface
{
	GENERATED_BODY()

public:
	AQHCharacterBase();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void InitAbilityActorInfo();
	virtual FVector GetCombatSocketLocation_Implementation(const FGameplayTag& socketTag) override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet();

	
	void AddCharactorAbilities();



public:	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="InitInfo")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAbilitySystemComponent> qh_ability_system_component;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAttributeSet> qh_attribute_set;

	UPROPERTY(EditAnywhere, Category="InitInfo")
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;

	UPROPERTY(EditAnywhere, Category="InitInfo")
	FName WeaponAttackSocket;
	UPROPERTY(EditAnywhere, Category="InitInfo")
	FName LeftHandAttackSocket;
	UPROPERTY(EditAnywhere, Category="InitInfo")
	FName RightHandAttackSocket;
	UPROPERTY(EditAnywhere, Category="InitInfo")
	FName TailAttackSocket;
};
