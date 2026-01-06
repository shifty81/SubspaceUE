// Copyright Epic Games, Inc. All Rights Reserved.

#include "SpaceActor.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

ASpaceActor::ASpaceActor()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create mesh component
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
	
	// Load a default mesh (sphere for asteroids/ships)
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMeshAsset(TEXT("/Engine/BasicShapes/Sphere"));
	if (SphereMeshAsset.Succeeded())
	{
		Mesh->SetStaticMesh(SphereMeshAsset.Object);
	}

	// Set default rotation speed
	RotationSpeed = FVector(0.0f, 0.0f, 10.0f);
}

void ASpaceActor::BeginPlay()
{
	Super::BeginPlay();
}

void ASpaceActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Apply rotation for visual effect
	FRotator DeltaRotation = FRotator(
		RotationSpeed.Y * DeltaTime,
		RotationSpeed.Z * DeltaTime,
		RotationSpeed.X * DeltaTime
	);
	AddActorLocalRotation(DeltaRotation);
}
