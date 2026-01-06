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
 * Equipment types
 */
UENUM(BlueprintType)
enum class EEquipmentType : uint8
{
	PulseLaser UMETA(DisplayName = "Pulse Laser"),
	BeamLaser UMETA(DisplayName = "Beam Laser"),
	PlasmaCannon UMETA(DisplayName = "Plasma Cannon"),
	Railgun UMETA(DisplayName = "Railgun"),
	MissileLauncher UMETA(DisplayName = "Missile Launcher"),
	MiningLaser UMETA(DisplayName = "Mining Laser"),
	SalvageBeam UMETA(DisplayName = "Salvage Beam"),
	TractorBeam UMETA(DisplayName = "Tractor Beam"),
	ShieldGenerator UMETA(DisplayName = "Shield Generator"),
	CombatEngine UMETA(DisplayName = "Combat Engine"),
	TravelEngine UMETA(DisplayName = "Travel Engine"),
	PowerReactor UMETA(DisplayName = "Power Reactor")
};

/**
 * Equipment item data
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	float Damage = 100.0f;  // For weapons

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	float Range = 1000.0f;  // For weapons/tools

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	float PowerConsumption = 50.0f;  // W

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	float FireRate = 1.0f;  // Shots per second

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
	/** Create pulse laser equipment */
	FEquipmentItem CreatePulseLaser(int32 Level = 1);

	/** Create mining laser equipment */
	FEquipmentItem CreateMiningLaser(int32 Level = 1);

	/** Create shield generator equipment */
	FEquipmentItem CreateShieldGenerator(int32 Level = 1);
};
