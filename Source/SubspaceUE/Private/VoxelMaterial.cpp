// Copyright Epic Games, Inc. All Rights Reserved.

#include "VoxelMaterial.h"

// Static member initialization
TMap<EMaterialTier, FVoxelMaterialProperties> UVoxelMaterialLibrary::MaterialTable;
bool UVoxelMaterialLibrary::bMaterialTableInitialized = false;

void UVoxelMaterialLibrary::InitializeMaterialTable()
{
	if (bMaterialTableInitialized)
		return;

	// Iron - Starting material
	FVoxelMaterialProperties Iron;
	Iron.Name = TEXT("Iron");
	Iron.Tier = EMaterialTier::Iron;
	Iron.DurabilityMultiplier = 1.0f;
	Iron.MassMultiplier = 1.0f;
	Iron.EnergyEfficiency = 1.0f;
	Iron.ShieldMultiplier = 0.0f; // No shields at Iron tier
	Iron.TechLevel = 0;
	Iron.Color = FColor(127, 127, 127); // Gray
	Iron.UnlockDistance = MAX_int32;
	Iron.StatMultiplier = 1.0f;
	Iron.TechPointsMultiplier = 1.0f;
	MaterialTable.Add(EMaterialTier::Iron, Iron);

	// Titanium - Tier 1
	FVoxelMaterialProperties Titanium;
	Titanium.Name = TEXT("Titanium");
	Titanium.Tier = EMaterialTier::Titanium;
	Titanium.DurabilityMultiplier = 1.5f;
	Titanium.MassMultiplier = 0.9f;
	Titanium.EnergyEfficiency = 1.1f;
	Titanium.ShieldMultiplier = 0.5f;
	Titanium.TechLevel = 1;
	Titanium.Color = FColor(179, 204, 230); // Silver-blue
	Titanium.UnlockDistance = 350;
	Titanium.StatMultiplier = 1.3f;
	Titanium.TechPointsMultiplier = 1.5f;
	MaterialTable.Add(EMaterialTier::Titanium, Titanium);

	// Naonite - Tier 2
	FVoxelMaterialProperties Naonite;
	Naonite.Name = TEXT("Naonite");
	Naonite.Tier = EMaterialTier::Naonite;
	Naonite.DurabilityMultiplier = 2.0f;
	Naonite.MassMultiplier = 0.8f;
	Naonite.EnergyEfficiency = 1.3f;
	Naonite.ShieldMultiplier = 1.0f;
	Naonite.TechLevel = 2;
	Naonite.Color = FColor(51, 230, 77); // Bright green
	Naonite.UnlockDistance = 250;
	Naonite.StatMultiplier = 1.6f;
	Naonite.TechPointsMultiplier = 2.5f;
	MaterialTable.Add(EMaterialTier::Naonite, Naonite);

	// Trinium - Tier 3
	FVoxelMaterialProperties Trinium;
	Trinium.Name = TEXT("Trinium");
	Trinium.Tier = EMaterialTier::Trinium;
	Trinium.DurabilityMultiplier = 2.5f;
	Trinium.MassMultiplier = 0.6f;
	Trinium.EnergyEfficiency = 1.5f;
	Trinium.ShieldMultiplier = 1.5f;
	Trinium.TechLevel = 3;
	Trinium.Color = FColor(77, 153, 255); // Blue
	Trinium.UnlockDistance = 150;
	Trinium.StatMultiplier = 2.0f;
	Trinium.TechPointsMultiplier = 4.0f;
	MaterialTable.Add(EMaterialTier::Trinium, Trinium);

	// Xanion - Tier 4
	FVoxelMaterialProperties Xanion;
	Xanion.Name = TEXT("Xanion");
	Xanion.Tier = EMaterialTier::Xanion;
	Xanion.DurabilityMultiplier = 3.0f;
	Xanion.MassMultiplier = 0.5f;
	Xanion.EnergyEfficiency = 1.8f;
	Xanion.ShieldMultiplier = 2.0f;
	Xanion.TechLevel = 4;
	Xanion.Color = FColor(255, 230, 51); // Gold
	Xanion.UnlockDistance = 75;
	Xanion.StatMultiplier = 2.5f;
	Xanion.TechPointsMultiplier = 6.0f;
	MaterialTable.Add(EMaterialTier::Xanion, Xanion);

	// Ogonite - Tier 5
	FVoxelMaterialProperties Ogonite;
	Ogonite.Name = TEXT("Ogonite");
	Ogonite.Tier = EMaterialTier::Ogonite;
	Ogonite.DurabilityMultiplier = 4.0f;
	Ogonite.MassMultiplier = 0.4f;
	Ogonite.EnergyEfficiency = 2.2f;
	Ogonite.ShieldMultiplier = 2.5f;
	Ogonite.TechLevel = 5;
	Ogonite.Color = FColor(255, 102, 38); // Orange-red
	Ogonite.UnlockDistance = 50;
	Ogonite.StatMultiplier = 3.0f;
	Ogonite.TechPointsMultiplier = 9.0f;
	MaterialTable.Add(EMaterialTier::Ogonite, Ogonite);

	// Avorion - Tier 6 (Ultimate)
	FVoxelMaterialProperties Avorion;
	Avorion.Name = TEXT("Avorion");
	Avorion.Tier = EMaterialTier::Avorion;
	Avorion.DurabilityMultiplier = 5.0f;
	Avorion.MassMultiplier = 0.3f;
	Avorion.EnergyEfficiency = 3.0f;
	Avorion.ShieldMultiplier = 3.5f;
	Avorion.TechLevel = 6;
	Avorion.Color = FColor(217, 51, 255); // Purple
	Avorion.UnlockDistance = 25;
	Avorion.StatMultiplier = 4.0f;
	Avorion.TechPointsMultiplier = 15.0f;
	MaterialTable.Add(EMaterialTier::Avorion, Avorion);

	bMaterialTableInitialized = true;
}

