// Copyright Epic Games, Inc. All Rights Reserved.

#include "UlyssesShip.h"
#include "ShipInteriorComponent.h"
#include "ShipEquipmentComponent.h"
#include "Components/StaticMeshComponent.h"

AUlyssesShip::AUlyssesShip()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create ship mesh component
	ShipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	RootComponent = ShipMesh;
	ShipMesh->SetSimulatePhysics(false); // We handle physics manually
	ShipMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	// Create interior component
	Interior = CreateDefaultSubobject<UShipInteriorComponent>(TEXT("Interior"));

	// Create equipment component
	Equipment = CreateDefaultSubobject<UShipEquipmentComponent>(TEXT("Equipment"));

	// Initialize stats
	CurrentHull = 0.0f;
	CurrentShield = 0.0f;
	CurrentEnergy = 0.0f;
	Velocity = FVector::ZeroVector;
}

void AUlyssesShip::BeginPlay()
{
	Super::BeginPlay();

	InitializeUlysses();
}

void AUlyssesShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Regenerate shields over time
	RegenerateShields(DeltaTime);

	// Regenerate energy
	if (CurrentEnergy < Stats.PowerGeneration)
	{
		CurrentEnergy = FMath::Min(CurrentEnergy + (Stats.PowerGeneration * DeltaTime * 0.1f), Stats.PowerGeneration);
	}
}

void AUlyssesShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AUlyssesShip::InitializeUlysses()
{
	// Setup configuration
	Config.ShipClass = EX4ShipClass::Corvette;
	Config.DesignStyle = EX4DesignStyle::Balanced;
	Config.Variant = EX4ShipVariant::Standard;
	Config.ShipName = TEXT("Ulysses");
	Config.Material = TEXT("Iron");

	// Setup default stats
	SetupDefaultStats();

	// Initialize current values
	CurrentHull = Stats.MaxHull;
	CurrentShield = Stats.MaxShield;
	CurrentEnergy = Stats.PowerGeneration;

	// Setup equipment
	SetupDefaultEquipment();

	// Setup interior
	SetupInterior();

	UE_LOG(LogTemp, Log, TEXT("Ulysses initialized: Hull=%.0f, Shield=%.0f, Speed=%.1f m/s"), 
		Stats.MaxHull, Stats.MaxShield, Stats.MaxSpeed);
}

void AUlyssesShip::SetupDefaultStats()
{
	// Ulysses Corvette-class default statistics
	Stats.Hull = 1500.0f;
	Stats.MaxHull = 1500.0f;
	Stats.Shield = 750.0f;
	Stats.MaxShield = 750.0f;
	Stats.Mass = 500.0f;
	Stats.MaxSpeed = 80.0f;  // m/s
	Stats.Thrust = 5000.0f;  // N
	Stats.TurnRate = 2.0f;   // rad/s
	Stats.CargoCapacity = 50;
	Stats.PowerGeneration = 500.0f;  // W
	Stats.PowerConsumption = 100.0f; // W
	Stats.PrimaryWeaponSlots = 2;    // 2x Pulse Lasers
	Stats.TurretSlots = 0;
	Stats.UtilitySlots = 2;          // 1x Mining Laser + 1 free slot
}

void AUlyssesShip::SetupDefaultEquipment()
{
	if (!Equipment)
	{
		return;
	}

	// Equipment will be setup via the ShipEquipmentComponent
	// Default equipment:
	// - 2x Pulse Lasers (Primary Weapons)
	// - 1x Mining Laser (Utility)
	// - Basic Shield Generator
	// - Basic Power Generator

	UE_LOG(LogTemp, Log, TEXT("Ulysses equipment setup: %d primary weapons, %d utility slots"),
		Stats.PrimaryWeaponSlots, Stats.UtilitySlots);
}

void AUlyssesShip::SetupInterior()
{
	if (!Interior)
	{
		return;
	}

	// Interior will be setup via the ShipInteriorComponent
	// Ulysses has 4 interior rooms:
	// 1. Cockpit/Bridge - Command center
	// 2. Crew Quarters - Living space
	// 3. Cargo Bay - Storage area
	// 4. Engine Room - Power systems

	UE_LOG(LogTemp, Log, TEXT("Ulysses interior setup complete"));
}

float AUlyssesShip::GetHullPercentage() const
{
	if (Stats.MaxHull <= 0.0f) return 0.0f;
	return (CurrentHull / Stats.MaxHull) * 100.0f;
}

float AUlyssesShip::GetShieldPercentage() const
{
	if (Stats.MaxShield <= 0.0f) return 0.0f;
	return (CurrentShield / Stats.MaxShield) * 100.0f;
}

float AUlyssesShip::GetEnergyPercentage() const
{
	if (Stats.PowerGeneration <= 0.0f) return 0.0f;
	return (CurrentEnergy / Stats.PowerGeneration) * 100.0f;
}

void AUlyssesShip::TakeDamage(float Amount)
{
	if (Amount <= 0.0f) return;

	// Shields absorb damage first
	if (CurrentShield > 0.0f)
	{
		float ShieldDamage = FMath::Min(Amount, CurrentShield);
		CurrentShield -= ShieldDamage;
		Amount -= ShieldDamage;
	}

	// Remaining damage goes to hull
	if (Amount > 0.0f)
	{
		CurrentHull = FMath::Max(0.0f, CurrentHull - Amount);
		
		if (CurrentHull <= 0.0f)
		{
			// Ship destroyed
			UE_LOG(LogTemp, Warning, TEXT("Ulysses destroyed!"));
			// TODO: Handle ship destruction
		}
	}
}

void AUlyssesShip::RegenerateShields(float DeltaTime)
{
	if (CurrentShield < Stats.MaxShield)
	{
		// Shields regenerate at 10% of max per second
		float RegenRate = Stats.MaxShield * 0.1f;
		CurrentShield = FMath::Min(CurrentShield + (RegenRate * DeltaTime), Stats.MaxShield);
	}
}
