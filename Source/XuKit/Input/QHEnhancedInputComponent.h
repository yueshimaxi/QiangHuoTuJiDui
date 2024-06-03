// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "InputConfigDataAsset.h"
#include "QHEnhancedInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class XUKIT_API UQHEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template <typename UserClass, typename PressedFunc, typename HeldFunc, typename ReleaseFunc>
	void BindActions(UInputConfigDataAsset* InputConfigDataAsset, UserClass* object, PressedFunc pressedFunc, HeldFunc heldFunc, ReleaseFunc releaseFunc)
	{
		check(InputConfigDataAsset);
		for (auto& Action : InputConfigDataAsset->InputActions)
		{
			if (Action.InputAction && Action.ActionTag.IsValid())
			{
				if (pressedFunc)
				{
					BindAction(Action.InputAction, ETriggerEvent::Started, object, pressedFunc, Action.ActionTag);
				}
				if (heldFunc)
				{
					BindAction(Action.InputAction, ETriggerEvent::Triggered, object, heldFunc, Action.ActionTag);
				}
				if (releaseFunc)
				{
					BindAction(Action.InputAction, ETriggerEvent::Completed, object, releaseFunc, Action.ActionTag);
				}
			}
		}
	}
};
