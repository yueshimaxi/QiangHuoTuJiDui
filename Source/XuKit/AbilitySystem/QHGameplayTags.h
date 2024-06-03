#pragma once


#include "GameplayTagContainer.h"

/**
 * 
 */
struct QHGameplayTags
{
public:

	QHGameplayTags()
	{
		InitGameplayTags();
	}
	
	static QHGameplayTags& Get() { return gameplayTags; };

	void InitGameplayTags();


	FGameplayTag MaxHealthTag;

	//input tags
	FGameplayTag  InputTag_MouseLeftTag;
	FGameplayTag  InputTag_MouseRightTag;
	

private:
	static QHGameplayTags gameplayTags;
};