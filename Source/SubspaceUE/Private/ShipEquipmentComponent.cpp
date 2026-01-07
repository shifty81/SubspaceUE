// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShipEquipmentComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogShipEquipment, Log, All);

UShipEquipmentComponent::UShipEquipmentComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UShipEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UShipEquipmentComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UShipEquipmentComponent::AddEquipmentSlot(const FEquipmentSlot& Slot)
{
	EquipmentSlots.Add(Slot);
}

bool UShipEquipmentComponent::InstallEquipment(int32 SlotIndex, const FEquipmentItem& Equipment)
{
	if (!EquipmentSlots.IsValidIndex(SlotIndex))
	{
		UE_LOG(LogShipEquipment, Warning, TEXT("Invalid equipment slot index: %d"), SlotIndex);
		return false;
	}

	FEquipmentSlot& Slot = EquipmentSlots[SlotIndex];
	Slot.Equipment = Equipment;
	Slot.bIsOccupied = true;

	UE_LOG(LogShipEquipment, Log, TEXT("Installed %s in slot %d"), *Equipment.ItemName, SlotIndex);
	return true;
}

bool UShipEquipmentComponent::RemoveEquipment(int32 SlotIndex, FEquipmentItem& OutEquipment)
{
	if (!EquipmentSlots.IsValidIndex(SlotIndex))
	{
		return false;
	}

	FEquipmentSlot& Slot = EquipmentSlots[SlotIndex];
	if (!Slot.bIsOccupied)
	{
		return false;
	}

	OutEquipment = Slot.Equipment;
	Slot.bIsOccupied = false;
	Slot.Equipment = FEquipmentItem();

	return true;
}

TArray<FEquipmentSlot> UShipEquipmentComponent::GetSlotsByType(EEquipmentSlotType Type) const
{
	TArray<FEquipmentSlot> Result;
	for (const FEquipmentSlot& Slot : EquipmentSlots)
	{
		if (Slot.SlotType == Type)
		{
			Result.Add(Slot);
		}
	}
	return Result;
}

TArray<FEquipmentSlot> UShipEquipmentComponent::GetWeaponSlots() const
{
	TArray<FEquipmentSlot> Result;
	for (const FEquipmentSlot& Slot : EquipmentSlots)
	{
		if (Slot.SlotType == EEquipmentSlotType::PrimaryWeapon || 
			Slot.SlotType == EEquipmentSlotType::Turret)
		{
			if (Slot.bIsOccupied)
			{
				Result.Add(Slot);
			}
		}
	}
	return Result;
}

float UShipEquipmentComponent::GetTotalPowerConsumption() const
{
	float Total = 0.0f;
	for (const FEquipmentSlot& Slot : EquipmentSlots)
	{
		if (Slot.bIsOccupied)
		{
			Total += Slot.Equipment.PowerConsumption;
		}
	}
	return Total;
}

