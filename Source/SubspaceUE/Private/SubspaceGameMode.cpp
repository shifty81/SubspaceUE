// Copyright Epic Games, Inc. All Rights Reserved.

#include "SubspaceGameMode.h"
#include "SubspacePlayerController.h"
#include "SubspacePlayerPawn.h"
#include "SubspaceHUD.h"
#include "SpaceActor.h"
#include "SpaceLightingActor.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

ASubspaceGameMode::ASubspaceGameMode()
{
	// Set default pawn and controller classes
	DefaultPawnClass = ASubspacePlayerPawn::StaticClass();
	PlayerControllerClass = ASubspacePlayerController::StaticClass();
	HUDClass = ASubspaceHUD::StaticClass();

	// Enable tick
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	// Initialize at galactic rim (starting zone)
	CurrentSectorCoordinates = FIntVector(100, 0, 0);
}

void ASubspaceGameMode::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Log, TEXT("SubspaceGameMode: Initializing game systems..."));
	
	// Spawn lighting
	if (GetWorld())
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		GetWorld()->SpawnActor<ASpaceLightingActor>(ASpaceLightingActor::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
		UE_LOG(LogTemp, Log, TEXT("SubspaceGameMode: Lighting spawned"));
	}
	
	// Initialize core game systems
	InitializeGalaxySystem();
	
	// Generate initial sector content
	GenerateAsteroids(50);
	SpawnAIShips(5);

	UE_LOG(LogTemp, Log, TEXT("SubspaceGameMode: Game systems initialized at sector (%d, %d, %d)"), 
		CurrentSectorCoordinates.X, CurrentSectorCoordinates.Y, CurrentSectorCoordinates.Z);
}

void ASubspaceGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Update game systems here
	// TODO: Update AI ships
	// TODO: Update faction relationships
	// TODO: Handle sector transitions
}

void ASubspaceGameMode::InitializeGalaxySystem()
{
	UE_LOG(LogTemp, Log, TEXT("SubspaceGameMode: Initializing galaxy system..."));
	
	// TODO: Initialize procedural galaxy generation
	// TODO: Load or generate faction data
	// TODO: Set up tech zones based on distance from center
	
	UE_LOG(LogTemp, Log, TEXT("SubspaceGameMode: Galaxy system initialized"));
}

void ASubspaceGameMode::SpawnAIShips(int32 NumShips)
{
	UE_LOG(LogTemp, Log, TEXT("SubspaceGameMode: Spawning %d AI ships..."), NumShips);
	
	if (GetWorld())
	{
		for (int32 i = 0; i < NumShips; i++)
		{
			// Random position around the player
			FVector SpawnLocation = FVector(
				FMath::RandRange(-5000.0f, 5000.0f),
				FMath::RandRange(-5000.0f, 5000.0f),
				FMath::RandRange(-2000.0f, 2000.0f)
			);
			
			FRotator SpawnRotation = FRotator(
				FMath::RandRange(-180.0f, 180.0f),
				FMath::RandRange(-180.0f, 180.0f),
				FMath::RandRange(-180.0f, 180.0f)
			);
			
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			
			ASpaceActor* Ship = GetWorld()->SpawnActor<ASpaceActor>(ASpaceActor::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
			if (Ship)
			{
				Ship->RotationSpeed = FVector(
					FMath::RandRange(-20.0f, 20.0f),
					FMath::RandRange(-20.0f, 20.0f),
					FMath::RandRange(-20.0f, 20.0f)
				);
				UE_LOG(LogTemp, Log, TEXT("Spawned AI ship at %s"), *SpawnLocation.ToString());
			}
		}
	}
}

void ASubspaceGameMode::GenerateAsteroids(int32 NumAsteroids)
{
	UE_LOG(LogTemp, Log, TEXT("SubspaceGameMode: Generating %d asteroids..."), NumAsteroids);
	
	if (GetWorld())
	{
		for (int32 i = 0; i < NumAsteroids; i++)
		{
			// Random position in a larger area around origin
			FVector SpawnLocation = FVector(
				FMath::RandRange(-10000.0f, 10000.0f),
				FMath::RandRange(-10000.0f, 10000.0f),
				FMath::RandRange(-5000.0f, 5000.0f)
			);
			
			FRotator SpawnRotation = FRotator(
				FMath::RandRange(-180.0f, 180.0f),
				FMath::RandRange(-180.0f, 180.0f),
				FMath::RandRange(-180.0f, 180.0f)
			);
			
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			
			ASpaceActor* Asteroid = GetWorld()->SpawnActor<ASpaceActor>(ASpaceActor::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
			if (Asteroid)
			{
				// Set random scale for variety
				float Scale = FMath::RandRange(1.0f, 3.0f);
				Asteroid->SetActorScale3D(FVector(Scale));
				
				// Random slow rotation
				Asteroid->RotationSpeed = FVector(
					FMath::RandRange(-5.0f, 5.0f),
					FMath::RandRange(-5.0f, 5.0f),
					FMath::RandRange(-5.0f, 5.0f)
				);
				
				UE_LOG(LogTemp, Log, TEXT("Spawned asteroid at %s"), *SpawnLocation.ToString());
			}
		}
	}
}
