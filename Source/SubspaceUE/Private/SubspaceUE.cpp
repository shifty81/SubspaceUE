// Copyright Epic Games, Inc. All Rights Reserved.

#include "SubspaceUE.h"
#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FSubspaceUEModule"

void FSubspaceUEModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	UE_LOG(LogTemp, Log, TEXT("SubspaceUE Module: Initializing Codename:Subspace systems..."));
	
	// Initialize core subsystems here
	// TODO: Initialize procedural generation system
	// TODO: Initialize faction system
	// TODO: Initialize resource management
	
	UE_LOG(LogTemp, Log, TEXT("SubspaceUE Module: Initialization complete"));
}

void FSubspaceUEModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module. For modules that support dynamic reloading,
	// we call this function before unloading the module.
	UE_LOG(LogTemp, Log, TEXT("SubspaceUE Module: Shutting down..."));
	
	// Cleanup subsystems here
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_PRIMARY_GAME_MODULE( FSubspaceUEModule, SubspaceUE, "SubspaceUE" );
