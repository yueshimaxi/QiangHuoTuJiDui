// Fill out your copyright notice in the Description page of Project Settings.


#include "XuKit/PlayerController/XuPlayerController.h"

#include "XuCheatManager.h"
#include "XuKit/Subsystem/APPMgr.h"

AXuPlayerController::AXuPlayerController()
{
	CheatClass = UXuCheatManager::StaticClass();
}

void AXuPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetShowMouseCursor(true);
	GetWorld()->GetSubsystem<UAPPMgr>()->Init();
}

void AXuPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

FTransform AXuPlayerController::GetCurViewTran()
{
	FTransform ts;
	ts = PlayerCameraManager->GetActorTransform();
	return ts;
}
