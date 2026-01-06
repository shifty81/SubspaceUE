// Copyright Epic Games, Inc. All Rights Reserved.

#include "SubspacePlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

ASubspacePlayerController::ASubspacePlayerController()
{
	bShowMouseCursor = false;
	bEnableClickEvents = false;
	bEnableTouchEvents = false;
}

void ASubspacePlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Set input mode for gameplay
	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
	
	UE_LOG(LogTemp, Log, TEXT("SubspacePlayerController: Initialized"));
}

void ASubspacePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// TODO: Bind enhanced input actions
		// These will be set up through the input mapping context
		UE_LOG(LogTemp, Log, TEXT("SubspacePlayerController: Enhanced Input Component ready"));
	}
}

void ASubspacePlayerController::ToggleControlMode()
{
	bIsShipControlMode = !bIsShipControlMode;
	
	if (bIsShipControlMode)
	{
		UE_LOG(LogTemp, Log, TEXT("SubspacePlayerController: Switched to Ship Control Mode"));
		bShowMouseCursor = false;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("SubspacePlayerController: Switched to Camera Mode"));
		bShowMouseCursor = false;
	}
}

void ASubspacePlayerController::OpenGalaxyMap()
{
	UE_LOG(LogTemp, Log, TEXT("SubspacePlayerController: Opening Galaxy Map..."));
	// TODO: Create and display galaxy map widget
	bShowMouseCursor = true;
}

void ASubspacePlayerController::ToggleInventory()
{
	UE_LOG(LogTemp, Log, TEXT("SubspacePlayerController: Toggling Inventory..."));
	// TODO: Toggle inventory widget
	bShowMouseCursor = !bShowMouseCursor;
}

void ASubspacePlayerController::ToggleShipBuilder()
{
	UE_LOG(LogTemp, Log, TEXT("SubspacePlayerController: Toggling Ship Builder..."));
	// TODO: Toggle ship builder widget
	bShowMouseCursor = !bShowMouseCursor;
}
