// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "VoxelBlock.generated.h"

/**
 * Geometric shape of a voxel block
 */
UENUM(BlueprintType)
enum class EBlockShape : uint8
{
	Cube UMETA(DisplayName = "Cube"),
	Wedge UMETA(DisplayName = "Wedge"),
	Corner UMETA(DisplayName = "Corner"),
	InnerCorner UMETA(DisplayName = "Inner Corner"),
	Tetrahedron UMETA(DisplayName = "Tetrahedron"),
	HalfBlock UMETA(DisplayName = "Half Block")
};

/**
 * Orientation of a shaped block (which direction it faces)
 */
UENUM(BlueprintType)
enum class EBlockOrientation : uint8
{
	PosX UMETA(DisplayName = "+X"),
	NegX UMETA(DisplayName = "-X"),
	PosY UMETA(DisplayName = "+Y"),
	NegY UMETA(DisplayName = "-Y"),
	PosZ UMETA(DisplayName = "+Z"),
	NegZ UMETA(DisplayName = "-Z")
};

/**
 * Types of voxel blocks following Avorion-style categories
 */
UENUM(BlueprintType)
enum class EBlockType : uint8
{
	// Structural
	Hull UMETA(DisplayName = "Hull"),
	Armor UMETA(DisplayName = "Armor"),
	
	// Functional
	Engine UMETA(DisplayName = "Engine"),
	Thruster UMETA(DisplayName = "Thruster"),
	GyroArray UMETA(DisplayName = "Gyro Array"),
	Generator UMETA(DisplayName = "Generator"),
	ShieldGenerator UMETA(DisplayName = "Shield Generator"),
	
	// Weapons
	TurretMount UMETA(DisplayName = "Turret Mount"),
	
	// Systems
	HyperdriveCore UMETA(DisplayName = "Hyperdrive Core"),
	Cargo UMETA(DisplayName = "Cargo"),
	CrewQuarters UMETA(DisplayName = "Crew Quarters"),
	PodDocking UMETA(DisplayName = "Pod Docking"),
	Computer UMETA(DisplayName = "Computer"),
	Battery UMETA(DisplayName = "Battery"),
	IntegrityField UMETA(DisplayName = "Integrity Field")
};

/**
 * Material properties for different tiers
 */
USTRUCT(BlueprintType)
struct FMaterialProperties
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	float DurabilityMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	float MassMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	float EnergyEfficiency;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	float ShieldMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	int32 TechLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	FColor Color;

	FMaterialProperties()
		: Name("Iron")
		, DurabilityMultiplier(1.0f)
		, MassMultiplier(1.0f)
		, EnergyEfficiency(0.8f)
		, ShieldMultiplier(0.5f)
		, TechLevel(1)
		, Color(184, 184, 192) // Iron grey
	{
	}

	// Static material definitions
	static FMaterialProperties GetMaterial(const FString& MaterialName);
};

/**
 * Represents a single voxel block with position, size, and material properties
 */
USTRUCT(BlueprintType)
struct SUBSPACEUE_API FVoxelBlock
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voxel")
	FGuid Id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voxel")
	FVector Position;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voxel")
	FVector Size;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voxel")
	FString MaterialType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voxel")
	EBlockType BlockType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voxel")
	EBlockShape Shape;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voxel")
	EBlockOrientation Orientation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voxel")
	float Durability;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voxel")
	float MaxDurability;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voxel")
	float Mass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voxel")
	FColor Color;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voxel")
	bool bIsDestroyed;

	// Functional properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voxel|Functional")
	float ThrustPower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voxel|Functional")
	float PowerGeneration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voxel|Functional")
	float ShieldCapacity;

	FVoxelBlock()
		: Id(FGuid::NewGuid())
		, Position(FVector::ZeroVector)
		, Size(FVector::OneVector)
		, MaterialType(TEXT("Iron"))
		, BlockType(EBlockType::Hull)
		, Shape(EBlockShape::Cube)
		, Orientation(EBlockOrientation::PosY)
		, Durability(100.0f)
		, MaxDurability(100.0f)
		, Mass(1.0f)
		, Color(FColor::White)
		, bIsDestroyed(false)
		, ThrustPower(0.0f)
		, PowerGeneration(0.0f)
		, ShieldCapacity(0.0f)
	{
	}

	FVoxelBlock(FVector InPosition, FVector InSize, const FString& InMaterialType = TEXT("Iron"),
	            EBlockType InBlockType = EBlockType::Hull, EBlockShape InShape = EBlockShape::Cube,
	            EBlockOrientation InOrientation = EBlockOrientation::PosY);

	/** Take damage to this block */
	void TakeDamage(float Damage);

	/** Check if this voxel intersects with another */
	bool Intersects(const FVoxelBlock& Other) const;

	/** Calculate properties based on material and block type */
	void CalculateProperties();
};
