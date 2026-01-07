// Copyright Epic Games, Inc. All Rights Reserved.

#include "VoxelBlock.h"
#include "VoxelMaterial.h"

FVoxelBlock::FVoxelBlock(FVector InPosition, FVector InSize, const FString& InMaterialType,
                         EBlockType InBlockType, EBlockShape InShape, EBlockOrientation InOrientation)
	: Id(FGuid::NewGuid())
	, Position(InPosition)
	, Size(InSize)
	, MaterialType(InMaterialType)
	, BlockType(InBlockType)
	, Shape(InShape)
	, Orientation(InOrientation)
	, bIsDestroyed(false)
	, ThrustPower(0.0f)
	, PowerGeneration(0.0f)
	, ShieldCapacity(0.0f)
{
	CalculateProperties();
}

void FVoxelBlock::TakeDamage(float Damage)
{
	Durability -= Damage;
	if (Durability <= 0)
	{
		Durability = 0;
		bIsDestroyed = true;
	}
}

bool FVoxelBlock::Intersects(const FVoxelBlock& Other) const
{
	return Position.X < Other.Position.X + Other.Size.X &&
	       Position.X + Size.X > Other.Position.X &&
	       Position.Y < Other.Position.Y + Other.Size.Y &&
	       Position.Y + Size.Y > Other.Position.Y &&
	       Position.Z < Other.Position.Z + Other.Size.Z &&
	       Position.Z + Size.Z > Other.Position.Z;
}

void FVoxelBlock::CalculateProperties()
{
	// Use the new material system
	FVoxelMaterialProperties Material = UVoxelMaterialLibrary::GetMaterialPropertiesByName(MaterialType);
	float Volume = Size.X * Size.Y * Size.Z;

	// Adjust volume based on shape
	switch (Shape)
	{
	case EBlockShape::Wedge:
	case EBlockShape::HalfBlock:
		Volume *= 0.5f;
		break;
	case EBlockShape::Corner:
	case EBlockShape::Tetrahedron:
		Volume *= 0.25f;
		break;
	case EBlockShape::InnerCorner:
		Volume *= 0.75f;
		break;
	default:
		break;
	}

	// Calculate basic properties using new material system
	Mass = Volume * Material.MassMultiplier;
	MaxDurability = 100.0f * Material.DurabilityMultiplier * Volume;
	Durability = MaxDurability;
	Color = Material.Color;

	// Apply block-specific modifiers
	switch (BlockType)
	{
	case EBlockType::Armor:
		// Armor is 5x more durable but 1.5x heavier than hull
		MaxDurability *= 5.0f;
		Durability = MaxDurability;
		Mass *= 1.5f;
		break;
		
	case EBlockType::Engine:
		ThrustPower = 50.0f * Volume * Material.EnergyEfficiency;
		break;
		
	case EBlockType::Thruster:
		ThrustPower = 30.0f * Volume * Material.EnergyEfficiency;
		break;
		
	case EBlockType::GyroArray:
		ThrustPower = 20.0f * Volume * Material.EnergyEfficiency; // Torque
		break;
		
	case EBlockType::Generator:
		PowerGeneration = 100.0f * Volume * Material.EnergyEfficiency;
		break;
		
	case EBlockType::ShieldGenerator:
		ShieldCapacity = 200.0f * Volume * Material.ShieldMultiplier;
		break;
		
	default:
		break;
	}
}
