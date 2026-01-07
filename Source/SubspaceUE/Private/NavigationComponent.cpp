// Copyright Epic Games, Inc. All Rights Reserved.

#include "NavigationComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

DEFINE_LOG_CATEGORY_STATIC(LogNavigation, Log, All);

UNavigationComponent::UNavigationComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = 0.0f;  // Tick every frame for smooth navigation
}

void UNavigationComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// Initialize boost fuel to full
	BoostFuel = MaxBoostFuel;
}

void UNavigationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// Update autopilot
	if (AutopilotState != EAutopilotState::Inactive)
	{
		UpdateAutopilot(DeltaTime);
	}
	
	// Update travel drive
	if (CurrentTravelMode == ETravelMode::TravelDrive || AutopilotState == EAutopilotState::TravelDriveCharging)
	{
		UpdateTravelDrive(DeltaTime);
	}
	
	// Update boost fuel
	UpdateBoostFuel(DeltaTime);
	
	// Apply flight assist
	if (FlightAssist.bFlightAssistEnabled || FlightAssist.bAutoRollEnabled || FlightAssist.bCollisionAvoidanceEnabled)
	{
		ApplyFlightAssist(DeltaTime);
	}
	
	// Check collision avoidance
	if (FlightAssist.bCollisionAvoidanceEnabled)
	{
		UpdateCollisionAvoidance(DeltaTime);
	}
}

// ===== Travel Mode Control =====

void UNavigationComponent::SetTravelMode(ETravelMode NewMode)
{
	if (CurrentTravelMode == NewMode)
	{
		return;
	}
	
	ETravelMode OldMode = CurrentTravelMode;
	CurrentTravelMode = NewMode;
	
	UE_LOG(LogNavigation, Log, TEXT("Travel mode changed: %d -> %d"), (int32)OldMode, (int32)NewMode);
	
	// Reset state when changing modes
	if (NewMode != ETravelMode::Boost)
	{
		DeactivateBoost();
	}
	if (NewMode != ETravelMode::TravelDrive)
	{
		TravelDriveCharge = 0.0f;
		TravelDriveTimer = 0.0f;
	}
}

bool UNavigationComponent::ActivateBoost()
{
	if (CurrentTravelMode == ETravelMode::TravelDrive)
	{
		UE_LOG(LogNavigation, Warning, TEXT("Cannot boost while in travel drive"));
		return false;
	}
	
	if (BoostFuel <= 0.0f)
	{
		UE_LOG(LogNavigation, Warning, TEXT("Insufficient boost fuel"));
		return false;
	}
	
	SetTravelMode(ETravelMode::Boost);
	UE_LOG(LogNavigation, Log, TEXT("Boost activated"));
	return true;
}

void UNavigationComponent::DeactivateBoost()
{
	if (CurrentTravelMode == ETravelMode::Boost)
	{
		SetTravelMode(ETravelMode::StandardFlight);
		UE_LOG(LogNavigation, Log, TEXT("Boost deactivated"));
	}
}

bool UNavigationComponent::StartTravelDrive()
{
	if (!CanActivateTravelDrive())
	{
		return false;
	}
	
	AutopilotState = EAutopilotState::TravelDriveCharging;
	TravelDriveTimer = 0.0f;
	TravelDriveCharge = 0.0f;
	
	UE_LOG(LogNavigation, Log, TEXT("Travel drive charging..."));
	return true;
}

void UNavigationComponent::CancelTravelDrive()
{
	if (CurrentTravelMode == ETravelMode::TravelDrive)
	{
		SetTravelMode(ETravelMode::StandardFlight);
	}
	
	if (AutopilotState == EAutopilotState::TravelDriveCharging)
	{
		AutopilotState = EAutopilotState::NavigatingToTarget;
	}
	
	TravelDriveTimer = 0.0f;
	TravelDriveCharge = 0.0f;
	
	UE_LOG(LogNavigation, Log, TEXT("Travel drive cancelled"));
}

bool UNavigationComponent::CanActivateTravelDrive() const
{
	// Can't use travel drive if docked or in certain states
	if (CurrentTravelMode == ETravelMode::Docked)
	{
		return false;
	}
	
	// Check if ship has travel drive installed
	// TODO: Check equipment component for travel drive
	
	return true;
}

