// Fill out your copyright notice in the Description page of Project Settings.


#include "QHCharacterBase.h"

#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "XuKit/XuKit.h"
#include "XuKit/AbilitySystem/QHAbilitySystemComponent.h"
#include "XuKit/AbilitySystem/QHGameplayTags.h"

// Sets default values
AQHCharacterBase::AQHCharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponAttackSocket = TEXT("WeaponSocket");
	WeaponMesh->SetupAttachment(GetMesh(), WeaponAttackSocket);
}

// Called when the game starts or when spawned
void AQHCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AQHCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AQHCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AQHCharacterBase::InitAbilityActorInfo()
{
}

FVector AQHCharacterBase::GetCombatSocketLocation_Implementation(const FGameplayTag& socketTag)
{
	if (socketTag == QHGameplayTags::Get().CombatSocket_WeaponTag)
	{
		FVector socketLocation = WeaponMesh->GetSocketLocation(WeaponAttackSocket);
		return socketLocation;
	}
	if (socketTag == QHGameplayTags::Get().CombatSocket_LeftHandTag)
	{
		FVector socketLocation = GetMesh()->GetSocketLocation(LeftHandAttackSocket);
		return socketLocation;
	}
	if (socketTag == QHGameplayTags::Get().CombatSocket_RightHandTag)
	{
		FVector socketLocation = GetMesh()->GetSocketLocation(RightHandAttackSocket);
		return socketLocation;
	}
	if (socketTag == QHGameplayTags::Get().CombatSocket_TailTag)
	{
		FVector socketLocation = GetMesh()->GetSocketLocation(TailAttackSocket);
		return socketLocation;
	}
	return FVector::ZeroVector;
}

UAbilitySystemComponent* AQHCharacterBase::GetAbilitySystemComponent() const
{
	return qh_ability_system_component;
}

UAttributeSet* AQHCharacterBase::GetAttributeSet()
{
	return qh_attribute_set;
}

UAnimMontage* AQHCharacterBase::GetHitReactMontage_Implementation()
{
	return HitReactMontage;
}

void AQHCharacterBase::AddCharactorAbilities()
{
}

TArray<FTaggedMontage> AQHCharacterBase::GetTaggedMontages_Implementation()
{
	return TaggedMontages;
}

FTaggedMontage AQHCharacterBase::GetTaggedMontageByTag_Implementation(FGameplayTag tag)
{
	for (FTaggedMontage& taggedMontage : TaggedMontages)
	{
		if (taggedMontage.MontageTag.MatchesTag(tag))
		{
			return taggedMontage;
		}
	}
	return FTaggedMontage();
}

void AQHCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> DefaultAttributeEffect)
{
	check(IsValid(GetAbilitySystemComponent()));
	check(DefaultAttributeEffect);
	FGameplayEffectContextHandle effect_context_handle = GetAbilitySystemComponent()->MakeEffectContext();
	effect_context_handle.AddSourceObject(this);
	const FGameplayEffectSpecHandle effect_spec_handle = GetAbilitySystemComponent()->MakeOutgoingSpec(DefaultAttributeEffect, 1.0f, effect_context_handle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*effect_spec_handle.Data.Get(), GetAbilitySystemComponent());
}

void AQHCharacterBase::InitDefaultAttributesToSelf()
{
	for (TSubclassOf<UGameplayEffect> DefaultPrimaryAttributeEffect : DefaultPrimaryAttributeEffects)
	{
		ApplyEffectToSelf(DefaultPrimaryAttributeEffect);
	}
}

void AQHCharacterBase::Die()
{
	Die_Server();
}

bool AQHCharacterBase::IsDead()
{
	return isDead;

}


void AQHCharacterBase::Die_Server_Implementation()
{
	Die_Multicast();
}

void AQHCharacterBase::Die_Multicast_Implementation()
{
	VirDie();
}

void AQHCharacterBase::VirDie()
{
	isDead = true;

	WeaponMesh->SetSimulatePhysics(true);
	WeaponMesh->SetEnableGravity(true);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Dissive();
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), DeathSound, GetActorLocation());
}


void AQHCharacterBase::Dissive()
{
	if (MeshDissiveM)
	{
		MeshDissiveDM = UMaterialInstanceDynamic::Create(MeshDissiveM, GetMesh());
		GetMesh()->SetMaterial(0, MeshDissiveDM);
		StartDissiveTimeline(MeshDissiveDM);
	}
	if (WeaponMeshDissiveM)
	{
		WeaponMeshDissiveDM = UMaterialInstanceDynamic::Create(WeaponMeshDissiveM, WeaponMesh);
		WeaponMesh->SetMaterial(0, WeaponMeshDissiveDM);
		StartWeaponDissiveTimeline(WeaponMeshDissiveDM);
	}
}
