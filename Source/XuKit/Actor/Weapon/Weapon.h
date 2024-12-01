// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "XuKit/QiangHuoTuJiDui.h"
#include "XuKit/AbilitySystem/Ability/QHGameplayAbility.h"
#include "XuKit/Interface/IInteractionIterface.h"
#include "Weapon.generated.h"

class APlayerCharacter;
class USphereComponent;
class UWidgetComponent;

UENUM()
enum class EWeaponState
{
	EWS_Inital,
	EWS_Equiped,
	EWS_Backpack,
	EWS_Dropped,
	
	Max,
};





UCLASS()
class XUKIT_API AWeapon : public AActor,public IIInteractionIterface
{
	GENERATED_BODY()
	
public:	
	AWeapon();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


public:
	virtual EInteractionType GetInteractionType_Implementation() override;
public:	
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* weapon_mesh_component;

	UPROPERTY(EditAnywhere)
	USphereComponent* area_component;

	UPROPERTY(EditAnywhere)
	UWidgetComponent* widget_component;

	UPROPERTY()
	EWeaponState weapon_state;

	void SetWeaponState(EWeaponState state,APlayerCharacter* character);
	UFUNCTION(Server,Reliable)
	void ServerSetWeaponState(EWeaponState state,APlayerCharacter* character);
	UFUNCTION(NetMulticast,Reliable)
	void MulticastSetWeaponState(EWeaponState state,APlayerCharacter* character);

	
	virtual  void OnWeaponStateSet();

	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
					  int32 OtherBodyIndex);


	virtual void OnRep_Owner() override;

	void SetOwningCharacter(APlayerCharacter* character);

	UPROPERTY(EditAnywhere, Category = "AQHInitInfo")
	TArray<TSubclassOf<UQHGameplayAbility>> Abilities;


	UPROPERTY(BlueprintReadOnly, Category = "AQHInitInfo")
	TArray<FGameplayAbilitySpecHandle> AbilitySpecHandles;
	
	UPROPERTY(BlueprintReadOnly, Replicated, Category = "AQHInitInfo")
	APlayerCharacter* OwningCharacter;

	// Called when the player equips this weapon
	virtual void Equip();

	// Called when the player unequips this weapon
	virtual void UnEquip();
	
	virtual void AddAbilities();
	virtual void RemoveAbilities();

	virtual int32 GetAbilityLevel(EQHAbilityInputID AbilityID);

	


};


