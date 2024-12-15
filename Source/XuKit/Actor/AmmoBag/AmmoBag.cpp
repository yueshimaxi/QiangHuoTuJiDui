// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoBag.h"

#include "XuKit/XuBPFuncLib.h"
#include "XuKit/AbilitySystem/QHGameplayTags.h"
#include "XuKit/Event/EventDataDefine.h"
#include "XuKit/Event/EventMgr.h"


// Sets default values
AAmmoBag::AAmmoBag()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAmmoBag::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAmmoBag::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FGameplayTag AAmmoBag::GetInteractionType_Implementation()
{
	return QHGameplayTags::Get().Interact_Prop_Ammo;
}

void AAmmoBag::Interaction_Implementation(APlayerCharacter* playerCharacter)
{
	ReplenishAmmo(playerCharacter);
}


void AAmmoBag::ReplenishAmmo(APlayerCharacter* player_character)
{
	//TODO: 补充弹药为弹药上限
	TArray<FGameplayTag> MatchingTags = QHGameplayTags::GetTagsWithPrefix(AmmoTag);
	UGameplayEffect* GEAmmo = NewObject<UGameplayEffect>(GetTransientPackage(), FName(TEXT("Ammo")));
	GEAmmo->DurationPolicy = EGameplayEffectDurationType::Instant;
	GEAmmo->Modifiers.SetNum(MatchingTags.Num());
	
	
	for (int i = 0; i < MatchingTags.Num(); ++i)
	{
		FGameplayTag WeaponTag = MatchingTags[i];
		FGameplayAttribute MaxAttribute= UQHAttributeSet::GetMaxReserveAmmoAttributeFromTag(WeaponTag);
		int num = MaxAttribute.GetNumericValue(player_character->qh_attribute_set);
		FGameplayModifierInfo& InfoPrimaryAmmo = GEAmmo->Modifiers[i];
		InfoPrimaryAmmo.ModifierMagnitude = FScalableFloat(num);
		InfoPrimaryAmmo.ModifierOp = EGameplayModOp::Override;
		InfoPrimaryAmmo.Attribute = UQHAttributeSet::GetReserveAmmoAttributeFromTag(WeaponTag);
	}

	player_character->GetAbilitySystemComponent()->ApplyGameplayEffectToSelf(GEAmmo, 0, player_character->GetAbilitySystemComponent()->MakeEffectContext());
	UFreshHUDEventData* fresh_hud_event = NewObject<UFreshHUDEventData>();
	UXuBPFuncLib::GetEventManager(GetWorld())->BroadcastEvent(EXuEventType::FreshHUD, fresh_hud_event);

	OnAmmoBagPickedUp();
}

void AAmmoBag::OnAmmoBagPickedUp_Implementation()
{
	
}
