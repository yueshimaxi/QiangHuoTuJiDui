// Fill out your copyright notice in the Description page of Project Settings.


#include "QHCharacterBase.h"

#include "Components/CapsuleComponent.h"
#include "XuKit/XuKit.h"
#include "XuKit/AbilitySystem/QHAbilitySystemComponent.h"

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

UAbilitySystemComponent* AQHCharacterBase::GetAbilitySystemComponent() const
{
	return qh_ability_system_component;
}

UAttributeSet* AQHCharacterBase::GetAttributeSet()
{
	return qh_attribute_set;
}

void AQHCharacterBase::AddCharactorAbilities()
{
	UQHAbilitySystemComponent* ABS = Cast<UQHAbilitySystemComponent>(qh_ability_system_component);
	if (!HasAuthority())return;
	ABS->AddCharactorAbilities(DefaultAbilities);
}