void UShipEquipmentComponent::SetupUlyssesEquipment()
{
	EquipmentSlots.Empty();

	// Primary Weapon Slot 1 - Forward Left
	FEquipmentSlot PrimarySlot1;
	PrimarySlot1.SlotType = EEquipmentSlotType::PrimaryWeapon;
	PrimarySlot1.SlotName = TEXT("Primary Weapon 1");
	PrimarySlot1.MountPosition = FVector(400.0f, -100.0f, 50.0f);
	PrimarySlot1.MountRotation = FRotator(0.0f, 0.0f, 0.0f);
	PrimarySlot1.bIsOccupied = true;
	PrimarySlot1.Equipment = CreatePulseLaser(1);
	AddEquipmentSlot(PrimarySlot1);

	// Primary Weapon Slot 2 - Forward Right
	FEquipmentSlot PrimarySlot2;
	PrimarySlot2.SlotType = EEquipmentSlotType::PrimaryWeapon;
	PrimarySlot2.SlotName = TEXT("Primary Weapon 2");
	PrimarySlot2.MountPosition = FVector(400.0f, 100.0f, 50.0f);
	PrimarySlot2.MountRotation = FRotator(0.0f, 0.0f, 0.0f);
	PrimarySlot2.bIsOccupied = true;
	PrimarySlot2.Equipment = CreatePulseLaser(1);
	AddEquipmentSlot(PrimarySlot2);

	// Utility Slot 1 - Mining Laser
	FEquipmentSlot UtilitySlot1;
	UtilitySlot1.SlotType = EEquipmentSlotType::Utility;
	UtilitySlot1.SlotName = TEXT("Utility Slot 1");
	UtilitySlot1.MountPosition = FVector(350.0f, 0.0f, -50.0f);
	UtilitySlot1.MountRotation = FRotator(0.0f, 0.0f, 0.0f);
	UtilitySlot1.bIsOccupied = true;
	UtilitySlot1.Equipment = CreateMiningLaser(1);
	AddEquipmentSlot(UtilitySlot1);

	// Utility Slot 2 - Empty (for future expansion)
	FEquipmentSlot UtilitySlot2;
	UtilitySlot2.SlotType = EEquipmentSlotType::Utility;
	UtilitySlot2.SlotName = TEXT("Utility Slot 2");
	UtilitySlot2.MountPosition = FVector(350.0f, 0.0f, 50.0f);
	UtilitySlot2.MountRotation = FRotator(0.0f, 0.0f, 0.0f);
	UtilitySlot2.bIsOccupied = false;
	AddEquipmentSlot(UtilitySlot2);

	// Shield Generator Slot
	FEquipmentSlot ShieldSlot;
	ShieldSlot.SlotType = EEquipmentSlotType::Shield;
	ShieldSlot.SlotName = TEXT("Shield Generator");
	ShieldSlot.MountPosition = FVector(0.0f, 0.0f, 100.0f);
	ShieldSlot.bIsOccupied = true;
	ShieldSlot.Equipment = CreateShieldGenerator(1);
	AddEquipmentSlot(ShieldSlot);

	UE_LOG(LogShipEquipment, Log, TEXT("Ulysses equipment setup complete: %d slots, %.1f W power consumption"),
		EquipmentSlots.Num(), GetTotalPowerConsumption());
}

FEquipmentItem UShipEquipmentComponent::CreatePulseLaser(int32 Level)
{
	FEquipmentItem Item;
	Item.Type = EEquipmentType::PulseLaser;
	Item.ItemName = FString::Printf(TEXT("Pulse Laser Mk%d"), Level);
	Item.Level = Level;
	Item.Damage = 80.0f * Level;
	Item.Range = 1200.0f;
	Item.FireRate = 3.0f;  // 3 shots per second
	Item.ProjectileSpeed = 2500.0f;
	Item.HeatGeneration = 8.0f;
	Item.PowerConsumption = 45.0f * Level;
	Item.Mass = 150.0f;
	Item.Size = 1;
	Item.Description = TEXT("Standard energy weapon. Reliable damage with good fire rate.");
	return Item;
}

FEquipmentItem UShipEquipmentComponent::CreateBeamLaser(int32 Level)
{
	FEquipmentItem Item;
	Item.Type = EEquipmentType::BeamLaser;
	Item.ItemName = FString::Printf(TEXT("Beam Laser Mk%d"), Level);
	Item.Level = Level;
	Item.Damage = 50.0f * Level;  // Lower per-hit but continuous
	Item.Range = 1500.0f;
	Item.FireRate = 10.0f;  // Continuous beam = high fire rate
	Item.ProjectileSpeed = 0.0f;  // Instant hit beam
	Item.HeatGeneration = 15.0f;
	Item.PowerConsumption = 80.0f * Level;
	Item.Mass = 200.0f;
	Item.Size = 2;
	Item.Description = TEXT("Continuous beam weapon. Excellent for sustained damage.");
	return Item;
}

FEquipmentItem UShipEquipmentComponent::CreatePlasmaCannon(int32 Level)
{
	FEquipmentItem Item;
	Item.Type = EEquipmentType::PlasmaCannon;
	Item.ItemName = FString::Printf(TEXT("Plasma Cannon Mk%d"), Level);
	Item.Level = Level;
	Item.Damage = 200.0f * Level;  // High damage
	Item.Range = 800.0f;  // Shorter range
	Item.FireRate = 1.0f;  // Slower fire rate
	Item.ProjectileSpeed = 1500.0f;
	Item.HeatGeneration = 25.0f;
	Item.PowerConsumption = 120.0f * Level;
	Item.Mass = 250.0f;
	Item.Size = 2;
	Item.Description = TEXT("Heavy plasma weapon. High damage at close range.");
	return Item;
}

