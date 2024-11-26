// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileGameplayAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "XuKit/AbilitySystem/QHGameplayTags.h"
#include "XuKit/Actor/Casing/Casing.h"
#include "XuKit/Actor/Projectile/Projectile.h"
#include "XuKit/Actor/Weapon/ProjectileWeapon/ProjectionWeapon.h"
#include "XuKit/Interface/CombatInterface.h"

void UProjectileGameplayAbility::ApplyCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const
{
	//Super::ApplyCooldown(Handle, ActorInfo, ActivationInfo);
	UGameplayEffect* CooldownGE = GetCooldownGameplayEffect();
	if (CooldownGE)
	{
		ICombatInterface* combat_interface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
		if (!combat_interface)return;

		AProjectionWeapon* projection_weapon = ICombatInterface::Execute_get_cur_projection_weapon(GetAvatarActorFromActorInfo());
		if (!projection_weapon)return;	

		float Fire_delay = projection_weapon->weapon_info.weapon_fire_delay;

		FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(CooldownGameplayEffectClass, GetAbilityLevel());
		SpecHandle.Data.Get()->SetSetByCallerMagnitude(cooldown_tag, Fire_delay);
		ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, SpecHandle);
	}
}

void UProjectileGameplayAbility::SpawnProjectile(FVector targetLocation, FGameplayTag socketTag)
{
	//XuPRINT_ShowInScreen(TEXT("SpawnProjectile"));
	if (!GetAvatarActorFromActorInfo()->HasAuthority())return;

	ICombatInterface* combat_interface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (!combat_interface)return;

	AProjectionWeapon* projection_weapon = ICombatInterface::Execute_get_cur_projection_weapon(GetAvatarActorFromActorInfo());
	if (!projection_weapon)return;

	FTransform spawn_transform;
	FVector ammoLocation = projection_weapon->GetProjectileSpawnLocation();
	FRotator ammoRotation = (targetLocation - GetAvatarActorFromActorInfo()->GetActorLocation()).Rotation();
	ammoRotation.Pitch = 0;
	spawn_transform.SetLocation(ammoLocation);
	spawn_transform.SetRotation(ammoRotation.Quaternion());

	//画球体
	//DrawDebugSphere(GetWorld(), ammoLocation, 10, 10, FColor::Red, false, 1);

	//生成子弹
	AProjectile* projectile = GetWorld()->SpawnActorDeferred<AProjectile>(projection_weapon->projectionClass, spawn_transform, GetOwningActorFromActorInfo(),
	                                                                      Cast<APawn>(GetAvatarActorFromActorInfo()), ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	UAbilitySystemComponent* abs = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwningActorFromActorInfo());
	FGameplayEffectContextHandle effect_context_handle = abs->MakeEffectContext();
	FGameplayEffectSpecHandle effect_spec_handle = abs->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), effect_context_handle);
	projectile->EffectHandle = effect_spec_handle;

	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(effect_spec_handle, QHGameplayTags::Get().DamageTag, damageValue);

	projectile->FinishSpawning(spawn_transform);
	//生成弹壳
	if (projection_weapon->casingClass)
	{
		FTransform casing_transform;
		FVector casingLocation = projection_weapon->GetCasingSpawnLocation();
		casing_transform.SetLocation(casingLocation);
		casing_transform.SetRotation(ammoRotation.Quaternion());

		GetWorld()->SpawnActor<ACasing>(projection_weapon->casingClass, casing_transform);
	}

	projection_weapon->Fire();
}

void UProjectileGameplayAbility::SpawnShotGunProjectile(FVector targetLocation, FGameplayTag socketTag, int num,int angleValue)
{
	if (!GetAvatarActorFromActorInfo()->HasAuthority())return;

	ICombatInterface* combat_interface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (!combat_interface)return;

	AProjectionWeapon* projection_weapon = ICombatInterface::Execute_get_cur_projection_weapon(GetAvatarActorFromActorInfo());
	if (!projection_weapon)return;

	//生成一个球型Debug
	DrawDebugSphere(GetWorld(), targetLocation, 30, 30, FColor::Red, false, 1);
	FVector newLocationDir = targetLocation - GetAvatarActorFromActorInfo()->GetActorLocation();
	//从枪口生成num个子弹，每个子弹的方向是 newLocationDir的均匀（-30，30）角度偏移

	for (int i = 0; i < num; ++i)
	{
		FVector newDir = newLocationDir;
		float zz = angleValue*2/num *i-angleValue;
		
		newDir = newDir.RotateAngleAxis(zz, FVector(0, 0, 1));
		FVector ammoLocation = projection_weapon->GetProjectileSpawnLocation();

		DrawDebugLine(GetWorld(), ammoLocation, ammoLocation + newDir * 1000, FColor::Red, false, 1);
		SpawnProjectile(ammoLocation + newDir * 1000, socketTag);
		
	}
	
	

	
	
}
