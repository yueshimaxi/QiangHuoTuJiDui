#include "QHGameplayTags.h"

#include "GameplayTagsManager.h"

QHGameplayTags QHGameplayTags::gameplayTags;

void QHGameplayTags::InitGameplayTags()
{
	gameplayTags.MaxHealthTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxHealth"),TEXT("Max Health"));
	gameplayTags.InputTag_MouseLeftTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.Mouse.Left"),TEXT("Mouse Left"));
	gameplayTags.InputTag_MouseRightTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.Mouse.Right"),TEXT("Mouse Right"));
	gameplayTags.InputTag_key_R_tag =	UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.Key.R"),TEXT("Key R"));
	
	gameplayTags.DamageTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage"),TEXT("Damage"));

	gameplayTags.CombatSocket_WeaponTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.Weapon"),TEXT("CombatSocket Weapon"));
	gameplayTags.CombatSocket_LeftHandTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.LeftHand"),TEXT("CombatSocket LeftHand"));
	gameplayTags.CombatSocket_RightHandTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.RightHand"),TEXT("CombatSocket RightHand"));
	gameplayTags.CombatSocket_TailTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.Tail"),TEXT("CombatSocket Tail"));


	gameplayTags.Attributes_Meta_IncomingXPTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Meta.IncomingXP"),TEXT("Incoming XP"));

	gameplayTags.HitReactTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("HitReact"),TEXT("Hit React"));

	gameplayTags.FireTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Ability.Fire"),TEXT("Fire"));
	gameplayTags.ReloadTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Ability.Reload"),TEXT("Reload"));
	gameplayTags.SwapWeaponTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Ability.SwapWeapon"),TEXT("Swap Weapon"));
	gameplayTags.Abilities_AttackTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Ability.Attack"),TEXT("Attack"));

	gameplayTags.Cooldown_FireTag= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.Fire"),TEXT("Fire Cooldown"));
	gameplayTags.Cooldown_ReloadTag= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.Reload"),TEXT("Reload Cooldown"));

	gameplayTags.GameplayCue_GunFireSoundTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("GameplayCue.GunFire.Sound"),TEXT("Gun Fire Sound"));
	gameplayTags.GameplayCue_GunFireEmitterTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("GameplayCue.GunFire.Emitter"),TEXT("Gun Fire Emitter"));

	gameplayTags.Montage_Attack1Tag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack1"),TEXT("Montage Attack1"));
	gameplayTags.Montage_Attack2Tag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack2"),TEXT("Montage Attack2"));
	gameplayTags.Montage_Attack3Tag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack3"),TEXT("Montage Attack3"));
	gameplayTags.Montage_Attack4Tag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack4"),TEXT("Montage Attack4"));

	gameplayTags.Weapon_Projectile_Pistol = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Weapon.Projectile.Pistol"),TEXT("Weapon Projectile Pistol"));
	gameplayTags.Weapon_Projectile_Rifle = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Weapon.Projectile.Rifle"),TEXT("Weapon Projectile Rifle"));
	gameplayTags.Weapon_Explode_Shotgun = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Weapon.Explode.Shotgun"),TEXT("Weapon Explode Shotgun"));
	gameplayTags.Weapon_Explode_Rocket = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Weapon.Explode.Sniper"),TEXT("Weapon Explode Sniper"));
	gameplayTags.Weapon_Plasma_LaserGun = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Weapon.Plasma.LaserGun"),TEXT("Weapon Plasma LaserGun"));
	gameplayTags.Weapon_Hero_BlackGatling = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Weapon.Hero.Grenade"),TEXT("Weapon Hero Grenade"));
}
