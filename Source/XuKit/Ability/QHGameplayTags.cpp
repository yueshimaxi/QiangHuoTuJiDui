#include "QHGameplayTags.h"

#include "GameplayTagsManager.h"

QHGameplayTags QHGameplayTags::gameplayTags;

void QHGameplayTags::InitGameplayTags()
{
	gameplayTags.MaxHealthTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxHealth"),TEXT("Max Health"));
	

}
