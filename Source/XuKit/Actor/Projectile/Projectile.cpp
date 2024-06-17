// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "XuKit/XuKit.h"
#include "XuKit/AbilitySystem/QHAbilityBPLibrary.h"

// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereCom = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCom"));
	SetRootComponent(SphereCom);
	SphereCom->SetCollisionObjectType(ECC_Projectile);
	SphereCom->SetGenerateOverlapEvents(true);
	SphereCom->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereCom->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereCom->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	SphereCom->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	SphereCom->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	ProjectileMovementCom = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementCom"));
	ProjectileMovementCom->InitialSpeed = 2000.f;
	ProjectileMovementCom->MaxSpeed = 2000.f;
	ProjectileMovementCom->ProjectileGravityScale = 0;

	bReplicates = true;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(lifeSpan);
	if (HasAuthority())
	{
		SphereCom->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnOverlapBegin);
	}

	if (tracerEffect)
	{
		tracer_component = UGameplayStatics::SpawnEmitterAttached(tracerEffect, SphereCom, FName(), GetActorLocation(), GetActorRotation(),
		                                                          EAttachLocation::KeepWorldPosition);
	}
	if (LoopSound)
	{
		LoopSoundComponent = UGameplayStatics::SpawnSoundAttached(LoopSound, GetRootComponent());
	}
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::Destroyed()
{
	Super::Destroyed();

	if (LoopSoundComponent)LoopSoundComponent->Stop();

}

void AProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!EffectHandle.Data.IsValid())
	{
		//XuPRINT("EffectHandle is invalid",false);
		return;
	}
	if (EffectHandle.Data.IsValid() && EffectHandle.Data.Get()->GetEffectContext().GetEffectCauser() == OtherActor)
	{
		//XuPRINT("EffectHandle is invalid && EffectHandle.Data.Get()->GetEffectContext().GetEffectCauser() == OtherActor", false);
		return;
	}
	if (!UQHAbilityBPLibrary::IsNotFriendly(EffectHandle.Data.Get()->GetEffectContext().GetEffectCauser(), OtherActor))
	{
		return;
	}
	if (UAbilitySystemComponent* targetABS = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
	{
		targetABS->ApplyGameplayEffectSpecToSelf(*EffectHandle.Data.Get());
	}
	HitDestory();
}

void AProjectile::HitDestory_Implementation()
{
	if (ImpactEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, GetActorLocation(), GetActorRotation());
	}
	if (ImpactSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, GetActorLocation());
	}
	Destroy();
}
