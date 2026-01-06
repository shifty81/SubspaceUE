// Copyright Epic Games, Inc. All Rights Reserved.

#include "VoxelBlock.h"

// Static material definitions
FMaterialProperties FMaterialProperties::GetMaterial(const FString& MaterialName)
{
	static TMap<FString, FMaterialProperties> Materials;
	
	// Initialize materials map if empty
	if (Materials.Num() == 0)
	{
		// Iron
		FMaterialProperties Iron;
		Iron.Name = TEXT("Iron");
		Iron.DurabilityMultiplier = 1.0f;
		Iron.MassMultiplier = 1.0f;
		Iron.EnergyEfficiency = 0.8f;
		Iron.ShieldMultiplier = 0.5f;
		Iron.TechLevel = 1;
		Iron.Color = FColor(184, 184, 192);
		Materials.Add(TEXT("Iron"), Iron);

		// Titanium
		FMaterialProperties Titanium;
		Titanium.Name = TEXT("Titanium");
		Titanium.DurabilityMultiplier = 1.5f;
		Titanium.MassMultiplier = 0.9f;
		Titanium.EnergyEfficiency = 1.0f;
		Titanium.ShieldMultiplier = 0.8f;
		Titanium.TechLevel = 2;
		Titanium.Color = FColor(208, 222, 242);
		Materials.Add(TEXT("Titanium"), Titanium);

		// Naonite
		FMaterialProperties Naonite;
		Naonite.Name = TEXT("Naonite");
		Naonite.DurabilityMultiplier = 2.0f;
		Naonite.MassMultiplier = 0.8f;
		Naonite.EnergyEfficiency = 1.2f;
		Naonite.ShieldMultiplier = 1.2f;
		Naonite.TechLevel = 3;
		Naonite.Color = FColor(38, 235, 89);
		Materials.Add(TEXT("Naonite"), Naonite);

		// Trinium
		FMaterialProperties Trinium;
		Trinium.Name = TEXT("Trinium");
		Trinium.DurabilityMultiplier = 2.5f;
		Trinium.MassMultiplier = 0.6f;
		Trinium.EnergyEfficiency = 1.5f;
		Trinium.ShieldMultiplier = 1.5f;
		Trinium.TechLevel = 4;
		Trinium.Color = FColor(64, 166, 255);
		Materials.Add(TEXT("Trinium"), Trinium);

		// Xanion
		FMaterialProperties Xanion;
		Xanion.Name = TEXT("Xanion");
		Xanion.DurabilityMultiplier = 3.0f;
		Xanion.MassMultiplier = 0.5f;
		Xanion.EnergyEfficiency = 1.8f;
		Xanion.ShieldMultiplier = 2.0f;
		Xanion.TechLevel = 5;
		Xanion.Color = FColor(255, 209, 38);
		Materials.Add(TEXT("Xanion"), Xanion);

		// Ogonite
		FMaterialProperties Ogonite;
		Ogonite.Name = TEXT("Ogonite");
		Ogonite.DurabilityMultiplier = 4.0f;
		Ogonite.MassMultiplier = 0.4f;
		Ogonite.EnergyEfficiency = 2.2f;
		Ogonite.ShieldMultiplier = 2.5f;
		Ogonite.TechLevel = 6;
		Ogonite.Color = FColor(255, 102, 38);
		Materials.Add(TEXT("Ogonite"), Ogonite);

		// Avorion
		FMaterialProperties Avorion;
		Avorion.Name = TEXT("Avorion");
		Avorion.DurabilityMultiplier = 5.0f;
		Avorion.MassMultiplier = 0.3f;
		Avorion.EnergyEfficiency = 3.0f;
		Avorion.ShieldMultiplier = 3.5f;
		Avorion.TechLevel = 7;
		Avorion.Color = FColor(217, 51, 255);
		Materials.Add(TEXT("Avorion"), Avorion);
	}

	// Return material or default to Iron
	if (Materials.Contains(MaterialName))
	{
		return Materials[MaterialName];
	}
	return Materials[TEXT("Iron")];
}

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
	FMaterialProperties Material = FMaterialProperties::GetMaterial(MaterialType);
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

	// Calculate basic properties
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
