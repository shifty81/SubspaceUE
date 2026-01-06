// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpaceActor.generated.h"

/**
 * Base class for space objects like asteroids
 */
UCLASS()
class SUBSPACEUE_API ASpaceActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpaceActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	/** Visual mesh for the space object */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Subspace|Visuals")
	class UStaticMeshComponent* Mesh;

	/** Rotation speed for visual effect */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subspace|Visuals")
	FVector RotationSpeed;
};
