// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShipEquipmentComponent.h"

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
		UE_LOG(LogTemp, Warning, TEXT("Invalid equipment slot index: %d"), SlotIndex);
		return false;
	}

	FEquipmentSlot& Slot = EquipmentSlots[SlotIndex];
	Slot.Equipment = Equipment;
	Slot.bIsOccupied = true;

	UE_LOG(LogTemp, Log, TEXT("Installed %s in slot %d"), *Equipment.ItemName, SlotIndex);
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

	UE_LOG(LogTemp, Log, TEXT("Ulysses equipment setup complete: %d slots, %.1f W power consumption"),
		EquipmentSlots.Num(), GetTotalPowerConsumption());
}

FEquipmentItem UShipEquipmentComponent::CreatePulseLaser(int32 Level)
{
	FEquipmentItem Item;
	Item.Type = EEquipmentType::PulseLaser;
	Item.ItemName = FString::Printf(TEXT("Pulse Laser Mk%d"), Level);
	Item.Level = Level;
	Item.Damage = 100.0f * Level;
	Item.Range = 1000.0f;
	Item.PowerConsumption = 50.0f * Level;
	Item.FireRate = 2.0f;  // 2 shots per second
	Item.Description = TEXT("Standard energy weapon. Good balance of damage and fire rate.");
	return Item;
}

FEquipmentItem UShipEquipmentComponent::CreateMiningLaser(int32 Level)
{
	FEquipmentItem Item;
	Item.Type = EEquipmentType::MiningLaser;
	Item.ItemName = FString::Printf(TEXT("Mining Laser Mk%d"), Level);
	Item.Level = Level;
	Item.Damage = 50.0f * Level;  // Lower damage but extracts resources
	Item.Range = 500.0f;
	Item.PowerConsumption = 75.0f * Level;
	Item.FireRate = 1.0f;
	Item.Description = TEXT("Extracts resources from asteroids. Essential for resource gathering.");
	return Item;
}

FEquipmentItem UShipEquipmentComponent::CreateShieldGenerator(int32 Level)
{
	FEquipmentItem Item;
	Item.Type = EEquipmentType::ShieldGenerator;
	Item.ItemName = FString::Printf(TEXT("Shield Generator Mk%d"), Level);
	Item.Level = Level;
	Item.Damage = 0.0f;
	Item.Range = 0.0f;
	Item.PowerConsumption = 100.0f * Level;
	Item.FireRate = 0.0f;
	Item.Description = FString::Printf(TEXT("Generates %.0f shield points. Regenerates shields over time."), 
		750.0f * Level);
	return Item;
}
