// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

/**
 * SubspaceUE Game Module
 * 
 * This is the main module for the Codename:Subspace game, converted from C# .NET to Unreal Engine 5.7.
 * 
 * Original Systems Ported:
 * - Entity-Component System (now using UE's Actor-Component system)
 * - Voxel-based ship construction
 * - Modular ship generation system
 * - Newtonian physics simulation (using Chaos physics)
 * - Procedural galaxy generation
 * - AI behavior system
 * - Multiplayer networking
 * - Resource and inventory management
 * - Faction and diplomacy system
 * - Quest system
 */
class FSubspaceUEModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
