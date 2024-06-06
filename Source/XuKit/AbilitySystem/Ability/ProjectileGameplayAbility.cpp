// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileGameplayAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "XuKit/AbilitySystem/QHGameplayTags.h"
#include "XuKit/Actor/Projectile/Projectile.h"
#include "XuKit/Actor/Weapon/ProjectileWeapon/ProjectionWeapon.h"
#include "XuKit/Interface/CombatInterface.h"

void UProjectileGameplayAbility::SpawnProjectile(FVector targetLocation, FGameplayTag socketTag, bool overridePitch, float pitch)
{
	//XuPRINT_ShowInScreen(TEXT("SpawnProjectile"));
	if (!GetAvatarActorFromActorInfo()->HasAuthority())return;

	ICombatInterface* combat_interface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (!combat_interface)return;

	AProjectionWeapon* projection_weapon = ICombatInterface::Execute_get_cur_projection_weapon(GetAvatarActorFromActorInfo());
	if (!projection_weapon)return;

	FTransform spawn_transform;
	FVector weaponLocation = ICombatInterface::Execute_GetCombatSocketLocation(GetAvatarActorFromActorInfo(), socketTag);
	FRotator rotation = (targetLocation - weaponLocation).Rotation();
	rotation.Pitch = 0;
	spawn_transform.SetLocation(weaponLocation);
	//画球体
	DrawDebugSphere(GetWorld(), weaponLocation, 10, 10, FColor::Red, false, 1);
	spawn_transform.SetRotation(rotation.Quaternion());


	AProjectile* projectile = GetWorld()->SpawnActorDeferred<AProjectile>(projection_weapon->projectionClass, spawn_transform, GetOwningActorFromActorInfo(),
	                                                                      Cast<APawn>(GetAvatarActorFromActorInfo()), ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	UAbilitySystemComponent* abs = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwningActorFromActorInfo());
	FGameplayEffectContextHandle effect_context_handle = abs->MakeEffectContext();
	FGameplayEffectSpecHandle effect_spec_handle = abs->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), effect_context_handle);
	projectile->EffectHandle = effect_spec_handle;

	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(effect_spec_handle, QHGameplayTags::Get().DamageTag, damageValue);

	projectile->FinishSpawning(spawn_transform);
	//XuPRINT_ShowInScreen(TEXT("FinishSpawning"));
}
