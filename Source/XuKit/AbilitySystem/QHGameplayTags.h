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
	FGameplayTag SwapWeaponTag;
	FGameplayTag Abilities_AttackTag;


	//meta data tags
	FGameplayTag Attributes_Meta_IncomingXPTag;
	
	FGameplayTag HitReactTag;

	

	//cooldown tags
	FGameplayTag Cooldown_FireTag;
	FGameplayTag Cooldown_ReloadTag;


	FGameplayTag GameplayCue_GunFireSoundTag;
	FGameplayTag GameplayCue_GunFireEmitterTag;

	FGameplayTag Montage_Attack1Tag;
	FGameplayTag Montage_Attack2Tag;
	FGameplayTag Montage_Attack3Tag;
	FGameplayTag Montage_Attack4Tag;

	FGameplayTag Weapon_Projectile_Rifle;
	FGameplayTag Weapon_Projectile_Pistol;
	FGameplayTag Weapon_Explode_Shotgun;
	FGameplayTag Weapon_Explode_Rocket;
	FGameplayTag Weapon_Plasma_LaserGun;
	FGameplayTag Weapon_Hero_BlackGatling;

	

	
private:
	static QHGameplayTags gameplayTags;
};