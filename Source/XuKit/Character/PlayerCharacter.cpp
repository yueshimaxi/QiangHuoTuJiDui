// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "XuKit/PlayerController/QHPlayerController.h"

APlayerCharacter::APlayerCharacter()
{
	bReplicates = true;

	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0, 500, 0);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	//CharactorClass = ECharactorClass::Elementalist;



	spring_arm_component = CreateDefaultSubobject<USpringArmComponent>(TEXT("spring_arm_component"));
	spring_arm_component->SetupAttachment(RootComponent);
	spring_arm_component->bDoCollisionTest = false;
	spring_arm_component->bUsePawnControlRotation=false;
	spring_arm_component->bInheritYaw = false;
	spring_arm_component->bInheritPitch = false;
	spring_arm_component->bInheritRoll = false;
	
	camera_component = CreateDefaultSubobject<UCameraComponent>(TEXT("camera_component"));
	camera_component->SetupAttachment(spring_arm_component, USpringArmComponent::SocketName);

	
}

void APlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//让角色面朝鼠标的方向
	SetPawnRotatorToMouseCursor();
}

void APlayerCharacter::SetPawnRotatorToMouseCursor()
{
	if (AQHPlayerController* player_controller = Cast<AQHPlayerController>(GetController()))
	{
		FVector hit_location = player_controller->CurorHitResult.ImpactPoint;
		FRotator look_at = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), hit_location);
		FRotator new_rot = FRotator(0, look_at.Yaw, 0);
		SetActorRotation(new_rot);
	}
}