// ===== Autopilot =====

void UNavigationComponent::StartAutopilot(FVector TargetLocation, bool bUseTravelDrive, bool bDockOnArrival)
{
	FNavigationWaypoint Waypoint;
	Waypoint.Location = TargetLocation;
	Waypoint.WaypointName = TEXT("Autopilot Target");
	Waypoint.bUseTravelDrive = bUseTravelDrive;
	Waypoint.bDockOnArrival = bDockOnArrival;
	Waypoint.ArrivalRadius = 100.0f;
	
	WaypointQueue.Empty();
	WaypointQueue.Add(Waypoint);
	
	AutopilotState = EAutopilotState::NavigatingToTarget;
	CurrentTarget = nullptr;
	
	UE_LOG(LogNavigation, Log, TEXT("Autopilot started to location: %s"), *TargetLocation.ToString());
}

void UNavigationComponent::StartAutopilotToActor(AActor* TargetActor, bool bUseTravelDrive, bool bDockOnArrival)
{
	if (!TargetActor)
	{
		UE_LOG(LogNavigation, Warning, TEXT("Cannot start autopilot: Invalid target actor"));
		return;
	}
	
	FNavigationWaypoint Waypoint;
	Waypoint.Location = TargetActor->GetActorLocation();
	Waypoint.WaypointName = TargetActor->GetName();
	Waypoint.TargetActor = TargetActor;
	Waypoint.bUseTravelDrive = bUseTravelDrive;
	Waypoint.bDockOnArrival = bDockOnArrival;
	Waypoint.ArrivalRadius = 200.0f;
	
	WaypointQueue.Empty();
	WaypointQueue.Add(Waypoint);
	
	AutopilotState = EAutopilotState::NavigatingToTarget;
	CurrentTarget = TargetActor;
	
	UE_LOG(LogNavigation, Log, TEXT("Autopilot started to actor: %s"), *TargetActor->GetName());
}

void UNavigationComponent::AddWaypoint(const FNavigationWaypoint& Waypoint)
{
	WaypointQueue.Add(Waypoint);
	
	if (AutopilotState == EAutopilotState::Inactive)
	{
		AutopilotState = EAutopilotState::NavigatingToTarget;
	}
	
	UE_LOG(LogNavigation, Log, TEXT("Waypoint added: %s"), *Waypoint.WaypointName);
}

void UNavigationComponent::ClearWaypoints()
{
	WaypointQueue.Empty();
	CurrentTarget = nullptr;
	UE_LOG(LogNavigation, Log, TEXT("Waypoints cleared"));
}

void UNavigationComponent::CancelAutopilot()
{
	AutopilotState = EAutopilotState::Inactive;
	ClearWaypoints();
	CancelTravelDrive();
	SetTravelMode(ETravelMode::StandardFlight);
	
	UE_LOG(LogNavigation, Log, TEXT("Autopilot cancelled"));
}

float UNavigationComponent::GetDistanceToWaypoint() const
{
	if (WaypointQueue.Num() == 0)
	{
		return 0.0f;
	}
	
	const FNavigationWaypoint& Waypoint = WaypointQueue[0];
	FVector CurrentLocation = GetOwner()->GetActorLocation();
	
	if (Waypoint.TargetActor)
	{
		return FVector::Dist(CurrentLocation, Waypoint.TargetActor->GetActorLocation());
	}
	
	return FVector::Dist(CurrentLocation, Waypoint.Location);
}

// ===== Flight Assist =====

void UNavigationComponent::ToggleAutoRoll()
{
	FlightAssist.bAutoRollEnabled = !FlightAssist.bAutoRollEnabled;
	UE_LOG(LogNavigation, Log, TEXT("Auto Roll: %s"), FlightAssist.bAutoRollEnabled ? TEXT("ON") : TEXT("OFF"));
}

void UNavigationComponent::ToggleFlightAssist()
{
	FlightAssist.bFlightAssistEnabled = !FlightAssist.bFlightAssistEnabled;
	UE_LOG(LogNavigation, Log, TEXT("Flight Assist: %s"), FlightAssist.bFlightAssistEnabled ? TEXT("ON") : TEXT("OFF"));
}

