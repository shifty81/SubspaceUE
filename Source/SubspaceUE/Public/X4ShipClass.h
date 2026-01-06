// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "X4ShipClass.generated.h"

/**
 * X4-inspired ship classes and their characteristics
 * Based on X4 Foundations ship classification system
 */
UENUM(BlueprintType)
enum class EX4ShipClass : uint8
{
	// Small (S) class - Fast, agile, low cargo
	Fighter_Light UMETA(DisplayName = "Fighter (Light)"),
	Fighter_Heavy UMETA(DisplayName = "Fighter (Heavy)"),
	Miner_Small UMETA(DisplayName = "Miner (Small)"),
	
	// Medium (M) class - Balanced versatility
	Corvette UMETA(DisplayName = "Corvette"),
	Frigate UMETA(DisplayName = "Frigate"),
	Gunboat UMETA(DisplayName = "Gunboat"),
	Miner_Medium UMETA(DisplayName = "Miner (Medium)"),
	Freighter_Medium UMETA(DisplayName = "Freighter (Medium)"),
	
	// Large (L) class - Heavy combat/cargo
	Destroyer UMETA(DisplayName = "Destroyer"),
	Freighter_Large UMETA(DisplayName = "Freighter (Large)"),
	Miner_Large UMETA(DisplayName = "Miner (Large)"),
	
	// Extra Large (XL) class - Capital ships
	Battleship UMETA(DisplayName = "Battleship"),
	Carrier UMETA(DisplayName = "Carrier"),
	Builder UMETA(DisplayName = "Builder")
};

/**
 * X4-inspired racial/faction design philosophies
 * Visual styles without using actual X4 race names
 */
UENUM(BlueprintType)
enum class EX4DesignStyle : uint8
{
	Balanced UMETA(DisplayName = "Balanced"),      // Angular, industrial
	Aggressive UMETA(DisplayName = "Aggressive"),  // Sharp, aggressive lines
	Durable UMETA(DisplayName = "Durable"),        // Bulky, reinforced
	Sleek UMETA(DisplayName = "Sleek"),            // Smooth curves
	Advanced UMETA(DisplayName = "Advanced"),      // High-tech, clean lines
	Alien UMETA(DisplayName = "Alien")             // Unconventional
};

/**
 * Ship variant types like X4's Sentinel/Vanguard system
 */
UENUM(BlueprintType)
enum class EX4ShipVariant : uint8
{
	Standard UMETA(DisplayName = "Standard"),   // Balanced variant
	Sentinel UMETA(DisplayName = "Sentinel"),   // More hull/cargo, slower
	Vanguard UMETA(DisplayName = "Vanguard"),   // Faster, lighter defense/cargo
	Military UMETA(DisplayName = "Military")    // Combat-oriented variant
};

/**
 * Ship statistics structure
 */
USTRUCT(BlueprintType)
struct FX4ShipStats
{
	GENERATED_BODY()

	// Core Stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship Stats")
	float Hull = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship Stats")
	float MaxHull = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship Stats")
	float Shield = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship Stats")
	float MaxShield = 500.0f;

	// Movement
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship Stats")
	float Mass = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship Stats")
	float MaxSpeed = 80.0f;  // m/s

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship Stats")
	float Thrust = 5000.0f;  // N

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship Stats")
	float TurnRate = 2.0f;  // rad/s

	// Cargo & Systems
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship Stats")
	int32 CargoCapacity = 50;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship Stats")
	float PowerGeneration = 500.0f;  // W

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship Stats")
	float PowerConsumption = 100.0f;  // W

	// Weapons
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship Stats")
	int32 PrimaryWeaponSlots = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship Stats")
	int32 TurretSlots = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship Stats")
	int32 UtilitySlots = 2;
};

/**
 * Configuration for generating X4-style ships
 */
USTRUCT(BlueprintType)
struct FX4ShipConfig
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship Config")
	EX4ShipClass ShipClass = EX4ShipClass::Corvette;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship Config")
	EX4DesignStyle DesignStyle = EX4DesignStyle::Balanced;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship Config")
	EX4ShipVariant Variant = EX4ShipVariant::Standard;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship Config")
	FString ShipName = TEXT("Unnamed Ship");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship Config")
	FString Material = TEXT("Iron");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship Config")
	int32 Seed = 0;

	// Color customization
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship Config|Colors")
	FLinearColor PrimaryColor = FLinearColor(0.5f, 0.5f, 0.5f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship Config|Colors")
	FLinearColor SecondaryColor = FLinearColor(0.25f, 0.25f, 0.25f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship Config|Colors")
	FLinearColor AccentColor = FLinearColor(1.0f, 0.5f, 0.0f, 1.0f);
};
