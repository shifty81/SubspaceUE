// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShipEquipmentComponent.generated.h"

/**
 * Equipment slot types
 */
UENUM(BlueprintType)
enum class EEquipmentSlotType : uint8
{
	PrimaryWeapon UMETA(DisplayName = "Primary Weapon"),
	Turret UMETA(DisplayName = "Turret"),
	Utility UMETA(DisplayName = "Utility"),
	Shield UMETA(DisplayName = "Shield Generator"),
	Engine UMETA(DisplayName = "Engine"),
	PowerGenerator UMETA(DisplayName = "Power Generator")
};

/**
 * Equipment types (X4-inspired comprehensive system)
 */
UENUM(BlueprintType)
enum class EEquipmentType : uint8
{
	// Energy Weapons
	PulseLaser UMETA(DisplayName = "Pulse Laser"),
	BeamLaser UMETA(DisplayName = "Beam Laser"),
	PlasmaCannon UMETA(DisplayName = "Plasma Cannon"),
	
	// Ballistic Weapons
	Railgun UMETA(DisplayName = "Railgun"),
	MassDriver UMETA(DisplayName = "Mass Driver"),
	Gatling UMETA(DisplayName = "Gatling Cannon"),
	
	// Missiles
	MissileLauncher UMETA(DisplayName = "Missile Launcher"),
	TorpedoLauncher UMETA(DisplayName = "Torpedo Launcher"),
	MineLauncher UMETA(DisplayName = "Mine Launcher"),
	
	// Utility Tools
	MiningLaser UMETA(DisplayName = "Mining Laser"),
	SalvageBeam UMETA(DisplayName = "Salvage Beam"),
	TractorBeam UMETA(DisplayName = "Tractor Beam"),
	
	// Defensive Systems
	ShieldGenerator UMETA(DisplayName = "Shield Generator"),
	Countermeasure UMETA(DisplayName = "Countermeasure"),
	ArmorPlating UMETA(DisplayName = "Armor Plating"),
	
	// Engines
	CombatEngine UMETA(DisplayName = "Combat Engine"),
	TravelEngine UMETA(DisplayName = "Travel Engine"),
	AllRoundEngine UMETA(DisplayName = "All-Round Engine"),
	
	// Power & Systems
	PowerReactor UMETA(DisplayName = "Power Reactor"),
	CargoExtension UMETA(DisplayName = "Cargo Extension"),
	DockingComputer UMETA(DisplayName = "Docking Computer"),
	LongRangeScanner UMETA(DisplayName = "Long Range Scanner"),
	TradingSoftware UMETA(DisplayName = "Trading Software")
};

/**
 * Equipment item data (X4-style comprehensive stats)
 */
USTRUCT(BlueprintType)
struct FEquipmentItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	EEquipmentType Type = EEquipmentType::PulseLaser;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	FString ItemName = TEXT("Unnamed Equipment");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	int32 Level = 1;

	// Weapon Stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment|Weapon")
	float Damage = 100.0f;  // Base damage per shot

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment|Weapon")
	float Range = 1000.0f;  // Maximum effective range (m)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment|Weapon")
	float FireRate = 1.0f;  // Shots per second

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment|Weapon")
	float ProjectileSpeed = 2000.0f;  // m/s (0 = instant hit)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment|Weapon")
	float HeatGeneration = 10.0f;  // Heat per shot

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment|Weapon")
	int32 AmmoCapacity = 0;  // 0 = unlimited (energy weapons)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment|Weapon")
	int32 CurrentAmmo = 0;

	// Turret-specific
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment|Turret")
	float TrackingSpeed = 2.0f;  // rad/s for turrets

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment|Turret")
	float ArcAngle = 180.0f;  // Firing arc in degrees

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment|Turret")
	bool bRequiresLockOn = false;  // For guided missiles

	// Engine Stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment|Engine")
	float TravelSpeed = 0.0f;  // Max speed in travel mode

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment|Engine")
	float CombatSpeed = 0.0f;  // Max speed in combat

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment|Engine")
	float Acceleration = 0.0f;  // Thrust multiplier

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment|Engine")
	float ChargeTime = 0.0f;  // Charge time for travel engines

	// Shield Stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment|Shield")
	float ShieldCapacity = 0.0f;  // Maximum shield points

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment|Shield")
	float ShieldRegenRate = 0.0f;  // Points per second

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment|Shield")
	float ShieldRegenDelay = 3.0f;  // Seconds after damage

	// Utility Stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment|Utility")
	float MiningPower = 0.0f;  // Resources per second

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment|Utility")
	float SalvagePower = 0.0f;  // Materials per second

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment|Utility")
	float ScanRange = 0.0f;  // Scanner range (m)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment|Utility")
	int32 CargoBonus = 0;  // Additional cargo capacity

	// General Stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	float PowerConsumption = 50.0f;  // W

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	float Mass = 100.0f;  // kg

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	int32 Size = 1;  // 1=S, 2=M, 3=L

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	FString Description = TEXT("");
};