FEquipmentItem UShipEquipmentComponent::CreateRailgun(int32 Level)
{
	FEquipmentItem Item;
	Item.Type = EEquipmentType::Railgun;
	Item.ItemName = FString::Printf(TEXT("Railgun Mk%d"), Level);
	Item.Level = Level;
	Item.Damage = 350.0f * Level;  // Very high damage
	Item.Range = 2500.0f;  // Very long range
	Item.FireRate = 0.5f;  // Very slow fire rate
	Item.ProjectileSpeed = 5000.0f;  // Very fast projectile
	Item.HeatGeneration = 40.0f;
	Item.PowerConsumption = 200.0f * Level;
	Item.AmmoCapacity = 50;
	Item.CurrentAmmo = 50;
	Item.Mass = 400.0f;
	Item.Size = 3;
	Item.Description = TEXT("High-velocity kinetic weapon. Devastating single shots.");
	return Item;
}

FEquipmentItem UShipEquipmentComponent::CreateMassDriver(int32 Level)
{
	FEquipmentItem Item;
	Item.Type = EEquipmentType::MassDriver;
	Item.ItemName = FString::Printf(TEXT("Mass Driver Mk%d"), Level);
	Item.Level = Level;
	Item.Damage = 120.0f * Level;
	Item.Range = 1800.0f;
	Item.FireRate = 2.0f;
	Item.ProjectileSpeed = 3000.0f;
	Item.HeatGeneration = 12.0f;
	Item.PowerConsumption = 60.0f * Level;
	Item.AmmoCapacity = 200;
	Item.CurrentAmmo = 200;
	Item.Mass = 200.0f;
	Item.Size = 2;
	Item.Description = TEXT("Ballistic kinetic weapon. Good damage and penetration.");
	return Item;
}

FEquipmentItem UShipEquipmentComponent::CreateGatling(int32 Level)
{
	FEquipmentItem Item;
	Item.Type = EEquipmentType::Gatling;
	Item.ItemName = FString::Printf(TEXT("Gatling Cannon Mk%d"), Level);
	Item.Level = Level;
	Item.Damage = 30.0f * Level;  // Low per shot
	Item.Range = 1000.0f;
	Item.FireRate = 15.0f;  // Very high fire rate
	Item.ProjectileSpeed = 2000.0f;
	Item.HeatGeneration = 20.0f;
	Item.PowerConsumption = 40.0f * Level;
	Item.AmmoCapacity = 1000;
	Item.CurrentAmmo = 1000;
	Item.Mass = 180.0f;
	Item.Size = 1;
	Item.Description = TEXT("Rapid-fire ballistic weapon. Suppressive fire and anti-fighter.");
	return Item;
}

FEquipmentItem UShipEquipmentComponent::CreateMissileLauncher(int32 Level)
{
	FEquipmentItem Item;
	Item.Type = EEquipmentType::MissileLauncher;
	Item.ItemName = FString::Printf(TEXT("Missile Launcher Mk%d"), Level);
	Item.Level = Level;
	Item.Damage = 500.0f * Level;  // Very high damage
	Item.Range = 3000.0f;  // Long range
	Item.FireRate = 0.33f;  // 1 missile every 3 seconds
	Item.ProjectileSpeed = 800.0f;  // Slower but guided
	Item.HeatGeneration = 5.0f;
	Item.PowerConsumption = 30.0f * Level;
	Item.AmmoCapacity = 20;
	Item.CurrentAmmo = 20;
	Item.bRequiresLockOn = true;
	Item.Mass = 250.0f;
	Item.Size = 2;
	Item.Description = TEXT("Guided missile launcher. High damage, requires lock-on.");
	return Item;
}

FEquipmentItem UShipEquipmentComponent::CreateTorpedoLauncher(int32 Level)
{
	FEquipmentItem Item;
	Item.Type = EEquipmentType::TorpedoLauncher;
	Item.ItemName = FString::Printf(TEXT("Torpedo Launcher Mk%d"), Level);
	Item.Level = Level;
	Item.Damage = 2000.0f * Level;  // Massive damage
	Item.Range = 5000.0f;  // Very long range
	Item.FireRate = 0.1f;  // 1 torpedo every 10 seconds
	Item.ProjectileSpeed = 600.0f;  // Slow but deadly
	Item.HeatGeneration = 10.0f;
	Item.PowerConsumption = 50.0f * Level;
	Item.AmmoCapacity = 5;
	Item.CurrentAmmo = 5;
	Item.bRequiresLockOn = true;
	Item.Mass = 500.0f;
	Item.Size = 3;
	Item.Description = TEXT("Heavy anti-capital torpedo. Devastating damage to large ships.");
	return Item;
}

