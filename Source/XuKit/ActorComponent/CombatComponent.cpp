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
	DOREPLIFETIME(UCombatComponent, Inventory);
}

AWeapon* UCombatComponent::GetCurProjectionWeapon()
{
	return CurrentWeapon;
}

void UCombatComponent::EquipWeapon(AWeapon* weapon)
{
	if (weapon)
	{
		CurrentWeapon = weapon;
		weapon->SetWeaponState(EWeaponState::EWS_Equiped);
	}
}

void UCombatComponent::UnEquipCurrentWeapon()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->SetWeaponState(EWeaponState::EWS_Backpack);
		CurrentWeapon = nullptr;
	}
}


void UCombatComponent::DropWeapon(AWeapon* weapon)
{
	if (weapon)
	{
		weapon->SetWeaponState(EWeaponState::EWS_Dropped);
	}
}


void UCombatComponent::SwapWeapon(bool forward)
{
	Server_SwapWeapon(forward);
}

void UCombatComponent::Server_SwapWeapon_Implementation(bool forward)
{
	Multicast_SwapWeapon(forward);
}

void UCombatComponent::Multicast_SwapWeapon_Implementation(bool forward)
{
	if (Inventory.Weapons.Num() > 1)
	{
		if (forward)
		{
			currentIndex += 1;
			if (currentIndex >= Inventory.Weapons.Num())
			{
				currentIndex = 0;
			}
		}
		else
		{
			currentIndex -= 1;
			if (currentIndex < 0)
			{
				currentIndex = Inventory.Weapons.Num() - 1;
			}
		}

		UnEquipCurrentWeapon();
		EquipWeapon(Inventory.Weapons[currentIndex]);
	}
}

void UCombatComponent::AddWeaponToInventory(AWeapon* NewWeapon, bool bEquipWeapon)
{
	Server_AddWeaponToInventory(NewWeapon, bEquipWeapon);
}

void UCombatComponent::Server_AddWeaponToInventory_Implementation(AWeapon* NewWeapon, bool bEquipWeapon)
{
	Multicast_AddWeaponToInventory(NewWeapon, bEquipWeapon);
}

void UCombatComponent::Multicast_AddWeaponToInventory_Implementation(AWeapon* NewWeapon, bool bEquipWeapon)
{
	Inventory.Weapons.Add(NewWeapon);
	NewWeapon->OwningCharacter = owner_character;
	NewWeapon->SetOwner(owner_character);

	NewWeapon->AddAbilities();

	if (bEquipWeapon)
	{
		UnEquipCurrentWeapon();
		EquipWeapon(NewWeapon);
	}
	else
	{
		NewWeapon->SetWeaponState(EWeaponState::EWS_Backpack);
	}
}

void UCombatComponent::RemoveWeaponFromInventory(AWeapon* WeaponToRemove)
{
	Server_RemoveWeaponFromInventory(WeaponToRemove);
}

void UCombatComponent::Server_RemoveWeaponFromInventory_Implementation(AWeapon* WeaponToRemove)
{
	Multicast_RemoveWeaponFromInventory(WeaponToRemove);
}

void UCombatComponent::Multicast_RemoveWeaponFromInventory_Implementation(AWeapon* WeaponToRemove)
{
	if (DoesWeaponExistInInventory(WeaponToRemove))
	{
		DropWeapon(WeaponToRemove);
		Inventory.Weapons.Remove(WeaponToRemove);
		WeaponToRemove->RemoveAbilities();
		WeaponToRemove->OwningCharacter = (nullptr);
		WeaponToRemove->SetOwner(nullptr);
		CurrentWeapon = nullptr;

		if (WeaponToRemove == CurrentWeapon)
		{
			if (Inventory.Weapons.Num() > 0)
			{
				CurrentWeapon = Inventory.Weapons[0];
				EquipWeapon(CurrentWeapon);
			}
		}
	}
}

void UCombatComponent::RemoveAllWeaponsFromInventory()
{
	Server_RemoveAllWeaponsFromInventory();
}

void UCombatComponent::Server_RemoveAllWeaponsFromInventory_Implementation()
{
	Multicast_RemoveAllWeaponsFromInventory();
}

void UCombatComponent::Multicast_RemoveAllWeaponsFromInventory_Implementation()
{
	for (int32 i = Inventory.Weapons.Num() - 1; i >= 0; i--)
	{
		AWeapon* Weapon = Inventory.Weapons[i];
		DropWeapon(Weapon);
		Inventory.Weapons.Remove(Weapon);
		Weapon->RemoveAbilities();
		Weapon->OwningCharacter = (nullptr);
		Weapon->SetOwner(nullptr);
	}
	CurrentWeapon = nullptr;
}

bool UCombatComponent::DoesWeaponExistInInventory(AWeapon* InWeapon)
{
	for (AWeapon* Weapon : Inventory.Weapons)
	{
		if (Weapon && InWeapon && Weapon->GetClass() == InWeapon->GetClass())
		{
			return true;
		}
	}

	return false;
}

void UCombatComponent::OnRep_Inventory()
{
}
