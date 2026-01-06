// Copyright Epic Games, Inc. All Rights Reserved.

#include "SubspacePlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MainHUDWidget.h"
#include "Blueprint/UserWidget.h"
#include "SubspacePlayerPawn.h"

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
	
	// Create main HUD
	CreateMainHUD();
	
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

void ASubspacePlayerController::CreateMainHUD()
{
	if (!MainHUDClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("SubspacePlayerController: MainHUDClass is not set!"));
		return;
	}

	// Create HUD widget
	MainHUDWidget = CreateWidget<UMainHUDWidget>(this, MainHUDClass);
	if (MainHUDWidget)
	{
		MainHUDWidget->AddToViewport();
		UE_LOG(LogTemp, Log, TEXT("SubspacePlayerController: Main HUD created"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("SubspacePlayerController: Failed to create Main HUD widget"));
	}
}

void ASubspacePlayerController::UpdateHUD()
{
	if (!MainHUDWidget)
	{
		return;
	}

	// Get player pawn
	ASubspacePlayerPawn* PlayerPawn = Cast<ASubspacePlayerPawn>(GetPawn());
	if (!PlayerPawn)
	{
		return;
	}

	// Update HUD with ship stats
	// For now, use placeholder values - these will be replaced with actual ship stats later
	MainHUDWidget->UpdateHealth(100.0f, 100.0f);
	MainHUDWidget->UpdateShield(100.0f, 100.0f);
	MainHUDWidget->UpdateEnergy(100.0f, 100.0f);
	
	// Update velocity and position
	MainHUDWidget->UpdateVelocity(PlayerPawn->Velocity);
	MainHUDWidget->UpdatePosition(PlayerPawn->GetActorLocation());
	
	// Update speed
	float CurrentSpeed = PlayerPawn->Velocity.Size();
	MainHUDWidget->UpdateSpeed(CurrentSpeed, 1000.0f); // 1000 is placeholder max speed
}