/**
 * Equipment slot data
 */
USTRUCT(BlueprintType)
struct FEquipmentSlot
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment Slot")
	EEquipmentSlotType SlotType = EEquipmentSlotType::PrimaryWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment Slot")
	FString SlotName = TEXT("Slot");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment Slot")
	bool bIsOccupied = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment Slot")
	FEquipmentItem Equipment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment Slot")
	FVector MountPosition = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment Slot")
	FRotator MountRotation = FRotator::ZeroRotator;
};

/**
 * Component that manages ship equipment (weapons, utilities, engines)
 * X4-style modular equipment system
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SUBSPACEUE_API UShipEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UShipEquipmentComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** All equipment slots on the ship */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	TArray<FEquipmentSlot> EquipmentSlots;

	/** Add an equipment slot */
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void AddEquipmentSlot(const FEquipmentSlot& Slot);

	/** Install equipment in a slot by index */
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	bool InstallEquipment(int32 SlotIndex, const FEquipmentItem& Equipment);

	/** Remove equipment from a slot by index */
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	bool RemoveEquipment(int32 SlotIndex, FEquipmentItem& OutEquipment);

	/** Get equipment slots by type */
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	TArray<FEquipmentSlot> GetSlotsByType(EEquipmentSlotType Type) const;

	/** Get all occupied weapon slots */
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	TArray<FEquipmentSlot> GetWeaponSlots() const;

	/** Get total power consumption */
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	float GetTotalPowerConsumption() const;

	/** Setup default Ulysses equipment */
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void SetupUlyssesEquipment();

protected:
	/** Create equipment items - Energy Weapons */
	FEquipmentItem CreatePulseLaser(int32 Level = 1);
	FEquipmentItem CreateBeamLaser(int32 Level = 1);
	FEquipmentItem CreatePlasmaCannon(int32 Level = 1);
	
	/** Create equipment items - Ballistic Weapons */
	FEquipmentItem CreateRailgun(int32 Level = 1);
	FEquipmentItem CreateMassDriver(int32 Level = 1);
	FEquipmentItem CreateGatling(int32 Level = 1);
	
	/** Create equipment items - Missiles */
	FEquipmentItem CreateMissileLauncher(int32 Level = 1);
	FEquipmentItem CreateTorpedoLauncher(int32 Level = 1);
	
	/** Create equipment items - Utility */
	FEquipmentItem CreateMiningLaser(int32 Level = 1);
	FEquipmentItem CreateSalvageBeam(int32 Level = 1);
	FEquipmentItem CreateTractorBeam(int32 Level = 1);
	
	/** Create equipment items - Defensive */
	FEquipmentItem CreateShieldGenerator(int32 Level = 1);
	FEquipmentItem CreateCountermeasure(int32 Level = 1);
	
	/** Create equipment items - Engines */
	FEquipmentItem CreateCombatEngine(int32 Level = 1);
	FEquipmentItem CreateTravelEngine(int32 Level = 1);
	FEquipmentItem CreateAllRoundEngine(int32 Level = 1);
	
	/** Create equipment items - Systems */
	FEquipmentItem CreatePowerReactor(int32 Level = 1);
	FEquipmentItem CreateCargoExtension(int32 Level = 1);
	FEquipmentItem CreateDockingComputer(int32 Level = 1);
	FEquipmentItem CreateScanner(int32 Level = 1);
};
