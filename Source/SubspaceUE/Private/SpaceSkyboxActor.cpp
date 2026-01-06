// Copyright Epic Games, Inc. All Rights Reserved.

#include "SpaceSkyboxActor.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInterface.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "Camera/PlayerCameraManager.h"
#include "GameFramework/PlayerController.h"

ASpaceSkyboxActor::ASpaceSkyboxActor()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create skybox mesh component
	SkyboxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SkyboxMesh"));
	RootComponent = SkyboxMesh;
	
	// Load sphere mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("/Engine/BasicShapes/Sphere"));
	if (SphereMesh.Succeeded())
	{
		SkyboxMesh->SetStaticMesh(SphereMesh.Object);
		SkyboxMesh->SetWorldScale3D(FVector(SkyboxRadius / 50.0f)); // Scale to desired radius
	}

	// Set up mesh properties
	SkyboxMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SkyboxMesh->SetCastShadow(false);
	SkyboxMesh->bVisibleInReflectionCaptures = false;
	SkyboxMesh->bVisibleInRayTracing = false;
	SkyboxMesh->bVisibleInRealTimeSkyCaptures = false;

	// Flip normals by scaling negatively (so we see the inside of the sphere)
	SkyboxMesh->SetRelativeScale3D(FVector(-SkyboxRadius / 50.0f, SkyboxRadius / 50.0f, SkyboxRadius / 50.0f));
}

void ASpaceSkyboxActor::BeginPlay()
{
	Super::BeginPlay();
	
	// Create dynamic material instance if a base material is set
	if (SkyboxMaterial && SkyboxMesh)
	{
		DynamicMaterial = UMaterialInstanceDynamic::Create(SkyboxMaterial, this);
		SkyboxMesh->SetMaterial(0, DynamicMaterial);
		UpdateMaterialParameters();
	}
	else
	{
		// Create a simple procedural starfield if no material is provided
		CreateProceduralStarfield();
	}
	
	UE_LOG(LogTemp, Log, TEXT("SpaceSkyboxActor: Initialized skybox"));
}

void ASpaceSkyboxActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Follow camera if enabled
	if (bFollowCamera)
	{
		FollowPlayerCamera();
	}

	// Rotate skybox if enabled
	if (bRotateSkybox)
	{
		FRotator NewRotation = GetActorRotation();
		NewRotation.Yaw += RotationSpeed * DeltaTime;
		SetActorRotation(NewRotation);
	}
}

void ASpaceSkyboxActor::UpdateMaterialParameters()
{
	if (!DynamicMaterial)
	{
		return;
	}

	// Update material parameters
	DynamicMaterial->SetScalarParameterValue(TEXT("StarBrightness"), StarBrightness);
	DynamicMaterial->SetScalarParameterValue(TEXT("StarDensity"), StarDensity);
	DynamicMaterial->SetVectorParameterValue(TEXT("NebulaColor"), NebulaColor);
}

void ASpaceSkyboxActor::CreateProceduralStarfield()
{
	// This is a placeholder - in a real implementation, you would:
	// 1. Create a material with noise functions for stars
	// 2. Use particle systems for distant stars
	// 3. Or use a pre-made space skybox texture
	
	UE_LOG(LogTemp, Warning, TEXT("SpaceSkyboxActor: No skybox material set. Please assign a starfield material in the editor."));
	UE_LOG(LogTemp, Log, TEXT("SpaceSkyboxActor: You can use a basic emissive material with a star texture, or create one using the Material Editor."));
}

void ASpaceSkyboxActor::FollowPlayerCamera()
{
	if (UWorld* World = GetWorld())
	{
		if (APlayerController* PC = World->GetFirstPlayerController())
		{
			if (APlayerCameraManager* CameraManager = PC->PlayerCameraManager)
			{
				// Move skybox to camera location so it appears infinitely far away
				FVector CameraLocation = CameraManager->GetCameraLocation();
				SetActorLocation(CameraLocation);
			}
		}
	}
}
