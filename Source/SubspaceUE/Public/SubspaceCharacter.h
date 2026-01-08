// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SubspaceCharacter.generated.h"

/**
 * First-person character for walking around ship interiors and space stations
 */
UCLASS()
class SUBSPACEUE_API ASubspaceCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASubspaceCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** First-person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Subspace|Camera")
	class UCameraComponent* FirstPersonCamera;

	/** Walking speed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subspace|Movement")
	float WalkSpeed = 400.0f;

	/** Sprint speed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subspace|Movement")
	float SprintSpeed = 800.0f;

	/** Whether character is currently sprinting */
	UPROPERTY(BlueprintReadOnly, Category = "Subspace|Movement")
	bool bIsSprinting = false;

	/** Mouse look sensitivity for pitch */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subspace|Controls")
	float MousePitchSensitivity = 1.0f;

	/** Mouse look sensitivity for yaw */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subspace|Controls")
	float MouseYawSensitivity = 1.0f;

	/** Invert mouse pitch axis */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subspace|Controls")
	bool bInvertMousePitch = false;

	/** Reference to nearby ship that can be entered */
	UPROPERTY(BlueprintReadOnly, Category = "Subspace|Ship")
	class ASubspacePlayerPawn* NearbyShip;

	/** Distance to detect nearby ships for entering */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subspace|Ship")
	float ShipDetectionRange = 500.0f;

	// Input handlers
	void MoveForward(float Value);
	void MoveRight(float Value);
	void LookUp(float Value);
	void LookRight(float Value);
	void SprintPressed();
	void SprintReleased();
	void EnterExitShip();

protected:
	/** Check for nearby ships */
	void CheckForNearbyShip();
};
