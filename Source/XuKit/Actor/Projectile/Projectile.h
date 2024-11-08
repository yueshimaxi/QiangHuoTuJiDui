// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "NiagaraSystem.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;

UCLASS()
class XUKIT_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Destroyed() override;


	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USphereComponent* SphereCom;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ProjectileMovementCom;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UParticleSystemComponent* tracer_component;
	

	UPROPERTY(EditAnywhere, Category = "AInitInfo")
	TObjectPtr<UParticleSystem> tracerEffect;

	UPROPERTY(EditDefaultsOnly, Category = "AInitInfo")
	TObjectPtr<UParticleSystem> ImpactEffect;

	UPROPERTY(EditDefaultsOnly, Category = "AInitInfo")
	TObjectPtr<USoundBase> ImpactSound;

	UPROPERTY(EditDefaultsOnly, Category = "AInitInfo")
	TObjectPtr<USoundBase> LoopSound;
	
	UPROPERTY(VisibleAnywhere)
	UAudioComponent* LoopSoundComponent;

	UPROPERTY(BlueprintReadWrite, meta=(ExposeOnSpawn=true))
	FGameplayEffectSpecHandle EffectHandle;
	
	bool bHit;

	UPROPERTY(EditDefaultsOnly)
	float lifeSpan = 5;

	UFUNCTION(NetMulticast,Reliable)
	void HitDestory();

};
