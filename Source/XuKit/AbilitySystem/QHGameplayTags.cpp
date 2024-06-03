#include "QHGameplayTags.h"

#include "GameplayTagsManager.h"

QHGameplayTags QHGameplayTags::gameplayTags;

void QHGameplayTags::InitGameplayTags()
{
	gameplayTags.MaxHealthTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxHealth"),TEXT("Max Health"));
	gameplayTags.InputTag_MouseLeftTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.Mouse.Left"),TEXT("Mouse Left"));
	gameplayTags.InputTag_MouseRightTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.Mouse.Right"),TEXT("Mouse Right"));
	

}
