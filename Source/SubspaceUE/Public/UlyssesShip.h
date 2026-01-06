// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "X4ShipClass.h"
#include "UlyssesShip.generated.h"

class UShipInteriorComponent;
class UShipEquipmentComponent;

/**
 * Ulysses - Default starter ship (Corvette-class)
 * Based on X4 Foundations ship design philosophy
 * Pre-built ship with modular equipment (NOT voxel-based)
 */
UCLASS()
class SUBSPACEUE_API AUlyssesShip : public APawn
{
	GENERATED_BODY()

public:
	AUlyssesShip();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Ship mesh component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ship")
	UStaticMeshComponent* ShipMesh;

	/** Ship interior component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ship")
	UShipInteriorComponent* Interior;

	/** Ship equipment component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ship")
	UShipEquipmentComponent* Equipment;

	/** Ship statistics */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship|Stats")
	FX4ShipStats Stats;

	/** Ship configuration */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship|Config")
	FX4ShipConfig Config;

	/** Current hull health */
	UPROPERTY(BlueprintReadOnly, Category = "Ship|Status")
	float CurrentHull;

	/** Current shield strength */
	UPROPERTY(BlueprintReadOnly, Category = "Ship|Status")
	float CurrentShield;

	/** Current energy */
	UPROPERTY(BlueprintReadOnly, Category = "Ship|Status")
	float CurrentEnergy;

	/** Current velocity */
	UPROPERTY(BlueprintReadOnly, Category = "Ship|Status")
	FVector Velocity;

	/** Get current speed (magnitude of velocity) */
	UFUNCTION(BlueprintCallable, Category = "Ship")
	float GetCurrentSpeed() const { return Velocity.Size(); }

	/** Get hull percentage (0-100) */
	UFUNCTION(BlueprintCallable, Category = "Ship")
	float GetHullPercentage() const;

	/** Get shield percentage (0-100) */
	UFUNCTION(BlueprintCallable, Category = "Ship")
	float GetShieldPercentage() const;

	/** Get energy percentage (0-100) */
	UFUNCTION(BlueprintCallable, Category = "Ship")
	float GetEnergyPercentage() const;

	/** Take damage to hull/shields */
	UFUNCTION(BlueprintCallable, Category = "Ship")
	void TakeDamage(float Amount);

	/** Regenerate shields */
	UFUNCTION(BlueprintCallable, Category = "Ship")
	void RegenerateShields(float DeltaTime);

	/** Initialize Ulysses with default configuration */
	UFUNCTION(BlueprintCallable, Category = "Ship")
	void InitializeUlysses();

protected:
	/** Setup default Ulysses stats */
	void SetupDefaultStats();

	/** Setup default Ulysses equipment */
	void SetupDefaultEquipment();

	/** Setup Ulysses interior */
	void SetupInterior();
};
