// Copyright Epic Games, Inc. All Rights Reserved.

#include "SubspaceGameInstance.h"

USubspaceGameInstance::USubspaceGameInstance()
{
	// Initialize default values
}

void USubspaceGameInstance::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Log, TEXT("SubspaceGameInstance: Initializing game instance..."));

	// Initialize default inventory
	PlayerInventory.Add(FName("Iron"), 100);
	PlayerInventory.Add(FName("Titanium"), 50);
	
	// Initialize default faction reputation
	FactionReputation.Add(FName("Federation"), 0.0f);
	FactionReputation.Add(FName("Pirates"), -50.0f);
	FactionReputation.Add(FName("Traders"), 25.0f);

	UE_LOG(LogTemp, Log, TEXT("SubspaceGameInstance: Initialization complete"));
}

void USubspaceGameInstance::Shutdown()
{
	UE_LOG(LogTemp, Log, TEXT("SubspaceGameInstance: Shutting down..."));
	
	// Cleanup here
	
	Super::Shutdown();
}

void USubspaceGameInstance::SaveGame()
{
	UE_LOG(LogTemp, Log, TEXT("SubspaceGameInstance: Saving game..."));
	
	// TODO: Implement save system using UE's SaveGame class
	// TODO: Serialize player inventory, credits, faction rep
	// TODO: Save current sector location
	
	UE_LOG(LogTemp, Warning, TEXT("SubspaceGameInstance: Save system not yet implemented"));
}

void USubspaceGameInstance::LoadGame()
{
	UE_LOG(LogTemp, Log, TEXT("SubspaceGameInstance: Loading game..."));
	
	// TODO: Implement load system using UE's SaveGame class
	// TODO: Deserialize player data
	// TODO: Restore game state
	
	UE_LOG(LogTemp, Warning, TEXT("SubspaceGameInstance: Load system not yet implemented"));
}
