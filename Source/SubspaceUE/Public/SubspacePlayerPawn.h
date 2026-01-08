// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SubspacePlayerPawn.generated.h"

/**
 * Player Pawn representing the spaceship
 * 
 * Features 6DOF movement with Newtonian physics simulation
 */
UCLASS()
class SUBSPACEUE_API ASubspacePlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	ASubspacePlayerPawn();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Ship mesh component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Subspace|Ship")
	class UStaticMeshComponent* ShipMesh;
	
	/** Base material for ship mesh */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subspace|Ship")
	class UMaterial* ShipBaseMaterial;
	
	/** Ship color for material */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subspace|Ship")
	FLinearColor ShipColor = FLinearColor(0.2f, 0.4f, 0.8f, 1.0f);

	/** Camera component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Subspace|Camera")
	class UCameraComponent* Camera;

	/** Camera spring arm */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Subspace|Camera")
	class USpringArmComponent* SpringArm;

	/** Camera distance from ship */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subspace|Camera")
	float CameraDistance = 1000.0f;

	/** Minimum camera distance */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subspace|Camera")
	float MinCameraDistance = 300.0f;

	/** Maximum camera distance */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subspace|Camera")
	float MaxCameraDistance = 5000.0f;

	/** Camera zoom speed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subspace|Camera")
	float CameraZoomSpeed = 100.0f;

	/** Camera pitch offset (degrees) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subspace|Camera")
	float CameraPitchOffset = -15.0f;

	/** Enable third-person camera mode */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subspace|Camera")
	bool bThirdPersonCamera = true;

	/** Camera lag speed for smooth following */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subspace|Camera")
	float CameraLagSpeed = 3.0f;

	/** Current velocity */
	UPROPERTY(BlueprintReadOnly, Category = "Subspace|Physics")
	FVector Velocity;

	/** Current angular velocity */
	UPROPERTY(BlueprintReadOnly, Category = "Subspace|Physics")
	FVector AngularVelocity;

	/** Maximum thrust force (in Newtons, scaled for UE units: cm) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subspace|Physics")
	float MaxThrust = 50000.0f;

	/** Maximum rotation force */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subspace|Physics")
	float MaxRotationForce = 5000.0f;

	/** Drag coefficient (higher = more drag, slower max speed) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subspace|Physics")
	float DragCoefficient = 0.5f;

	/** Ship mass in kg */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subspace|Physics")
	float ShipMass = 1000.0f;

	/** Mouse look sensitivity for pitch */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subspace|Controls")
	float MousePitchSensitivity = 1.0f;

	/** Mouse look sensitivity for yaw */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subspace|Controls")
	float MouseYawSensitivity = 1.0f;

	/** Invert mouse pitch axis */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subspace|Controls")
	bool bInvertMousePitch = false;

	/** Invert mouse yaw axis */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subspace|Controls")
	bool bInvertMouseYaw = false;

	/** Mouse responsiveness multiplier (higher = more responsive) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subspace|Controls")
	float MouseResponsivenessMultiplier = 0.5f;

	/** Boost multiplier when boost is active */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subspace|Controls")
	float BoostMultiplier = 2.0f;

	/** Whether boost is currently active */
	UPROPERTY(BlueprintReadOnly, Category = "Subspace|Controls")
	bool bBoostActive = false;

	// Input handlers - Public to allow controller access
	void MoveForward(float Value);
	void MoveRight(float Value);
	void MoveUp(float Value);
	void PitchInput(float Value);
	void YawInput(float Value);
	void RollInput(float Value);
	void LookUp(float Value);
	void LookRight(float Value);
	void EmergencyBrake();
	void ZoomCamera(float Value);
	void ToggleCameraMode();
	void BoostPressed();
	void BoostReleased();
	void ExitShip();

protected:
	/** Apply thrust in given direction */
	void ApplyThrust(const FVector& Direction, float Magnitude);

	/** Apply rotation */
	void ApplyRotation(const FVector& RotationAxis, float Magnitude);

	/** Update Newtonian physics */
	void UpdatePhysics(float DeltaTime);
};
