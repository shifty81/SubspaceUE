// Copyright Epic Games, Inc. All Rights Reserved.

#include "SubspacePlayerPawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "SubspacePlayerController.h"

ASubspacePlayerPawn::ASubspacePlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create ship mesh
	ShipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	RootComponent = ShipMesh;
	ShipMesh->SetSimulatePhysics(false); // We'll handle physics manually
	ShipMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	
	// Load a default mesh if available (can be overridden in Blueprint)
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMeshAsset(TEXT("/Engine/BasicShapes/Cube"));
	if (ShipMeshAsset.Succeeded())
	{
		ShipMesh->SetStaticMesh(ShipMeshAsset.Object);
		ShipMesh->SetRelativeScale3D(FVector(4.0f, 8.0f, 2.0f)); // Make it ship-shaped (larger and more visible)
	}

	// Create spring arm for camera
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = CameraDistance;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = CameraLagSpeed;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->CameraRotationLagSpeed = 10.0f;
	SpringArm->SetRelativeRotation(FRotator(CameraPitchOffset, 0.0f, 0.0f));

	// Create camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	// Initialize physics properties
	Velocity = FVector::ZeroVector;
	AngularVelocity = FVector::ZeroVector;
}

void ASubspacePlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Log, TEXT("SubspacePlayerPawn: Ship initialized"));
}

void ASubspacePlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Update Newtonian physics
	UpdatePhysics(DeltaTime);
	
	// Update HUD if we have a player controller
	ASubspacePlayerController* PC = Cast<ASubspacePlayerController>(GetController());
	if (PC)
	{
		PC->UpdateHUD();
	}
}

void ASubspacePlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind movement inputs
	PlayerInputComponent->BindAxis("MoveForward", this, &ASubspacePlayerPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASubspacePlayerPawn::MoveRight);
	PlayerInputComponent->BindAxis("MoveUp", this, &ASubspacePlayerPawn::MoveUp);
	
	// Bind rotation inputs (keyboard - arrow keys)
	PlayerInputComponent->BindAxis("Pitch", this, &ASubspacePlayerPawn::PitchInput);
	PlayerInputComponent->BindAxis("Yaw", this, &ASubspacePlayerPawn::YawInput);
	PlayerInputComponent->BindAxis("Roll", this, &ASubspacePlayerPawn::RollInput);
	
	// Bind mouse look inputs (FPS-style)
	PlayerInputComponent->BindAxis("LookUp", this, &ASubspacePlayerPawn::LookUp);
	PlayerInputComponent->BindAxis("LookRight", this, &ASubspacePlayerPawn::LookRight);
	
	// Bind action inputs
	PlayerInputComponent->BindAction("Brake", IE_Pressed, this, &ASubspacePlayerPawn::EmergencyBrake);
	PlayerInputComponent->BindAction("ToggleCameraMode", IE_Pressed, this, &ASubspacePlayerPawn::ToggleCameraMode);
	
	// Bind camera controls
	PlayerInputComponent->BindAxis("MouseWheelAxis", this, &ASubspacePlayerPawn::ZoomCamera);
}

void ASubspacePlayerPawn::ApplyThrust(const FVector& Direction, float Magnitude)
{
	// Force = Mass * Acceleration
	// Acceleration = Force / Mass
	FVector Force = Direction * Magnitude * MaxThrust;
	// Convert to world space
	FVector WorldForce = GetActorRotation().RotateVector(Force);
	// Apply acceleration (F = ma, so a = F/m)
	FVector Acceleration = WorldForce / ShipMass;
	Velocity += Acceleration * GetWorld()->GetDeltaSeconds();
}

void ASubspacePlayerPawn::ApplyRotation(const FVector& RotationAxis, float Magnitude)
{
	FVector Torque = RotationAxis * Magnitude * MaxRotationForce;
	AngularVelocity += Torque * GetWorld()->GetDeltaSeconds();
}

