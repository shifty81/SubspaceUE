// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SpaceActor.h"
#include "PlanetActor.generated.h"

/**
 * Planet actor that orbits around a central point (sun) with configurable orbital parameters
 * Supports elliptical orbits with real-world astronomical data
 */
UCLASS()
class SUBSPACEUE_API APlanetActor : public ASpaceActor
{
	GENERATED_BODY()
	
public:	
	APlanetActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	/** Name of the planet */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Planet|Info")
	FString PlanetName;

	/** Semi-major axis in Unreal units (half the longest diameter of the ellipse) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Planet|Orbit")
	double SemiMajorAxis;

	/** Orbital eccentricity (0 = circle, 0.99 = highly elliptical) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Planet|Orbit", meta = (ClampMin = "0.0", ClampMax = "0.99"))
	double Eccentricity;

	/** Orbital period in Earth days (how long it takes to complete one orbit) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Planet|Orbit")
	double OrbitalPeriodDays;

	/** Orbital inclination in degrees (tilt relative to reference plane) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Planet|Orbit")
	double Inclination;

	/** Longitude of ascending node in degrees */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Planet|Orbit")
	double LongitudeOfAscendingNode;

	/** Argument of periapsis in degrees */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Planet|Orbit")
	double ArgumentOfPeriapsis;

	/** Current mean anomaly in degrees (position in orbit at time zero) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Planet|Orbit")
	double MeanAnomalyAtEpoch;

	/** Time multiplier for orbit speed (1.0 = real-time, higher = faster orbits) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Planet|Orbit")
	double TimeMultiplier;

	/** Center point of the orbit (typically the Sun's position) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Planet|Orbit")
	FVector OrbitCenter;

	/** Whether to show debug orbit visualization */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Planet|Debug")
	bool bShowOrbitPath;

	/** Planet diameter in kilometers (for display purposes) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Planet|Info")
	double DiameterKm;

	/** Planet mass in Earth masses (for display purposes) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Planet|Info")
	double MassEarthMasses;

	/** Whether this planet has a moon system */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Planet|Info")
	bool bHasMoons;

	/** Rotation period in Earth days (length of day on this planet) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Planet|Rotation")
	double RotationPeriodDays;

	/** Enable axial rotation of the planet */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Planet|Rotation")
	bool bEnableRotation;

	/** Blueprint event called when orbit position changes */
	UFUNCTION(BlueprintImplementableEvent, Category = "Planet|Events")
	void OnOrbitPositionUpdated(FVector NewPosition);

	/** Get current position in orbit */
	UFUNCTION(BlueprintCallable, Category = "Planet|Orbit")
	FVector GetOrbitPosition() const;

	/** Get distance from orbit center */
	UFUNCTION(BlueprintCallable, Category = "Planet|Orbit")
	double GetDistanceFromCenter() const;

	/** Set time multiplier at runtime */
	UFUNCTION(BlueprintCallable, Category = "Planet|Orbit")
	void SetTimeMultiplier(double NewMultiplier);

	/** Teleport to a specific position in orbit (0.0 = perihelion, 0.5 = aphelion) */
	UFUNCTION(BlueprintCallable, Category = "Planet|Orbit")
	void SetOrbitPosition(double NormalizedPosition);

private:
	/** Current time elapsed in the simulation */
	double ElapsedTime;

	/** Calculate position in elliptical orbit based on mean anomaly */
	FVector CalculateOrbitPosition(double MeanAnomaly) const;

	/** Solve Kepler's equation to get eccentric anomaly from mean anomaly */
	double SolveKeplersEquation(double MeanAnomaly) const;

	/** Draw debug orbit visualization */
	void DrawOrbitPath() const;

	/** Update axial rotation */
	void UpdateRotation(float DeltaTime);
};
