#include "QHGameplayTags.h"

#include "GameplayTagsManager.h"

QHGameplayTags QHGameplayTags::gameplayTags;

void QHGameplayTags::InitGameplayTags()
{
	gameplayTags.MaxHealthTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxHealth"),TEXT("Max Health"));
	gameplayTags.InputTag_MouseLeftTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.Mouse.Left"),TEXT("Mouse Left"));
	gameplayTags.InputTag_MouseRightTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.Mouse.Right"),TEXT("Mouse Right"));
	
	gameplayTags.DamageTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage"),TEXT("Damage"));

	gameplayTags.CombatSocket_WeaponTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Combat.Socket.Weapon"),TEXT("Weapon"));
	gameplayTags.CombatSocket_LeftHandTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Combat.Socket.LeftHand"),TEXT("Left Hand"));
	gameplayTags.CombatSocket_RightHandTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Combat.Socket.RightHand"),TEXT("Right Hand"));
	gameplayTags.CombatSocket_TailTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Combat.Socket.Tail"),TEXT("Tail"));

	gameplayTags.FireTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Ability.Fire"),TEXT("Fire"));
}
