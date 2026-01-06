// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpaceLightingActor.generated.h"

/**
 * Actor that provides basic space lighting
 */
UCLASS()
class SUBSPACEUE_API ASpaceLightingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpaceLightingActor();

protected:
	virtual void BeginPlay() override;

public:	
	/** Directional light component (acts as sun) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lighting")
	class UDirectionalLightComponent* DirectionalLight;

	/** Sky light component for ambient lighting */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lighting")
	class USkyLightComponent* SkyLight;
};