FEquipmentItem UShipEquipmentComponent::CreateMiningLaser(int32 Level)
{
	FEquipmentItem Item;
	Item.Type = EEquipmentType::MiningLaser;
	Item.ItemName = FString::Printf(TEXT("Mining Laser Mk%d"), Level);
	Item.Level = Level;
	Item.Damage = 40.0f * Level;  // Lower combat damage
	Item.Range = 500.0f;
	Item.FireRate = 2.0f;
	Item.ProjectileSpeed = 0.0f;  // Instant beam
	Item.MiningPower = 100.0f * Level;  // Resources extracted per second
	Item.PowerConsumption = 75.0f * Level;
	Item.Mass = 120.0f;
	Item.Size = 1;
	Item.Description = TEXT("Extracts resources from asteroids. Essential for resource gathering.");
	return Item;
}

FEquipmentItem UShipEquipmentComponent::CreateSalvageBeam(int32 Level)
{
	FEquipmentItem Item;
	Item.Type = EEquipmentType::SalvageBeam;
	Item.ItemName = FString::Printf(TEXT("Salvage Beam Mk%d"), Level);
	Item.Level = Level;
	Item.Damage = 0.0f;  // No combat damage
	Item.Range = 600.0f;
	Item.FireRate = 1.0f;
	Item.ProjectileSpeed = 0.0f;  // Instant beam
	Item.SalvagePower = 80.0f * Level;  // Materials recovered per second
	Item.PowerConsumption = 60.0f * Level;
	Item.Mass = 100.0f;
	Item.Size = 1;
	Item.Description = TEXT("Recovers materials from ship wrecks. Useful for resource collection.");
	return Item;
}

FEquipmentItem UShipEquipmentComponent::CreateTractorBeam(int32 Level)
{
	FEquipmentItem Item;
	Item.Type = EEquipmentType::TractorBeam;
	Item.ItemName = FString::Printf(TEXT("Tractor Beam Mk%d"), Level);
	Item.Level = Level;
	Item.Damage = 0.0f;
	Item.Range = 400.0f;
	Item.PowerConsumption = 40.0f * Level;
	Item.Mass = 80.0f;
	Item.Size = 1;
	Item.Description = TEXT("Manipulates cargo and small objects. Essential for cargo operations.");
	return Item;
}

FEquipmentItem UShipEquipmentComponent::CreateShieldGenerator(int32 Level)
{
	FEquipmentItem Item;
	Item.Type = EEquipmentType::ShieldGenerator;
	Item.ItemName = FString::Printf(TEXT("Shield Generator Mk%d"), Level);
	Item.Level = Level;
	Item.ShieldCapacity = 1000.0f * Level;
	Item.ShieldRegenRate = 50.0f * Level;
	Item.ShieldRegenDelay = 3.0f;
	Item.PowerConsumption = 100.0f * Level;
	Item.Mass = 200.0f;
	Item.Size = 2;
	Item.Description = FString::Printf(TEXT("Generates %.0f shield points. Regenerates %.0f/s after %.1fs."), 
		Item.ShieldCapacity, Item.ShieldRegenRate, Item.ShieldRegenDelay);
	return Item;
}

FEquipmentItem UShipEquipmentComponent::CreateCountermeasure(int32 Level)
{
	FEquipmentItem Item;
	Item.Type = EEquipmentType::Countermeasure;
	Item.ItemName = FString::Printf(TEXT("Countermeasure Mk%d"), Level);
	Item.Level = Level;
	Item.AmmoCapacity = 20 * Level;
	Item.CurrentAmmo = 20 * Level;
	Item.PowerConsumption = 10.0f;
	Item.Mass = 50.0f;
	Item.Size = 1;
	Item.Description = TEXT("Deploys flares and chaff to evade missiles.");
	return Item;
}

