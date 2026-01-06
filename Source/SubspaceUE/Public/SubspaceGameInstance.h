// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SubspaceGameInstance.generated.h"

/**
 * Game Instance for Codename:Subspace
 * 
 * Persists data across level transitions and manages global systems
 */
UCLASS()
class SUBSPACEUE_API USubspaceGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	USubspaceGameInstance();

	virtual void Init() override;
	virtual void Shutdown() override;

	/** Player inventory data */
	UPROPERTY(BlueprintReadWrite, Category = "Subspace|Inventory")
	TMap<FName, int32> PlayerInventory;

	/** Player credits/currency */
	UPROPERTY(BlueprintReadWrite, Category = "Subspace|Economy")
	int32 PlayerCredits = 10000;

	/** Current galaxy seed for procedural generation */
	UPROPERTY(BlueprintReadWrite, Category = "Subspace|Galaxy")
	int32 GalaxySeed = 12345;

	/** Faction reputation values */
	UPROPERTY(BlueprintReadWrite, Category = "Subspace|Faction")
	TMap<FName, float> FactionReputation;

	/** Save game data */
	UFUNCTION(BlueprintCallable, Category = "Subspace|Save")
	void SaveGame();

	/** Load game data */
	UFUNCTION(BlueprintCallable, Category = "Subspace|Save")
	void LoadGame();
};