FVoxelMaterialProperties UVoxelMaterialLibrary::GetMaterialProperties(EMaterialTier Tier)
{
	InitializeMaterialTable();
	
	if (MaterialTable.Contains(Tier))
	{
		return MaterialTable[Tier];
	}
	
	// Return Iron as default
	return MaterialTable[EMaterialTier::Iron];
}

FVoxelMaterialProperties UVoxelMaterialLibrary::GetMaterialPropertiesByName(const FString& MaterialName)
{
	InitializeMaterialTable();
	
	EMaterialTier Tier = MaterialNameToTier(MaterialName);
	return GetMaterialProperties(Tier);
}

FColor UVoxelMaterialLibrary::GetMaterialColor(EMaterialTier Tier)
{
	return GetMaterialProperties(Tier).Color;
}

int32 UVoxelMaterialLibrary::GetUnlockDistance(EMaterialTier Tier)
{
	return GetMaterialProperties(Tier).UnlockDistance;
}

float UVoxelMaterialLibrary::GetStatMultiplier(EMaterialTier Tier)
{
	return GetMaterialProperties(Tier).StatMultiplier;
}

float UVoxelMaterialLibrary::GetTechPointsMultiplier(EMaterialTier Tier)
{
	return GetMaterialProperties(Tier).TechPointsMultiplier;
}

FString UVoxelMaterialLibrary::GetMaterialDisplayName(EMaterialTier Tier)
{
	return GetMaterialProperties(Tier).Name;
}

FString UVoxelMaterialLibrary::GetMaterialDescription(EMaterialTier Tier)
{
	switch (Tier)
	{
	case EMaterialTier::Iron:
		return TEXT("Basic starting material. Available everywhere in the galaxy.");
	case EMaterialTier::Titanium:
		return TEXT("Stronger than iron. Provides improved hull strength and weapon damage.");
	case EMaterialTier::Naonite:
		return TEXT("Unlocks shields! Essential for survival in dangerous sectors.");
	case EMaterialTier::Trinium:
		return TEXT("Lightweight and energy-efficient. Great for thrusters and power systems.");
	case EMaterialTier::Xanion:
		return TEXT("Advanced material with excellent power generation capabilities.");
	case EMaterialTier::Ogonite:
		return TEXT("Heavy and durable. Perfect for large capital ships and defensive structures.");
	case EMaterialTier::Avorion:
		return TEXT("The ultimate material. Only found at the galactic core. Unlocks all capabilities.");
	default:
		return TEXT("Unknown material");
	}
}

TArray<FString> UVoxelMaterialLibrary::GetUnlockedFeatures(EMaterialTier Tier)
{
	TArray<FString> Features;

	// Base features (always available)
	Features.Add(TEXT("Basic Mining"));
	Features.Add(TEXT("Basic Hull"));
	Features.Add(TEXT("Basic Engines"));

	if (Tier >= EMaterialTier::Titanium)
	{
		Features.Add(TEXT("Improved Hull Strength"));
		Features.Add(TEXT("Better Weapons"));
	}

	if (Tier >= EMaterialTier::Naonite)
	{
		Features.Add(TEXT("Shield Generators"));
		Features.Add(TEXT("Advanced Weapons"));
		Features.Add(TEXT("Salvaging"));
	}

	if (Tier >= EMaterialTier::Trinium)
	{
		Features.Add(TEXT("Energy Management"));
		Features.Add(TEXT("Advanced Thrusters"));
		Features.Add(TEXT("Jump Drives"));
	}

	if (Tier >= EMaterialTier::Xanion)
	{
		Features.Add(TEXT("Improved Power Generation"));
		Features.Add(TEXT("Advanced Mining"));
		Features.Add(TEXT("Refining Stations"));
	}

	if (Tier >= EMaterialTier::Ogonite)
	{
		Features.Add(TEXT("Advanced Trading"));
		Features.Add(TEXT("Fleet Management"));
		Features.Add(TEXT("Captain Automation"));
	}

	if (Tier >= EMaterialTier::Avorion)
	{
		Features.Add(TEXT("Barrier Access"));
		Features.Add(TEXT("Boss Encounters"));
		Features.Add(TEXT("Endgame Content"));
		Features.Add(TEXT("Ultimate Upgrades"));
	}

	return Features;
}

EMaterialTier UVoxelMaterialLibrary::MaterialNameToTier(const FString& MaterialName)
{
	FString LowerName = MaterialName.ToLower();
	
	if (LowerName.Contains(TEXT("iron")))
		return EMaterialTier::Iron;
	if (LowerName.Contains(TEXT("titanium")))
		return EMaterialTier::Titanium;
	if (LowerName.Contains(TEXT("naonite")))
		return EMaterialTier::Naonite;
	if (LowerName.Contains(TEXT("trinium")))
		return EMaterialTier::Trinium;
	if (LowerName.Contains(TEXT("xanion")))
		return EMaterialTier::Xanion;
	if (LowerName.Contains(TEXT("ogonite")))
		return EMaterialTier::Ogonite;
	if (LowerName.Contains(TEXT("avorion")))
		return EMaterialTier::Avorion;
	
	// Default to Iron
	return EMaterialTier::Iron;
}