FEquipmentItem UShipEquipmentComponent::CreateCombatEngine(int32 Level)
{
	FEquipmentItem Item;
	Item.Type = EEquipmentType::CombatEngine;
	Item.ItemName = FString::Printf(TEXT("Combat Engine Mk%d"), Level);
	Item.Level = Level;
	Item.CombatSpeed = 120.0f * Level;
	Item.Acceleration = 15.0f * Level;
	Item.ChargeTime = 0.0f;  // Instant
	Item.PowerConsumption = 150.0f * Level;
	Item.Mass = 300.0f;
	Item.Size = 2;
	Item.Description = TEXT("Optimized for combat maneuvers. Instant acceleration, lower top speed.");
	return Item;
}

FEquipmentItem UShipEquipmentComponent::CreateTravelEngine(int32 Level)
{
	FEquipmentItem Item;
	Item.Type = EEquipmentType::TravelEngine;
	Item.ItemName = FString::Printf(TEXT("Travel Engine Mk%d"), Level);
	Item.Level = Level;
	Item.TravelSpeed = 500.0f * Level;  // Much higher top speed
	Item.Acceleration = 5.0f * Level;  // Slower acceleration
	Item.ChargeTime = 3.0f;  // Requires charge-up
	Item.PowerConsumption = 250.0f * Level;
	Item.Mass = 400.0f;
	Item.Size = 3;
	Item.Description = TEXT("High-speed travel engine. Requires charge-up, excellent for long distances.");
	return Item;
}

FEquipmentItem UShipEquipmentComponent::CreateAllRoundEngine(int32 Level)
{
	FEquipmentItem Item;
	Item.Type = EEquipmentType::AllRoundEngine;
	Item.ItemName = FString::Printf(TEXT("All-Round Engine Mk%d"), Level);
	Item.Level = Level;
	Item.CombatSpeed = 100.0f * Level;
	Item.TravelSpeed = 300.0f * Level;
	Item.Acceleration = 10.0f * Level;
	Item.ChargeTime = 1.0f;
	Item.PowerConsumption = 180.0f * Level;
	Item.Mass = 320.0f;
	Item.Size = 2;
	Item.Description = TEXT("Balanced engine. Good for both combat and travel.");
	return Item;
}

FEquipmentItem UShipEquipmentComponent::CreatePowerReactor(int32 Level)
{
	FEquipmentItem Item;
	Item.Type = EEquipmentType::PowerReactor;
	Item.ItemName = FString::Printf(TEXT("Power Reactor Mk%d"), Level);
	Item.Level = Level;
	Item.PowerConsumption = -500.0f * Level;  // Negative = generates power
	Item.Mass = 500.0f;
	Item.Size = 3;
	Item.Description = FString::Printf(TEXT("Generates %.0f W of power for ship systems."), 
		500.0f * Level);
	return Item;
}

FEquipmentItem UShipEquipmentComponent::CreateCargoExtension(int32 Level)
{
	FEquipmentItem Item;
	Item.Type = EEquipmentType::CargoExtension;
	Item.ItemName = FString::Printf(TEXT("Cargo Extension Mk%d"), Level);
	Item.Level = Level;
	Item.CargoBonus = 100 * Level;
	Item.PowerConsumption = 20.0f;
	Item.Mass = 200.0f;
	Item.Size = 2;
	Item.Description = FString::Printf(TEXT("Adds %d cargo capacity."), Item.CargoBonus);
	return Item;
}

FEquipmentItem UShipEquipmentComponent::CreateDockingComputer(int32 Level)
{
	FEquipmentItem Item;
	Item.Type = EEquipmentType::DockingComputer;
	Item.ItemName = FString::Printf(TEXT("Docking Computer Mk%d"), Level);
	Item.Level = Level;
	Item.PowerConsumption = 30.0f;
	Item.Mass = 50.0f;
	Item.Size = 1;
	Item.Description = TEXT("Automates docking procedures. Required for auto-pilot docking.");
	return Item;
}

FEquipmentItem UShipEquipmentComponent::CreateScanner(int32 Level)
{
	FEquipmentItem Item;
	Item.Type = EEquipmentType::LongRangeScanner;
	Item.ItemName = FString::Printf(TEXT("Scanner Mk%d"), Level);
	Item.Level = Level;
	Item.ScanRange = 5000.0f * Level;
	Item.PowerConsumption = 50.0f * Level;
	Item.Mass = 100.0f;
	Item.Size = 1;
	Item.Description = FString::Printf(TEXT("Detects ships and objects up to %.0f m away."), 
		Item.ScanRange);
	return Item;
}
