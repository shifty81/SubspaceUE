// Copyright Epic Games, Inc. All Rights Reserved.

#include "SubspacePlayerPawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/StaticMeshComponent.h"

ASubspacePlayerPawn::ASubspacePlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create ship mesh
	ShipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	RootComponent = ShipMesh;
	ShipMesh->SetSimulatePhysics(false); // We'll handle physics manually

	// Create spring arm for camera
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 1000.0f;
	SpringArm->bDoCollisionTest = false;

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
}

void ASubspacePlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind movement inputs
	PlayerInputComponent->BindAxis("MoveForward", this, &ASubspacePlayerPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASubspacePlayerPawn::MoveRight);
	PlayerInputComponent->BindAxis("MoveUp", this, &ASubspacePlayerPawn::MoveUp);
	
	// Bind rotation inputs
	PlayerInputComponent->BindAxis("Pitch", this, &ASubspacePlayerPawn::PitchInput);
	PlayerInputComponent->BindAxis("Yaw", this, &ASubspacePlayerPawn::YawInput);
	PlayerInputComponent->BindAxis("Roll", this, &ASubspacePlayerPawn::RollInput);
	
	// Bind action inputs
	PlayerInputComponent->BindAction("Brake", IE_Pressed, this, &ASubspacePlayerPawn::EmergencyBrake);
}

void ASubspacePlayerPawn::ApplyThrust(const FVector& Direction, float Magnitude)
{
	FVector Force = Direction * Magnitude * MaxThrust;
	// Convert to world space
	FVector WorldForce = GetActorRotation().RotateVector(Force);
	Velocity += WorldForce * GetWorld()->GetDeltaSeconds();
}

void ASubspacePlayerPawn::ApplyRotation(const FVector& RotationAxis, float Magnitude)
{
	FVector Torque = RotationAxis * Magnitude * MaxRotationForce;
	AngularVelocity += Torque * GetWorld()->GetDeltaSeconds();
}

void ASubspacePlayerPawn::UpdatePhysics(float DeltaTime)
{
	// Apply velocity to position
	FVector NewLocation = GetActorLocation() + (Velocity * DeltaTime);
	SetActorLocation(NewLocation);

	// Apply drag
	Velocity *= (1.0f - DragCoefficient * DeltaTime);

	// Apply angular velocity to rotation
	FRotator DeltaRotation = FRotator(
		AngularVelocity.Y * DeltaTime,
		AngularVelocity.Z * DeltaTime,
		AngularVelocity.X * DeltaTime
	);
	AddActorLocalRotation(DeltaRotation);

	// Apply angular drag
	AngularVelocity *= (1.0f - DragCoefficient * DeltaTime);
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

void ASubspacePlayerPawn::EmergencyBrake()
{
	Velocity = FVector::ZeroVector;
	AngularVelocity = FVector::ZeroVector;
	UE_LOG(LogTemp, Log, TEXT("SubspacePlayerPawn: Emergency brake engaged"));
}
