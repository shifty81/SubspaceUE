// Copyright Epic Games, Inc. All Rights Reserved.

#include "SubspaceCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SubspacePlayerPawn.h"
#include "SubspacePlayerController.h"
#include "Kismet/GameplayStatics.h"

ASubspaceCharacter::ASubspaceCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create first-person camera
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(GetMesh(), FName("head")); // Attach to head bone if using skeletal mesh
	FirstPersonCamera->SetRelativeLocation(FVector(0.0f, 0.0f, 64.0f)); // Position above capsule
	FirstPersonCamera->bUsePawnControlRotation = true;

	// Configure character movement
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;
	GetCharacterMovement()->AirControl = 0.2f;
	
	// Use controller rotation for character
	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
}

void ASubspaceCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// Set initial movement speed
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	
	UE_LOG(LogTemp, Log, TEXT("SubspaceCharacter: Character initialized"));
}

void ASubspaceCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Check for nearby ships
	CheckForNearbyShip();
}

void ASubspaceCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind movement inputs
	PlayerInputComponent->BindAxis("MoveForward", this, &ASubspaceCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASubspaceCharacter::MoveRight);
	
	// Bind mouse look inputs
	PlayerInputComponent->BindAxis("LookUp", this, &ASubspaceCharacter::LookUp);
	PlayerInputComponent->BindAxis("LookRight", this, &ASubspaceCharacter::LookRight);
	
	// Bind action inputs
	PlayerInputComponent->BindAction("Boost", IE_Pressed, this, &ASubspaceCharacter::SprintPressed);
	PlayerInputComponent->BindAction("Boost", IE_Released, this, &ASubspaceCharacter::SprintReleased);
	PlayerInputComponent->BindAction("EnterExitShip", IE_Pressed, this, &ASubspaceCharacter::EnterExitShip);
}

void ASubspaceCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// Get forward direction based on camera
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ASubspaceCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// Get right direction based on camera
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void ASubspaceCharacter::LookUp(float Value)
{
	if (Value != 0.0f)
	{
		float PitchValue = Value * MousePitchSensitivity;
		if (bInvertMousePitch)
		{
			PitchValue = -PitchValue;
		}
		AddControllerPitchInput(PitchValue);
	}
}

void ASubspaceCharacter::LookRight(float Value)
{
	if (Value != 0.0f)
	{
		// Apply mouse yaw (inverted to fix left/right)
		float YawValue = -Value * MouseYawSensitivity;
		AddControllerYawInput(YawValue);
	}
}

void ASubspaceCharacter::SprintPressed()
{
	bIsSprinting = true;
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	UE_LOG(LogTemp, Log, TEXT("SubspaceCharacter: Sprint activated"));
}

void ASubspaceCharacter::SprintReleased()
{
	bIsSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	UE_LOG(LogTemp, Log, TEXT("SubspaceCharacter: Sprint deactivated"));
}

void ASubspaceCharacter::EnterExitShip()
{
	if (NearbyShip)
	{
		// Get player controller
		ASubspacePlayerController* PC = Cast<ASubspacePlayerController>(GetController());
		if (PC)
		{
			// Possess the ship
			PC->Possess(NearbyShip);
			
			// Position character inside ship or hide it
			SetActorHiddenInGame(true);
			SetActorEnableCollision(false);
			SetActorLocation(NearbyShip->GetActorLocation());
			
			UE_LOG(LogTemp, Log, TEXT("SubspaceCharacter: Entered ship"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("SubspaceCharacter: No nearby ship to enter"));
	}
}

void ASubspaceCharacter::CheckForNearbyShip()
{
	// Find all ships in range
	TArray<AActor*> FoundShips;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASubspacePlayerPawn::StaticClass(), FoundShips);
	
	NearbyShip = nullptr;
	float ClosestDistance = ShipDetectionRange;
	
	for (AActor* Actor : FoundShips)
	{
		ASubspacePlayerPawn* Ship = Cast<ASubspacePlayerPawn>(Actor);
		if (Ship && Ship != this)
		{
			float Distance = FVector::Dist(GetActorLocation(), Ship->GetActorLocation());
			if (Distance < ClosestDistance)
			{
				ClosestDistance = Distance;
				NearbyShip = Ship;
			}
		}
	}
}
