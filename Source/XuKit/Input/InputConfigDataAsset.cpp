// Fill out your copyright notice in the Description page of Project Settings.


#include "InputConfigDataAsset.h"

UInputAction* UInputConfigDataAsset::FindQHInputActionByTag(FGameplayTag ActionTag, bool bLogError)
{
	for (FQHInputAction& Action : InputActions)
	{
		if (Action.ActionTag.MatchesTag(ActionTag))
		{
			if (Action.InputAction)
			{
				return Action.InputAction;
			}
		}
	}

	if (bLogError)
	{
		UE_LOG(LogTemp, Error, TEXT("ActionTag %s not found in UInputConfigDataAsset %s"), *ActionTag.ToString(), *GetName());
	}

	return nullptr;
}