void UNavigationComponent::ToggleAimAssist()
{
	FlightAssist.bAimAssistEnabled = !FlightAssist.bAimAssistEnabled;
	UE_LOG(LogNavigation, Log, TEXT("Aim Assist: %s"), FlightAssist.bAimAssistEnabled ? TEXT("ON") : TEXT("OFF"));
}

void UNavigationComponent::ToggleCollisionAvoidance()
{
	FlightAssist.bCollisionAvoidanceEnabled = !FlightAssist.bCollisionAvoidanceEnabled;
	UE_LOG(LogNavigation, Log, TEXT("Collision Avoidance: %s"), FlightAssist.bCollisionAvoidanceEnabled ? TEXT("ON") : TEXT("OFF"));
}

void UNavigationComponent::ToggleMouseSteering()
{
	FlightAssist.bMouseSteeringEnabled = !FlightAssist.bMouseSteeringEnabled;
	UE_LOG(LogNavigation, Log, TEXT("Mouse Steering: %s"), FlightAssist.bMouseSteeringEnabled ? TEXT("ON") : TEXT("OFF"));
}

// ===== Jump Gates & Highways =====

bool UNavigationComponent::ActivateJumpGate()
{
	if (!IsNearJumpGate())
	{
		UE_LOG(LogNavigation, Warning, TEXT("No jump gate in range"));
		return false;
	}
	
	// TODO: Find nearest jump gate and initiate jump
	// TODO: Trigger sector transition
	
	UE_LOG(LogNavigation, Log, TEXT("Jump gate activated"));
	return true;
}

bool UNavigationComponent::EnterHighway()
{
	if (!IsNearHighway())
	{
		UE_LOG(LogNavigation, Warning, TEXT("No highway entrance in range"));
		return false;
	}
	
	SetTravelMode(ETravelMode::Highway);
	UE_LOG(LogNavigation, Log, TEXT("Entered highway"));
	return true;
}

void UNavigationComponent::ExitHighway()
{
	if (CurrentTravelMode == ETravelMode::Highway)
	{
		SetTravelMode(ETravelMode::StandardFlight);
		UE_LOG(LogNavigation, Log, TEXT("Exited highway"));
	}
}

bool UNavigationComponent::IsNearJumpGate(float MaxDistance) const
{
	// TODO: Query for nearby jump gates
	return false;
}

bool UNavigationComponent::IsNearHighway(float MaxDistance) const
{
	// TODO: Query for nearby highways
	return false;
}

// ===== Docking =====

bool UNavigationComponent::RequestDocking(AActor* Station)
{
	if (!Station)
	{
		return false;
	}
	
	// TODO: Check if station has available docking port
	// TODO: Request docking permission
	
	CurrentTarget = Station;
	AutopilotState = EAutopilotState::ApproachingDock;
	
	UE_LOG(LogNavigation, Log, TEXT("Docking requested at: %s"), *Station->GetName());
	return true;
}

void UNavigationComponent::CancelDocking()
{
	if (AutopilotState == EAutopilotState::ApproachingDock || AutopilotState == EAutopilotState::Docking)
	{
		AutopilotState = EAutopilotState::Inactive;
		CurrentTarget = nullptr;
		UE_LOG(LogNavigation, Log, TEXT("Docking cancelled"));
	}
}

void UNavigationComponent::CompleteDocking()
{
	if (AutopilotState == EAutopilotState::Docking)
	{
		SetTravelMode(ETravelMode::Docked);
		AutopilotState = EAutopilotState::Inactive;
		DockedStation = CurrentTarget;
		
		UE_LOG(LogNavigation, Log, TEXT("Docking complete"));
	}
}

void UNavigationComponent::Undock()
{
	if (CurrentTravelMode == ETravelMode::Docked)
	{
		SetTravelMode(ETravelMode::StandardFlight);
		DockedStation = nullptr;
		
		// Move ship away from station
		// TODO: Apply undocking thrust
		
		UE_LOG(LogNavigation, Log, TEXT("Undocked"));
	}
}

// ===== Protected Helper Methods =====

