// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NavigationComponent.generated.h"

/**
 * Travel modes (X4-inspired)
 */
UENUM(BlueprintType)
enum class ETravelMode : uint8
{
	StandardFlight UMETA(DisplayName = "Standard Flight"),  // Normal maneuvering
	Boost UMETA(DisplayName = "Boost"),                     // Shield drain for speed burst
	TravelDrive UMETA(DisplayName = "Travel Drive"),        // High-speed sector crossing
	Autopilot UMETA(DisplayName = "Autopilot"),            // Automated navigation
	Highway UMETA(DisplayName = "Highway"),                 // Highway travel
	Docked UMETA(DisplayName = "Docked")                   // Docked at station
};

/**
 * Autopilot state
 */
UENUM(BlueprintType)
enum class EAutopilotState : uint8
{
	Inactive UMETA(DisplayName = "Inactive"),
	NavigatingToTarget UMETA(DisplayName = "Navigating to Target"),
	ApproachingDock UMETA(DisplayName = "Approaching Dock"),
	Docking UMETA(DisplayName = "Docking"),
	TravelDriveCharging UMETA(DisplayName = "Travel Drive Charging"),
	TravelDriveActive UMETA(DisplayName = "Travel Drive Active")
};

/**
 * Flight assist settings
 */
USTRUCT(BlueprintType)
struct FFlightAssistSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flight Assist")
	bool bAutoRollEnabled = true;  // Auto-level ship roll

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flight Assist")
	bool bFlightAssistEnabled = true;  // Velocity damping

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flight Assist")
	bool bAimAssistEnabled = false;  // Aim prediction

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flight Assist")
	bool bCollisionAvoidanceEnabled = true;  // Automatic obstacle avoidance

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flight Assist")
	bool bMouseSteeringEnabled = false;  // Mouse steering mode

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flight Assist")
	float CollisionAvoidanceDistance = 500.0f;  // Distance to start avoiding (m)
};

/**
 * Waypoint for navigation
 */
USTRUCT(BlueprintType)
struct FNavigationWaypoint
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Waypoint")
	FVector Location = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Waypoint")
	FString WaypointName = TEXT("Waypoint");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Waypoint")
	AActor* TargetActor = nullptr;  // Follow this actor if set

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Waypoint")
	float ArrivalRadius = 100.0f;  // Consider arrived within this distance

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Waypoint")
	bool bUseTravelDrive = false;  // Use travel drive for this waypoint
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Waypoint")
	bool bDockOnArrival = false;  // Attempt to dock when arriving
};

/**
 * Jump gate data (for sector transitions)
 */
USTRUCT(BlueprintType)
struct FJumpGateData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump Gate")
	FString GateName = TEXT("Jump Gate");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump Gate")
	FVector Location = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump Gate")
	FString ConnectedSectorId = TEXT("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump Gate")
	bool bIsLocked = false;  // Requires mission/unlock

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump Gate")
	int32 ControllingFaction = 0;  // Faction ID
};

/**
 * Highway data (for fast intra-sector travel)
 */
USTRUCT(BlueprintType)
struct FHighwayData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Highway")
	TArray<FVector> PathPoints;  // Highway path

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Highway")
	float Speed = 14000.0f;  // Highway speed (m/s)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Highway")
	bool bIsBidirectional = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Highway")
	int32 MaxShipSize = 2;  // 1=S, 2=M (L/XL can't use local highways)
};

