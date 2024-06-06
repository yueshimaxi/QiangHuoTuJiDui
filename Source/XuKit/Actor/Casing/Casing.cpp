// Fill out your copyright notice in the Description page of Project Settings.


#include "Casing.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
ACasing::ACasing()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh_component=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh_component"));
	RootComponent=mesh_component;
	mesh_component->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	mesh_component->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
	mesh_component->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Block);
	
	mesh_component->SetSimulatePhysics(true);
	ShellEjectionImpulse=5.f;
}

// Called when the game starts or when spawned
void ACasing::BeginPlay()
{
	Super::BeginPlay();
	mesh_component->OnComponentHit.AddDynamic(this, &ACasing::OnHit);
	mesh_component->AddImpulse(GetActorRightVector() * ShellEjectionImpulse);
}

// Called every frame	
void ACasing::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACasing::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if (fall_sound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), fall_sound, GetActorLocation());
	}
	Destroy();
}
