// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "VoxelMaterial.generated.h"

/**
 * Material tier system representing progression from galaxy rim to center
 * Each tier unlocks better stats and new capabilities
 */
UENUM(BlueprintType)
enum class EMaterialTier : uint8
{
	Iron = 0			UMETA(DisplayName = "Iron"),
	Titanium = 1		UMETA(DisplayName = "Titanium"),
	Naonite = 2			UMETA(DisplayName = "Naonite"),
	Trinium = 3			UMETA(DisplayName = "Trinium"),
	Xanion = 4			UMETA(DisplayName = "Xanion"),
	Ogonite = 5			UMETA(DisplayName = "Ogonite"),
	Avorion = 6			UMETA(DisplayName = "Avorion")
};

/**
 * Material properties for voxel blocks
 * Defines durability, mass, energy efficiency, and other stats
 */
USTRUCT(BlueprintType)
struct SUBSPACEUE_API FVoxelMaterialProperties
{
	GENERATED_BODY()

	/** Display name of the material */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	FString Name;

	/** Material tier for progression system */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	EMaterialTier Tier;

	/** Durability multiplier compared to base (1.0 = Iron baseline) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material|Stats")
	float DurabilityMultiplier;

	/** Mass multiplier compared to base (1.0 = Iron baseline) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material|Stats")
	float MassMultiplier;

	/** Energy efficiency for power systems (1.0 = Iron baseline) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material|Stats")
	float EnergyEfficiency;

	/** Shield capacity multiplier (1.0 = Iron baseline) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material|Stats")
	float ShieldMultiplier;

	/** Tech level required to use this material */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	int32 TechLevel;

	/** Material color for rendering (RGB) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material|Visuals")
	FColor Color;

	/** Distance from galactic center where this material becomes available */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material|Progression")
	int32 UnlockDistance;

	/** Stat multiplier compared to Iron (1.0 = Iron baseline) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material|Progression")
	float StatMultiplier;

	/** Tech points multiplier for research/upgrades */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material|Progression")
	float TechPointsMultiplier;

	// Constructor with defaults
	FVoxelMaterialProperties()
		: Name(TEXT("Iron"))
		, Tier(EMaterialTier::Iron)
		, DurabilityMultiplier(1.0f)
		, MassMultiplier(1.0f)
		, EnergyEfficiency(1.0f)
		, ShieldMultiplier(1.0f)
		, TechLevel(0)
		, Color(FColor(127, 127, 127)) // Gray
		, UnlockDistance(MAX_int32)
		, StatMultiplier(1.0f)
		, TechPointsMultiplier(1.0f)
	{
	}
};

/**
 * Static helper class for material properties
 * Provides access to material data and utility functions
 */
UCLASS()
class SUBSPACEUE_API UVoxelMaterialLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/** Get material properties by tier */
	UFUNCTION(BlueprintCallable, Category = "Voxel|Materials")
	static FVoxelMaterialProperties GetMaterialProperties(EMaterialTier Tier);

	/** Get material properties by name */
	UFUNCTION(BlueprintCallable, Category = "Voxel|Materials")
	static FVoxelMaterialProperties GetMaterialPropertiesByName(const FString& MaterialName);

	/** Get the color for a material tier */
	UFUNCTION(BlueprintCallable, Category = "Voxel|Materials")
	static FColor GetMaterialColor(EMaterialTier Tier);

	/** Get the unlock distance for a material tier */
	UFUNCTION(BlueprintCallable, Category = "Voxel|Materials")
	static int32 GetUnlockDistance(EMaterialTier Tier);

	/** Get stat multiplier for a material tier */
	UFUNCTION(BlueprintCallable, Category = "Voxel|Materials")
	static float GetStatMultiplier(EMaterialTier Tier);

	/** Get tech points multiplier for a material tier */
	UFUNCTION(BlueprintCallable, Category = "Voxel|Materials")
	static float GetTechPointsMultiplier(EMaterialTier Tier);

	/** Get display name for a material tier */
	UFUNCTION(BlueprintCallable, Category = "Voxel|Materials")
	static FString GetMaterialDisplayName(EMaterialTier Tier);

	/** Get description of material tier benefits */
	UFUNCTION(BlueprintCallable, Category = "Voxel|Materials")
	static FString GetMaterialDescription(EMaterialTier Tier);

	/** Get all unlocked features at a material tier */
	UFUNCTION(BlueprintCallable, Category = "Voxel|Materials")
	static TArray<FString> GetUnlockedFeatures(EMaterialTier Tier);

	/** Convert material name to tier enum */
	UFUNCTION(BlueprintCallable, Category = "Voxel|Materials")
	static EMaterialTier MaterialNameToTier(const FString& MaterialName);

private:
	/** Initialize material properties table (called once) */
	static void InitializeMaterialTable();

	/** Material properties lookup table */
	static TMap<EMaterialTier, FVoxelMaterialProperties> MaterialTable;
	static bool bMaterialTableInitialized;
};
