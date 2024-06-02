// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "XuKit/XuKit.h"

// Sets default values
AWeapon::AWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	weapon_mesh_component = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("weapon_mesh_component"));
	RootComponent = weapon_mesh_component;
	weapon_mesh_component->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	weapon_mesh_component->SetCollisionResponseToChannels(ECollisionResponse::ECR_Ignore);

	area_component = CreateDefaultSubobject<USphereComponent>(TEXT("area_component"));
	area_component->SetupAttachment(RootComponent);
	area_component->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	area_component->SetCollisionResponseToChannels(ECollisionResponse::ECR_Ignore);
	area_component->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	widget_component = CreateDefaultSubobject<UWidgetComponent>(TEXT("widget_component"));
	widget_component->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	area_component->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnOverlapBegin);
	area_component->OnComponentEndOverlap.AddDynamic(this, &AWeapon::OnOverlapEnd);
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void AWeapon::OnWeaponStateReply(EWeaponState state)
{
}

void AWeapon::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AWeapon::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AWeapon::Fire(const FHitResult& hit_result)
{
}

void AWeapon::OnRep_Owner()
{
	Super::OnRep_Owner();
}