/**
 * Component that manages ship navigation and travel modes
 * X4-style travel system with boost, travel drive, autopilot, and highways
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SUBSPACEUE_API UNavigationComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UNavigationComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** Current travel mode */
	UPROPERTY(BlueprintReadOnly, Category = "Navigation")
	ETravelMode CurrentTravelMode = ETravelMode::StandardFlight;

	/** Autopilot state */
	UPROPERTY(BlueprintReadOnly, Category = "Navigation")
	EAutopilotState AutopilotState = EAutopilotState::Inactive;

	/** Flight assist settings */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Navigation")
	FFlightAssistSettings FlightAssist;

	/** Current waypoint queue */
	UPROPERTY(BlueprintReadOnly, Category = "Navigation")
	TArray<FNavigationWaypoint> WaypointQueue;

	/** Current target for autopilot */
	UPROPERTY(BlueprintReadOnly, Category = "Navigation")
	AActor* CurrentTarget = nullptr;

	/** Travel drive charge percentage (0-100) */
	UPROPERTY(BlueprintReadOnly, Category = "Navigation")
	float TravelDriveCharge = 0.0f;

	/** Boost fuel remaining (0-100) */
	UPROPERTY(BlueprintReadOnly, Category = "Navigation")
	float BoostFuel = 100.0f;

	/** Maximum boost fuel */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Navigation")
	float MaxBoostFuel = 100.0f;

	/** Boost fuel regeneration rate per second */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Navigation")
	float BoostRegenRate = 10.0f;

	/** Travel drive charge time in seconds */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Navigation")
	float TravelDriveChargeTime = 3.0f;

	/** Travel drive speed multiplier */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Navigation")
	float TravelDriveSpeedMultiplier = 10.0f;

	/** Boost speed multiplier */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Navigation")
	float BoostSpeedMultiplier = 2.0f;

	// ===== Travel Mode Control =====

	/** Set travel mode */
	UFUNCTION(BlueprintCallable, Category = "Navigation")
	void SetTravelMode(ETravelMode NewMode);

	/** Activate boost */
	UFUNCTION(BlueprintCallable, Category = "Navigation")
	bool ActivateBoost();

	/** Deactivate boost */
	UFUNCTION(BlueprintCallable, Category = "Navigation")
	void DeactivateBoost();

	/** Start charging travel drive */
	UFUNCTION(BlueprintCallable, Category = "Navigation")
	bool StartTravelDrive();

	/** Cancel travel drive */
	UFUNCTION(BlueprintCallable, Category = "Navigation")
	void CancelTravelDrive();

	/** Check if can activate travel drive */
	UFUNCTION(BlueprintCallable, Category = "Navigation")
	bool CanActivateTravelDrive() const;

	// ===== Autopilot =====

	/** Start autopilot to location */
	UFUNCTION(BlueprintCallable, Category = "Navigation")
	void StartAutopilot(FVector TargetLocation, bool bUseTravelDrive = true, bool bDockOnArrival = false);

	/** Start autopilot to actor */
	UFUNCTION(BlueprintCallable, Category = "Navigation")
	void StartAutopilotToActor(AActor* TargetActor, bool bUseTravelDrive = true, bool bDockOnArrival = false);

	/** Add waypoint to queue */
	UFUNCTION(BlueprintCallable, Category = "Navigation")
	void AddWaypoint(const FNavigationWaypoint& Waypoint);

	/** Clear all waypoints */
	UFUNCTION(BlueprintCallable, Category = "Navigation")
	void ClearWaypoints();

	/** Cancel autopilot */
	UFUNCTION(BlueprintCallable, Category = "Navigation")
	void CancelAutopilot();

	/** Get distance to current waypoint */
	UFUNCTION(BlueprintCallable, Category = "Navigation")
	float GetDistanceToWaypoint() const;

	// ===== Flight Assist =====

	/** Toggle auto roll */
	UFUNCTION(BlueprintCallable, Category = "Navigation")
	void ToggleAutoRoll();

	/** Toggle flight assist */
	UFUNCTION(BlueprintCallable, Category = "Navigation")
	void ToggleFlightAssist();

	/** Toggle aim assist */
	UFUNCTION(BlueprintCallable, Category = "Navigation")
	void ToggleAimAssist();

	/** Toggle collision avoidance */
	UFUNCTION(BlueprintCallable, Category = "Navigation")
	void ToggleCollisionAvoidance();

	/** Toggle mouse steering */
	UFUNCTION(BlueprintCallable, Category = "Navigation")
	void ToggleMouseSteering();

	// ===== Jump Gates & Highways =====

	/** Activate nearby jump gate */
	UFUNCTION(BlueprintCallable, Category = "Navigation")
	bool ActivateJumpGate();

	/** Enter nearby highway */
	UFUNCTION(BlueprintCallable, Category = "Navigation")
	bool EnterHighway();

	/** Exit highway */
	UFUNCTION(BlueprintCallable, Category = "Navigation")
	void ExitHighway();

	/** Check if near jump gate */
	UFUNCTION(BlueprintCallable, Category = "Navigation")
	bool IsNearJumpGate(float MaxDistance = 500.0f) const;

	/** Check if near highway entrance */
	UFUNCTION(BlueprintCallable, Category = "Navigation")
	bool IsNearHighway(float MaxDistance = 500.0f) const;

	// ===== Docking =====

	/** Request docking at station */
	UFUNCTION(BlueprintCallable, Category = "Navigation")
	bool RequestDocking(AActor* Station);

	/** Cancel docking */
	UFUNCTION(BlueprintCallable, Category = "Navigation")
	void CancelDocking();

	/** Complete docking */
	UFUNCTION(BlueprintCallable, Category = "Navigation")
	void CompleteDocking();

	/** Undock from station */
	UFUNCTION(BlueprintCallable, Category = "Navigation")
	void Undock();

protected:
	/** Update autopilot navigation */
	void UpdateAutopilot(float DeltaTime);

	/** Update travel drive charging */
	void UpdateTravelDrive(float DeltaTime);

	/** Update boost fuel */
	void UpdateBoostFuel(float DeltaTime);

	/** Apply flight assist forces */
	void ApplyFlightAssist(float DeltaTime);

	/** Check and avoid collisions */
	void UpdateCollisionAvoidance(float DeltaTime);

	/** Get next waypoint */
	FNavigationWaypoint* GetCurrentWaypoint();

	/** Remove current waypoint and move to next */
	void AdvanceToNextWaypoint();

	/** Timer for travel drive charging */
	float TravelDriveTimer = 0.0f;

	/** Currently docked station */
	UPROPERTY()
	AActor* DockedStation = nullptr;
};