void UNavigationComponent::UpdateAutopilot(float DeltaTime)
{
	FNavigationWaypoint* CurrentWaypoint = GetCurrentWaypoint();
	if (!CurrentWaypoint)
	{
		AutopilotState = EAutopilotState::Inactive;
		return;
	}
	
	// Update target location if following actor
	if (CurrentWaypoint->TargetActor)
	{
		CurrentWaypoint->Location = CurrentWaypoint->TargetActor->GetActorLocation();
	}
	
	float Distance = GetDistanceToWaypoint();
	
	// Check if arrived
	if (Distance <= CurrentWaypoint->ArrivalRadius)
	{
		UE_LOG(LogNavigation, Log, TEXT("Arrived at waypoint: %s"), *CurrentWaypoint->WaypointName);
		
		if (CurrentWaypoint->bDockOnArrival && CurrentWaypoint->TargetActor)
		{
			RequestDocking(CurrentWaypoint->TargetActor);
		}
		
		AdvanceToNextWaypoint();
		return;
	}
	
	// Navigation logic
	switch (AutopilotState)
	{
	case EAutopilotState::NavigatingToTarget:
		// TODO: Calculate steering input toward target
		// TODO: Manage speed based on distance
		
		// Check if should use travel drive
		if (CurrentWaypoint->bUseTravelDrive && Distance > 5000.0f && CanActivateTravelDrive())
		{
			StartTravelDrive();
		}
		break;
		
	case EAutopilotState::TravelDriveCharging:
		// Handled in UpdateTravelDrive
		break;
		
	case EAutopilotState::TravelDriveActive:
		// TODO: Navigate at high speed
		// Cancel travel drive when close to target
		if (Distance < 1000.0f)
		{
			CancelTravelDrive();
		}
		break;
		
	case EAutopilotState::ApproachingDock:
		// TODO: Careful approach to station
		if (Distance < 50.0f)
		{
			AutopilotState = EAutopilotState::Docking;
		}
		break;
		
	case EAutopilotState::Docking:
		// TODO: Final docking alignment
		if (Distance < 10.0f)
		{
			CompleteDocking();
		}
		break;
	}
}

void UNavigationComponent::UpdateTravelDrive(float DeltaTime)
{
	if (AutopilotState == EAutopilotState::TravelDriveCharging)
	{
		TravelDriveTimer += DeltaTime;
		TravelDriveCharge = FMath::Clamp((TravelDriveTimer / TravelDriveChargeTime) * 100.0f, 0.0f, 100.0f);
		
		if (TravelDriveCharge >= 100.0f)
		{
			SetTravelMode(ETravelMode::TravelDrive);
			AutopilotState = EAutopilotState::TravelDriveActive;
			UE_LOG(LogNavigation, Log, TEXT("Travel drive activated"));
		}
	}
}

void UNavigationComponent::UpdateBoostFuel(float DeltaTime)
{
	if (CurrentTravelMode == ETravelMode::Boost)
	{
		// Consume boost fuel
		BoostFuel = FMath::Max(0.0f, BoostFuel - (20.0f * DeltaTime));
		
		if (BoostFuel <= 0.0f)
		{
			DeactivateBoost();
		}
	}
	else
	{
		// Regenerate boost fuel
		BoostFuel = FMath::Min(MaxBoostFuel, BoostFuel + (BoostRegenRate * DeltaTime));
	}
}

void UNavigationComponent::ApplyFlightAssist(float DeltaTime)
{
	// TODO: Implement flight assist forces
	// - Auto roll to level
	// - Velocity damping
	// - Collision avoidance adjustments
}

void UNavigationComponent::UpdateCollisionAvoidance(float DeltaTime)
{
	// TODO: Raycast ahead for obstacles
	// TODO: Calculate avoidance vector
	// TODO: Apply corrective forces
}

FNavigationWaypoint* UNavigationComponent::GetCurrentWaypoint()
{
	if (WaypointQueue.Num() > 0)
	{
		return &WaypointQueue[0];
	}
	return nullptr;
}

void UNavigationComponent::AdvanceToNextWaypoint()
{
	if (WaypointQueue.Num() > 0)
	{
		WaypointQueue.RemoveAt(0);
	}
	
	if (WaypointQueue.Num() == 0)
	{
		AutopilotState = EAutopilotState::Inactive;
		CurrentTarget = nullptr;
		UE_LOG(LogNavigation, Log, TEXT("All waypoints reached"));
	}
}
