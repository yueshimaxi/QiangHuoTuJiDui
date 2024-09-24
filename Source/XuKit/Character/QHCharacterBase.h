// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "NiagaraSystem.h"
#include "GameFramework/Character.h"
#include "XuKit/Interface/CombatInterface.h"
#include "QHCharacterBase.generated.h"

class UGameplayEffect;
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

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	UAnimMontage* HitReactMontage;
	virtual UAnimMontage* GetHitReactMontage_Implementation() override;
	virtual void AddCharactorAbilities();

	virtual TArray<FTaggedMontage> GetTaggedMontages_Implementation() override;
	virtual FTaggedMontage GetTaggedMontageByTag_Implementation(FGameplayTag tag) override;

public:	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "AInitInfo")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAbilitySystemComponent> qh_ability_system_component;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAttributeSet> qh_attribute_set;

	UPROPERTY(EditAnywhere, Category = "AInitInfo")
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;
	UPROPERTY(EditAnywhere, Category = "AInitInfo")
	TArray<TSubclassOf<UGameplayAbility>> StartUpPassiveAbilities;

	UPROPERTY(EditAnywhere, Category = "AInitInfo")
	FName WeaponAttackSocket;
	UPROPERTY(EditAnywhere, Category = "AInitInfo")
	FName LeftHandAttackSocket;
	UPROPERTY(EditAnywhere, Category = "AInitInfo")
	FName RightHandAttackSocket;
	UPROPERTY(EditAnywhere, Category = "AInitInfo")
	FName TailAttackSocket;

	UPROPERTY(EditAnywhere, Category=" AInitInfo")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributeEffect;
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> DefaultAttributeEffect);
	virtual void InitDefaultAttributesToSelf() ;

	UPROPERTY(EditAnywhere, Category = "AInitInfo")
	ECharactorClass CharactorClass;


	
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "AInitInfo")
	TArray<FTaggedMontage>	TaggedMontages;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "AInitInfo")
	UNiagaraSystem*	BloomEffect;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "AInitInfo")
	USoundBase* DeathSound;

	virtual void Die() override;
	virtual bool IsDead_Implementation() override;

	UFUNCTION(Server,Reliable)
	void Die_Server();
	UFUNCTION(NetMulticast, Reliable)
	void Die_Multicast();
	bool isDead=false;
	virtual void VirDie();

	UPROPERTY(EditAnywhere, Category="Combat")
	UMaterialInstance* MeshDissiveM;
	UPROPERTY()
	UMaterialInstanceDynamic* MeshDissiveDM;
	UPROPERTY(EditAnywhere, Category="Combat")
	UMaterialInstance* WeaponMeshDissiveM;
	UPROPERTY()
	UMaterialInstanceDynamic* WeaponMeshDissiveDM;

	
	void Dissive();

	UFUNCTION(BlueprintImplementableEvent)
	void StartDissiveTimeline(UMaterialInstanceDynamic* DissiveDM);

	UFUNCTION(BlueprintImplementableEvent)
	void StartWeaponDissiveTimeline(UMaterialInstanceDynamic* DissiveDM);
};
