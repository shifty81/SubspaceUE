// Copyright Epic Games, Inc. All Rights Reserved.

#include "AutoInitGameActor.h"
#include "Engine/World.h"
#include "GameFramework/WorldSettings.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"

AAutoInitGameActor::AAutoInitGameActor()
{
	PrimaryActorTick.bCanEverTick = false;
	
	// Make this actor persist across levels
	bNetLoadOnClient = true;
}

void AAutoInitGameActor::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Warning, TEXT("AutoInitGameActor: Initializing game world..."));
	
	SetupWorldSettings();
	EnsureGameMode();
	
	UE_LOG(LogTemp, Warning, TEXT("AutoInitGameActor: Initialization complete!"));
}

void AAutoInitGameActor::SetupWorldSettings()
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}
	
	AWorldSettings* WorldSettings = World->GetWorldSettings();
	if (WorldSettings)
	{
		// Disable gravity (we're in space!)
		WorldSettings->bWorldGravitySet = true;
		WorldSettings->GlobalGravityZ = 0.0f;
		
		// Set a black background color for space
		WorldSettings->bOverrideDefaultBroadphaseSettings = true;
		
		UE_LOG(LogTemp, Log, TEXT("AutoInitGameActor: World settings configured for space"));
	}
}

void AAutoInitGameActor::EnsureGameMode()
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}
	
	AGameModeBase* GameMode = World->GetAuthGameMode();
	if (GameMode)
	{
		UE_LOG(LogTemp, Log, TEXT("AutoInitGameActor: Game mode is active: %s"), *GameMode->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AutoInitGameActor: No game mode found!"));
	}
}
