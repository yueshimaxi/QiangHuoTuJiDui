// Fill out your copyright notice in the Description page of Project Settings.


#include "QHAnimInstance.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "XuKit/XuBPFuncLib.h"
#include "XuKit/Character/QHCharacterBase.h"
#include "XuKit/PlayerController/QHPlayerController.h"
#include "XuKit/PlayerState/QHPlayerState.h"

void UQHAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	InitCom();
}

void UQHAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (MovementComponent && qh_playerstate)
	{
		//以鼠标方向为向前方向，计算角色的前后左右移动速度
		FRotator ControlRotator = qh_character->GetControlRotation();
		FRotator CharacterRotator = qh_character->GetActorRotation();
		FRotator DeltaRotator = CharacterRotator - ControlRotator;
		DeltaRotator.Normalize();
		FVector ForwardVector = FRotationMatrix(DeltaRotator).GetUnitAxis(EAxis::X);
		FVector RightVector = FRotationMatrix(DeltaRotator).GetUnitAxis(EAxis::Y);


		FVector inputForward = FVector(MovementComponent->Velocity.X / MovementComponent->GetMaxSpeed(), 0, 0);
		FVector inputRight = FVector(0, MovementComponent->Velocity.Y / MovementComponent->GetMaxSpeed(), 0);
		float blenderSpaceMaxSpeed = 100;
		HorSpeed = FVector::DotProduct(RightVector, inputForward) + FVector::DotProduct(RightVector, inputRight);
		HorSpeed = FMath::Clamp(HorSpeed *= blenderSpaceMaxSpeed, -blenderSpaceMaxSpeed, blenderSpaceMaxSpeed);
		VerSpeed = FVector::DotProduct(ForwardVector, inputForward) + FVector::DotProduct(ForwardVector, inputRight);
		VerSpeed = FMath::Clamp(VerSpeed *= blenderSpaceMaxSpeed, -blenderSpaceMaxSpeed, blenderSpaceMaxSpeed);

		//XuPRINT(FString::Printf(TEXT("horInputValue: %f,verInputValue: %f"), qh_playercontroller->horInputValue, qh_playercontroller->verInputValue));

		//XuPRINT(FString::Printf(TEXT("ForwardVector: %s,RightVector: %s,HorSpeed: %f,VerSpeed: %f, MovementComponent->Velocity: %s"), *ForwardVector.ToString(), *RightVector.ToString(), HorSpeed, VerSpeed, *MovementComponent->Velocity.ToString()));
		//将向前向量和向右向量画出
		//DrawDebugLine(GetWorld(), qh_character->GetActorLocation(), qh_character->GetActorLocation() + ForwardVector * 100, FColor::Red, false, 0.1f, 0, 1);
		//DrawDebugLine(GetWorld(), qh_character->GetActorLocation(), qh_character->GetActorLocation() + RightVector * 100, FColor::Green, false, 0.1f, 0, 1);

		FVector2D MovementInput = FVector2D(HorSpeed, VerSpeed);
		ShouldIdle = MovementInput.Size() <= 3.f;
	}
	else
	{
		InitCom();
	}
}

void UQHAnimInstance::InitCom()
{
	qh_character = Cast<AQHCharacterBase>(TryGetPawnOwner());
	if (qh_character)
	{
		MovementComponent = qh_character->GetCharacterMovement();
		qh_playerstate = Cast<AQHPlayerState>(qh_character->GetPlayerState());
	}
}
