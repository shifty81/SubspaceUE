// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SubspaceGameMode.generated.h"

/**
 * Main Game Mode for Codename:Subspace
 * 
 * This game mode manages the core gameplay loop including:
 * - Player spawn and respawn
 * - Galaxy sector management
 * - AI ship spawning
 * - Resource generation
 * - Faction interactions
 */
UCLASS()
class SUBSPACEUE_API ASubspaceGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ASubspaceGameMode();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/** Initialize galaxy sector system */
	UFUNCTION(BlueprintCallable, Category = "Subspace|Galaxy")
	void InitializeGalaxySystem();

	/** Spawn AI ships in current sector */
	UFUNCTION(BlueprintCallable, Category = "Subspace|AI")
	void SpawnAIShips(int32 NumShips);

	/** Generate asteroids for current sector */
	UFUNCTION(BlueprintCallable, Category = "Subspace|Procedural")
	void GenerateAsteroids(int32 NumAsteroids);

public:
	/** Current galaxy sector coordinates */
	UPROPERTY(BlueprintReadWrite, Category = "Subspace|Galaxy")
	FIntVector CurrentSectorCoordinates;

	/** Maximum distance from galactic center */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subspace|Galaxy")
	float GalacticRadius = 100000.0f;
};
