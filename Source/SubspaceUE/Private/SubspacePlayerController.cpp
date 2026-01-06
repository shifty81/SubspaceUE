// Copyright Epic Games, Inc. All Rights Reserved.

#include "SubspacePlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "SubspaceInputConfig.h"
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

	SetupEnhancedInput();
}

void ASubspacePlayerController::SetupEnhancedInput()
{
	if (!InputConfig)
	{
		UE_LOG(LogTemp, Warning, TEXT("SubspacePlayerController: InputConfig is not set!"));
		return;
	}

	// Get Enhanced Input subsystem
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// Add input mapping context
		if (InputConfig->DefaultInputMappingContext)
		{
			Subsystem->AddMappingContext(InputConfig->DefaultInputMappingContext, 0);
			UE_LOG(LogTemp, Log, TEXT("SubspacePlayerController: Added default input mapping context"));
		}
	}

	// Bind actions
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Movement
		if (InputConfig->MoveForwardAction)
			EnhancedInputComponent->BindAction(InputConfig->MoveForwardAction, ETriggerEvent::Triggered, this, &ASubspacePlayerController::OnMoveForward);
		if (InputConfig->MoveRightAction)
			EnhancedInputComponent->BindAction(InputConfig->MoveRightAction, ETriggerEvent::Triggered, this, &ASubspacePlayerController::OnMoveRight);
		if (InputConfig->MoveUpAction)
			EnhancedInputComponent->BindAction(InputConfig->MoveUpAction, ETriggerEvent::Triggered, this, &ASubspacePlayerController::OnMoveUp);

		// Rotation (keyboard)
		if (InputConfig->PitchAction)
			EnhancedInputComponent->BindAction(InputConfig->PitchAction, ETriggerEvent::Triggered, this, &ASubspacePlayerController::OnPitch);
		if (InputConfig->YawAction)
			EnhancedInputComponent->BindAction(InputConfig->YawAction, ETriggerEvent::Triggered, this, &ASubspacePlayerController::OnYaw);
		if (InputConfig->RollAction)
			EnhancedInputComponent->BindAction(InputConfig->RollAction, ETriggerEvent::Triggered, this, &ASubspacePlayerController::OnRoll);

		// Look (mouse)
		if (InputConfig->LookAction)
			EnhancedInputComponent->BindAction(InputConfig->LookAction, ETriggerEvent::Triggered, this, &ASubspacePlayerController::OnLook);

		// Actions
		if (InputConfig->BrakeAction)
			EnhancedInputComponent->BindAction(InputConfig->BrakeAction, ETriggerEvent::Started, this, &ASubspacePlayerController::OnBrake);
		if (InputConfig->ToggleControlModeAction)
			EnhancedInputComponent->BindAction(InputConfig->ToggleControlModeAction, ETriggerEvent::Started, this, &ASubspacePlayerController::OnToggleControlMode);

		// UI
		if (InputConfig->OpenGalaxyMapAction)
			EnhancedInputComponent->BindAction(InputConfig->OpenGalaxyMapAction, ETriggerEvent::Started, this, &ASubspacePlayerController::OnOpenGalaxyMap);
		if (InputConfig->ToggleInventoryAction)
			EnhancedInputComponent->BindAction(InputConfig->ToggleInventoryAction, ETriggerEvent::Started, this, &ASubspacePlayerController::OnToggleInventory);
		if (InputConfig->ToggleShipBuilderAction)
			EnhancedInputComponent->BindAction(InputConfig->ToggleShipBuilderAction, ETriggerEvent::Started, this, &ASubspacePlayerController::OnToggleShipBuilder);
		if (InputConfig->PauseGameAction)
			EnhancedInputComponent->BindAction(InputConfig->PauseGameAction, ETriggerEvent::Started, this, &ASubspacePlayerController::OnPauseGame);

		UE_LOG(LogTemp, Log, TEXT("SubspacePlayerController: Enhanced Input actions bound"));
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

// Enhanced Input action handlers
void ASubspacePlayerController::OnMoveForward(const FInputActionValue& Value)
{
	if (ASubspacePlayerPawn* PlayerPawn = Cast<ASubspacePlayerPawn>(GetPawn()))
	{
		PlayerPawn->MoveForward(Value.Get<float>());
	}
}

void ASubspacePlayerController::OnMoveRight(const FInputActionValue& Value)
{
	if (ASubspacePlayerPawn* PlayerPawn = Cast<ASubspacePlayerPawn>(GetPawn()))
	{
		PlayerPawn->MoveRight(Value.Get<float>());
	}
}

void ASubspacePlayerController::OnMoveUp(const FInputActionValue& Value)
{
	if (ASubspacePlayerPawn* PlayerPawn = Cast<ASubspacePlayerPawn>(GetPawn()))
	{
		PlayerPawn->MoveUp(Value.Get<float>());
	}
}

void ASubspacePlayerController::OnPitch(const FInputActionValue& Value)
{
	if (ASubspacePlayerPawn* PlayerPawn = Cast<ASubspacePlayerPawn>(GetPawn()))
	{
		PlayerPawn->PitchInput(Value.Get<float>());
	}
}

void ASubspacePlayerController::OnYaw(const FInputActionValue& Value)
{
	if (ASubspacePlayerPawn* PlayerPawn = Cast<ASubspacePlayerPawn>(GetPawn()))
	{
		PlayerPawn->YawInput(Value.Get<float>());
	}
}

void ASubspacePlayerController::OnRoll(const FInputActionValue& Value)
{
	if (ASubspacePlayerPawn* PlayerPawn = Cast<ASubspacePlayerPawn>(GetPawn()))
	{
		PlayerPawn->RollInput(Value.Get<float>());
	}
}

void ASubspacePlayerController::OnLook(const FInputActionValue& Value)
{
	if (ASubspacePlayerPawn* PlayerPawn = Cast<ASubspacePlayerPawn>(GetPawn()))
	{
		const FVector2D LookAxisVector = Value.Get<FVector2D>();
		PlayerPawn->LookUp(LookAxisVector.Y);
		PlayerPawn->LookRight(LookAxisVector.X);
	}
}

void ASubspacePlayerController::OnBrake(const FInputActionValue& Value)
{
	if (ASubspacePlayerPawn* PlayerPawn = Cast<ASubspacePlayerPawn>(GetPawn()))
	{
		PlayerPawn->EmergencyBrake();
	}
}

void ASubspacePlayerController::OnToggleControlMode(const FInputActionValue& Value)
{
	ToggleControlMode();
}

void ASubspacePlayerController::OnOpenGalaxyMap(const FInputActionValue& Value)
{
	OpenGalaxyMap();
}

void ASubspacePlayerController::OnToggleInventory(const FInputActionValue& Value)
{
	ToggleInventory();
}

void ASubspacePlayerController::OnToggleShipBuilder(const FInputActionValue& Value)
{
	ToggleShipBuilder();
}

void ASubspacePlayerController::OnPauseGame(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Log, TEXT("SubspacePlayerController: Pause game requested"));
	// TODO: Implement pause menu
}
