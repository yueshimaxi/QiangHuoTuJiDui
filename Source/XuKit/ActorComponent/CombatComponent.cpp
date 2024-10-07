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
	DOREPLIFETIME(UCombatComponent, own_projection_weapons);
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

void UCombatComponent::Server_EquipWeapon_Implementation(AProjectionWeapon* projectile_weapon)
{
	if (!owner_character || own_projection_weapons.Num() >= max_Projectile_Weapon_Num)
	{
		return;
	}
	if (equipped_projection_weapon == nullptr)
	{
		equipped_projection_weapon = projectile_weapon;
		equipped_projection_weapon->SetOwner(owner_character);
		equipped_projection_weapon->AttachToComponent(owner_character->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, owner_character->WeaponAttackSocket);
		equipped_projection_weapon->SetWeaponState(EWeaponState::EWS_Equiped);
	}
	else
	{
		equipped_projection_weapon->SetOwner(owner_character);
		projectile_weapon->SetWeaponState(EWeaponState::EWS_Backpack);

	}
	projectile_weapon->OwningCharacter=owner_character;
	projectile_weapon->AddAbilities();
	//包含丢枪切换新枪，和捡到新枪俩种情况
	own_projection_weapons.AddUnique(projectile_weapon);
}

void UCombatComponent::AddToInventy(AWeapon* weapon)
{
	
}

void UCombatComponent::DropWeapon()
{
	if (equipped_projection_weapon && own_projection_weapons.Num() > 1)
	{
		Server_DropWeapon();
	}
}


void UCombatComponent::Server_DropWeapon_Implementation()
{
	equipped_projection_weapon->OwningCharacter=nullptr;
	equipped_projection_weapon->RemoveAbilities();
	equipped_projection_weapon->SetWeaponState(EWeaponState::EWS_Dropped);
	equipped_projection_weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	equipped_projection_weapon->SetOwner(nullptr);
	own_projection_weapons.RemoveAt(0);
	if (own_projection_weapons.Num() > 0)
	{
		equipped_projection_weapon = own_projection_weapons[0];
		equipped_projection_weapon->SetOwner(owner_character);
		equipped_projection_weapon->SetWeaponState(EWeaponState::EWS_Equiped);
		equipped_projection_weapon->AttachToComponent(owner_character->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, owner_character->WeaponAttackSocket);
	}
	else
	{
		equipped_projection_weapon = nullptr;
	}

}


void UCombatComponent::SwapWeapon(bool forward)
{
	Server_SwapWeapon(forward);
}

void UCombatComponent::Server_SwapWeapon_Implementation(bool forward)
{
	if (own_projection_weapons.Num() > 1)
	{
		AProjectionWeapon* temp = equipped_projection_weapon;
		temp->SetWeaponState(EWeaponState::EWS_Backpack);
		equipped_projection_weapon=nullptr;
		if (forward)
		{
		
			currentIndex += 1;
			if (currentIndex >= own_projection_weapons.Num())
			{
				currentIndex = 0;
			}
	
		}
		else
		{
			currentIndex -= 1;
			if (currentIndex < 0)
			{
				currentIndex = own_projection_weapons.Num() - 1;
			}
		}
		EquipWeapon(own_projection_weapons[currentIndex]);

		}
}
