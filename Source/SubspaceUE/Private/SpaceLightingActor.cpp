// Copyright Epic Games, Inc. All Rights Reserved.

#include "SpaceLightingActor.h"
#include "Components/DirectionalLightComponent.h"
#include "Components/SkyLightComponent.h"

ASpaceLightingActor::ASpaceLightingActor()
{
	PrimaryActorTick.bCanEverTick = false;

	// Create root scene component
	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	// Create directional light (sun)
	DirectionalLight = CreateDefaultSubobject<UDirectionalLightComponent>(TEXT("DirectionalLight"));
	DirectionalLight->SetupAttachment(RootComponent);
	DirectionalLight->SetIntensity(5.0f);
	DirectionalLight->SetLightColor(FLinearColor(1.0f, 0.95f, 0.9f)); // Slightly warm white
	DirectionalLight->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));

	// Create sky light for ambient illumination
	SkyLight = CreateDefaultSubobject<USkyLightComponent>(TEXT("SkyLight"));
	SkyLight->SetupAttachment(RootComponent);
	SkyLight->SetIntensity(0.5f);
	SkyLight->SetLightColor(FLinearColor(0.2f, 0.2f, 0.3f)); // Deep blue ambient
	SkyLight->SourceType = ESkyLightSourceType::SLS_CapturedScene;
}

void ASpaceLightingActor::BeginPlay()
{
	Super::BeginPlay();
	
	// Recapture sky light
	if (SkyLight)
	{
		SkyLight->RecaptureSky();
	}
}
