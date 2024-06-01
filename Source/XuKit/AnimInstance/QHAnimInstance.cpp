// Fill out your copyright notice in the Description page of Project Settings.


#include "QHAnimInstance.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "XuKit/XuBPFuncLib.h"
#include "XuKit/Character/QHCharacterBase.h"
#include "XuKit/PlayerController/QHPlayerController.h"

void UQHAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	InitCom();
}

void UQHAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (MovementComponent&&qh_playercontroller)
	{
		//以鼠标方向为向前方向，计算角色的前后左右移动速度
		// FRotator ControlRotator = qh_playercontroller->GetControlRotation();
		// FRotator CharacterRotator = qh_character->GetMesh()->GetComponentRotation();
		// FRotator DeltaRotator = ControlRotator - CharacterRotator;
		// DeltaRotator.Normalize();
		// FVector ForwardVector = FRotationMatrix(DeltaRotator).GetUnitAxis(EAxis::X);
		// FVector RightVector = FRotationMatrix(DeltaRotator).GetUnitAxis(EAxis::Y);
		// HorSpeed = FVector::DotProduct(ForwardVector, MovementComponent->Velocity);
		// VerSpeed = -FVector::DotProduct(RightVector, MovementComponent->Velocity);
	
		HorSpeed = qh_playercontroller->horInputValue * 100;
		VerSpeed = qh_playercontroller->verInputValue * 100;

		qh_playercontroller->horInputValue = 0;
		qh_playercontroller->verInputValue = 0;
		XuPRINT(FString::Printf(TEXT("HorSpeed:%f,VerSpeed:%f"), HorSpeed, VerSpeed));
		
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
		qh_playercontroller = qh_character->GetController<AQHPlayerController>();
	}
}
