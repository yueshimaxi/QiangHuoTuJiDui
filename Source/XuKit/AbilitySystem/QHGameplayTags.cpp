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

	gameplayTags.CombatSocket_WeaponTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Combat.Socket.Weapon"),TEXT("Weapon"));
	gameplayTags.CombatSocket_LeftHandTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Combat.Socket.LeftHand"),TEXT("Left Hand"));
	gameplayTags.CombatSocket_RightHandTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Combat.Socket.RightHand"),TEXT("Right Hand"));
	gameplayTags.CombatSocket_TailTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Combat.Socket.Tail"),TEXT("Tail"));


	gameplayTags.Attributes_Meta_IncomingXPTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Meta.IncomingXP"),TEXT("Incoming XP"));

	gameplayTags.HitReactTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("HitReact"),TEXT("Hit React"));

	gameplayTags.FireTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Ability.Fire"),TEXT("Fire"));
	gameplayTags.ReloadTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Ability.Reload"),TEXT("Reload"));
	gameplayTags.SwapWeaponTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Ability.SwapWeapon"),TEXT("Swap Weapon"));

	gameplayTags.Cooldown_FireTag= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.Fire"),TEXT("Fire Cooldown"));
	gameplayTags.Cooldown_ReloadTag= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.Reload"),TEXT("Reload Cooldown"));

	gameplayTags.GameplayCue_GunFireSoundTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("GameplayCue.GunFire.Sound"),TEXT("Gun Fire Sound"));
	gameplayTags.GameplayCue_GunFireEmitterTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("GameplayCue.GunFire.Emitter"),TEXT("Gun Fire Emitter"));
}