void ASubspacePlayerPawn::UpdatePhysics(float DeltaTime)
{
	// Apply velocity to position (Unreal uses cm, so velocity is in cm/s)
	FVector NewLocation = GetActorLocation() + (Velocity * DeltaTime);
	SetActorLocation(NewLocation);

	// Apply quadratic drag: Drag = 0.5 * Cd * v^2
	// This creates more realistic speed limiting
	float Speed = Velocity.Size();
	if (Speed > 0.01f)
	{
		float SpeedSquared = Speed * Speed; // Cache for performance
		FVector DragForce = -Velocity.GetSafeNormal() * DragCoefficient * SpeedSquared;
		FVector DragAcceleration = DragForce / ShipMass;
		Velocity += DragAcceleration * DeltaTime;
	}

	// Apply angular velocity to rotation
	FRotator DeltaRotation = FRotator(
		AngularVelocity.Y * DeltaTime,
		AngularVelocity.Z * DeltaTime,
		AngularVelocity.X * DeltaTime
	);
	AddActorLocalRotation(DeltaRotation);

	// Apply angular drag
	AngularVelocity *= (1.0f - DragCoefficient * DeltaTime);
	
	// Update camera
	if (SpringArm)
	{
		SpringArm->TargetArmLength = CameraDistance;
	}
}

void ASubspacePlayerPawn::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		ApplyThrust(FVector(1, 0, 0), Value);
	}
}

void ASubspacePlayerPawn::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		ApplyThrust(FVector(0, 1, 0), Value);
	}
}

void ASubspacePlayerPawn::MoveUp(float Value)
{
	if (Value != 0.0f)
	{
		ApplyThrust(FVector(0, 0, 1), Value);
	}
}

void ASubspacePlayerPawn::PitchInput(float Value)
{
	if (Value != 0.0f)
	{
		ApplyRotation(FVector(0, 1, 0), Value);
	}
}

void ASubspacePlayerPawn::YawInput(float Value)
{
	if (Value != 0.0f)
	{
		ApplyRotation(FVector(0, 0, 1), Value);
	}
}

void ASubspacePlayerPawn::RollInput(float Value)
{
	if (Value != 0.0f)
	{
		ApplyRotation(FVector(1, 0, 0), Value);
	}
}

void ASubspacePlayerPawn::LookUp(float Value)
{
	if (Value != 0.0f)
	{
		// Apply mouse pitch with sensitivity and inversion
		float PitchValue = Value * MousePitchSensitivity;
		if (bInvertMousePitch)
		{
			PitchValue = -PitchValue;
		}
		
		// For FPS-style controls, rotate the camera/ship based on mouse movement
		// Use the responsiveness multiplier for more responsive mouse control
		ApplyRotation(FVector(0, 1, 0), PitchValue * MouseResponsivenessMultiplier);
	}
}

void ASubspacePlayerPawn::LookRight(float Value)
{
	if (Value != 0.0f)
	{
		// Apply mouse yaw with sensitivity and inversion
		float YawValue = Value * MouseYawSensitivity;
		if (bInvertMouseYaw)
		{
			YawValue = -YawValue;
		}
		
		// For FPS-style controls, rotate the camera/ship based on mouse movement
		// Use the responsiveness multiplier for more responsive mouse control
		ApplyRotation(FVector(0, 0, 1), YawValue * MouseResponsivenessMultiplier);
	}
}

void ASubspacePlayerPawn::EmergencyBrake()
{
	Velocity = FVector::ZeroVector;
	AngularVelocity = FVector::ZeroVector;
	UE_LOG(LogTemp, Log, TEXT("SubspacePlayerPawn: Emergency brake engaged"));
}

void ASubspacePlayerPawn::ZoomCamera(float Value)
{
	if (Value != 0.0f)
	{
		// Mouse wheel up (positive value) zooms in (decreases distance)
		// Mouse wheel down (negative value) zooms out (increases distance)
		CameraDistance = FMath::Clamp(
			CameraDistance - (Value * CameraZoomSpeed),
			MinCameraDistance,
			MaxCameraDistance
		);
		
		if (SpringArm)
		{
			SpringArm->TargetArmLength = CameraDistance;
		}
	}
}

void ASubspacePlayerPawn::ToggleCameraMode()
{
	bThirdPersonCamera = !bThirdPersonCamera;
	
	if (bThirdPersonCamera)
	{
		// Third person view
		if (SpringArm)
		{
			SpringArm->TargetArmLength = CameraDistance;
		}
		UE_LOG(LogTemp, Log, TEXT("SubspacePlayerPawn: Third person camera enabled"));
	}
	else
	{
		// First person view (cockpit)
		if (SpringArm)
		{
			SpringArm->TargetArmLength = 0.0f;
		}
		UE_LOG(LogTemp, Log, TEXT("SubspacePlayerPawn: First person camera enabled"));
	}
}
