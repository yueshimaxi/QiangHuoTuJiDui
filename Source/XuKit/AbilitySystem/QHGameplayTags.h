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
	FGameplayTag  InputTag_key_R_tag;

	//ability tags
	FGameplayTag DamageTag;

	//socket tags
	FGameplayTag CombatSocket_WeaponTag;
	FGameplayTag CombatSocket_LeftHandTag;
	FGameplayTag CombatSocket_RightHandTag;
	FGameplayTag CombatSocket_TailTag;

	//ability tags
	FGameplayTag FireTag;
	FGameplayTag ReloadTag;

	FGameplayTag Attributes_Meta_IncomingXPTag;
	
	FGameplayTag HitReactTag;

	


	
private:
	static QHGameplayTags gameplayTags;
};