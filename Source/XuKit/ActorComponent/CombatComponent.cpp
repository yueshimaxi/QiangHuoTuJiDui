

#include "CombatComponent.h"

#include "Net/UnrealNetwork.h"
#include "XuKit/Actor/Weapon/Weapon.h"
#include "XuKit/Actor/Weapon/ProjectileWeapon/ProjectionWeapon.h"
#include "XuKit/Character/PlayerCharacter.h"

UCombatComponent::UCombatComponent()
{
	
	PrimaryComponentTick.bCanEverTick = true;

}


void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UCombatComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UCombatComponent, equipped_projection_weapon);

}

AProjectionWeapon* UCombatComponent::GetCurProjectionWeapon()
{
	return equipped_projection_weapon;
}

void UCombatComponent::OnRep_EquippedWeapon()
{
	
}

void UCombatComponent::EquipWeapon(AProjectionWeapon* weapon)
{
	Server_EquipWeapon(weapon);
}

void UCombatComponent::Server_EquipWeapon_Implementation(AProjectionWeapon* weapon)
{
	if (!owner_character || !weapon)
	{
		return;
	}
	equipped_projection_weapon = weapon;
	equipped_projection_weapon->SetWeaponState(EWeaponState::EWS_Equiped);
	equipped_projection_weapon->AttachToComponent(owner_character->GetMesh(),FAttachmentTransformRules::SnapToTargetNotIncludingScale,owner_character->WeaponAttackSocket);
	equipped_projection_weapon->SetOwner(owner_character);
}

void UCombatComponent::DropWeapon()
{
	
}

void UCombatComponent::Server_DropWeapon_Implementation()
{
	
}

