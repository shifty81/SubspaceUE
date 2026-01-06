// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpaceSkyboxActor.generated.h"

/**
 * Space Skybox Actor
 * 
 * Provides a starfield background for space scenes
 * Features a large sphere with stars mapped to the interior
 */
UCLASS()
class SUBSPACEUE_API ASpaceSkyboxActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpaceSkyboxActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	/** Skybox mesh component (large inverted sphere) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Subspace|Skybox")
	class UStaticMeshComponent* SkyboxMesh;

	/** Skybox material */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subspace|Skybox")
	class UMaterialInterface* SkyboxMaterial;

	/** Skybox radius */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subspace|Skybox")
	float SkyboxRadius = 100000.0f;

	/** Star brightness multiplier */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subspace|Skybox", meta = (ClampMin = "0.0", ClampMax = "10.0"))
	float StarBrightness = 1.0f;

	/** Star density (0-1) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subspace|Skybox", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float StarDensity = 0.5f;

	/** Nebula color tint */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subspace|Skybox")
	FLinearColor NebulaColor = FLinearColor(0.1f, 0.05f, 0.2f, 1.0f);

	/** Enable slow rotation of the skybox */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subspace|Skybox")
	bool bRotateSkybox = false;

	/** Rotation speed (degrees per second) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subspace|Skybox")
	float RotationSpeed = 0.5f;

	/** Follow player camera */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subspace|Skybox")
	bool bFollowCamera = true;

	/** Update skybox material parameters */
	UFUNCTION(BlueprintCallable, Category = "Subspace|Skybox")
	void UpdateMaterialParameters();

	/** Create procedural star material */
	UFUNCTION(BlueprintCallable, Category = "Subspace|Skybox")
	void CreateProceduralStarfield();

protected:
	/** Dynamic material instance */
	UPROPERTY()
	class UMaterialInstanceDynamic* DynamicMaterial;

	/** Find and follow the player camera */
	void FollowPlayerCamera();
};
