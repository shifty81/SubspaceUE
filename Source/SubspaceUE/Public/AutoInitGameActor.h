// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/WorldSettings.h"
#include "AutoInitGameActor.generated.h"

/**
 * Actor that automatically initializes the game world
 * This ensures the game is playable even without a proper level setup
 */
UCLASS()
class SUBSPACEUE_API AAutoInitGameActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AAutoInitGameActor();

protected:
	virtual void BeginPlay() override;

	/** Setup world settings for space environment */
	void SetupWorldSettings();

	/** Ensure game mode is correct */
	void EnsureGameMode();
};
