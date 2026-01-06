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

	/** Camera component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Subspace|Camera")
	class UCameraComponent* Camera;

	/** Camera spring arm */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Subspace|Camera")
	class USpringArmComponent* SpringArm;

	/** Current velocity */
	UPROPERTY(BlueprintReadOnly, Category = "Subspace|Physics")
	FVector Velocity;

	/** Current angular velocity */
	UPROPERTY(BlueprintReadOnly, Category = "Subspace|Physics")
	FVector AngularVelocity;

	/** Maximum thrust force */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subspace|Physics")
	float MaxThrust = 10000.0f;

	/** Maximum rotation force */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subspace|Physics")
	float MaxRotationForce = 5000.0f;

	/** Drag coefficient */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subspace|Physics")
	float DragCoefficient = 0.1f;

protected:
	/** Apply thrust in given direction */
	void ApplyThrust(const FVector& Direction, float Magnitude);

	/** Apply rotation */
	void ApplyRotation(const FVector& RotationAxis, float Magnitude);

	/** Update Newtonian physics */
	void UpdatePhysics(float DeltaTime);

	// Input handlers
	void MoveForward(float Value);
	void MoveRight(float Value);
	void MoveUp(float Value);
	void PitchInput(float Value);
	void YawInput(float Value);
	void RollInput(float Value);
	void EmergencyBrake();
};
