// Copyright Epic Games, Inc. All Rights Reserved.

#include "PlanetActor.h"
#include "DrawDebugHelpers.h"

APlanetActor::APlanetActor()
{
	PrimaryActorTick.bCanEverTick = true;

	// Default values
	PlanetName = TEXT("Unknown Planet");
	SemiMajorAxis = 100000.0;  // 1km default
	Eccentricity = 0.0;
	OrbitalPeriodDays = 365.0;
	Inclination = 0.0;
	LongitudeOfAscendingNode = 0.0;
	ArgumentOfPeriapsis = 0.0;
	MeanAnomalyAtEpoch = 0.0;
	TimeMultiplier = 1000.0;  // Speed up orbits by default for testing
	OrbitCenter = FVector::ZeroVector;
	bShowOrbitPath = true;
	DiameterKm = 12742.0;  // Earth size default
	MassEarthMasses = 1.0;
	bHasMoons = false;
	RotationPeriodDays = 1.0;
	bEnableRotation = true;
	ElapsedTime = 0.0;
}

void APlanetActor::BeginPlay()
{
	Super::BeginPlay();

	// Initialize position based on epoch
	FVector InitialPosition = CalculateOrbitPosition(FMath::DegreesToRadians(MeanAnomalyAtEpoch));
	SetActorLocation(InitialPosition);
}

void APlanetActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Update elapsed time with multiplier
	ElapsedTime += DeltaTime * TimeMultiplier;

	// Calculate mean anomaly (angle traveled in orbit)
	// Mean motion (radians per second) = 2π / period
	double OrbitalPeriodSeconds = OrbitalPeriodDays * 86400.0;  // Convert days to seconds
	double MeanMotion = (2.0 * PI) / OrbitalPeriodSeconds;
	double CurrentMeanAnomaly = FMath::DegreesToRadians(MeanAnomalyAtEpoch) + (MeanMotion * ElapsedTime);

	// Keep mean anomaly in [0, 2π] range
	CurrentMeanAnomaly = FMath::Fmod(CurrentMeanAnomaly, 2.0 * PI);
	if (CurrentMeanAnomaly < 0.0)
	{
		CurrentMeanAnomaly += 2.0 * PI;
	}

	// Calculate new position
	FVector NewPosition = CalculateOrbitPosition(CurrentMeanAnomaly);
	SetActorLocation(NewPosition);

	// Update rotation if enabled
	if (bEnableRotation)
	{
		UpdateRotation(DeltaTime);
	}

	// Draw orbit path if enabled
	if (bShowOrbitPath)
	{
		DrawOrbitPath();
	}

	// Trigger blueprint event
	OnOrbitPositionUpdated(NewPosition);
}

FVector APlanetActor::CalculateOrbitPosition(double MeanAnomaly) const
{
	// Solve Kepler's equation to get eccentric anomaly
	double EccentricAnomaly = SolveKeplersEquation(MeanAnomaly);

	// Calculate position in orbital plane
	double CosE = FMath::Cos(EccentricAnomaly);
	double SinE = FMath::Sin(EccentricAnomaly);

	// Semi-minor axis
	double SemiMinorAxis = SemiMajorAxis * FMath::Sqrt(1.0 - Eccentricity * Eccentricity);

	// Position in orbital plane (2D)
	double X = SemiMajorAxis * (CosE - Eccentricity);
	double Y = SemiMinorAxis * SinE;

	// Convert angles to radians
	double Inc = FMath::DegreesToRadians(Inclination);
	double Lan = FMath::DegreesToRadians(LongitudeOfAscendingNode);
	double ArgP = FMath::DegreesToRadians(ArgumentOfPeriapsis);

	// Rotation matrices to transform from orbital plane to world space
	// Apply argument of periapsis rotation
	double X1 = X * FMath::Cos(ArgP) - Y * FMath::Sin(ArgP);
	double Y1 = X * FMath::Sin(ArgP) + Y * FMath::Cos(ArgP);

	// Apply inclination rotation
	double X2 = X1;
	double Y2 = Y1 * FMath::Cos(Inc);
	double Z2 = Y1 * FMath::Sin(Inc);

	// Apply longitude of ascending node rotation
	double X3 = X2 * FMath::Cos(Lan) - Y2 * FMath::Sin(Lan);
	double Y3 = X2 * FMath::Sin(Lan) + Y2 * FMath::Cos(Lan);
	double Z3 = Z2;

	// Offset from orbit center
	FVector OrbitPosition(X3, Y3, Z3);
	return OrbitCenter + OrbitPosition;
}

double APlanetActor::SolveKeplersEquation(double MeanAnomaly) const
{
	// Solve Kepler's equation: M = E - e*sin(E)
	// Using Newton-Raphson iteration
	double EccentricAnomaly = MeanAnomaly;  // Initial guess
	const int MaxIterations = 10;
	const double Tolerance = 1e-8;

	for (int i = 0; i < MaxIterations; ++i)
	{
		double F = EccentricAnomaly - Eccentricity * FMath::Sin(EccentricAnomaly) - MeanAnomaly;
		double FPrime = 1.0 - Eccentricity * FMath::Cos(EccentricAnomaly);

		double Delta = F / FPrime;
		EccentricAnomaly -= Delta;

		if (FMath::Abs(Delta) < Tolerance)
		{
			break;
		}
	}

	return EccentricAnomaly;
}

void APlanetActor::DrawOrbitPath() const
{
	if (GetWorld() == nullptr)
	{
		return;
	}

	// Draw orbit as a series of line segments
	const int NumSegments = 100;
	FVector PreviousPoint;

	for (int i = 0; i <= NumSegments; ++i)
	{
		double Angle = (2.0 * PI * i) / NumSegments;
		FVector Point = CalculateOrbitPosition(Angle);

		if (i > 0)
		{
			DrawDebugLine(
				GetWorld(),
				PreviousPoint,
				Point,
				FColor::Cyan,
				false,  // bPersistentLines (false = drawn each frame)
				-1.0f,  // Lifetime (-1 = infinite, redrawn each frame)
				0,      // Depth priority
				50.0f   // Thickness
			);
		}

		PreviousPoint = Point;
	}

	// Draw a marker at perihelion (closest point)
	FVector Perihelion = CalculateOrbitPosition(0.0);
	DrawDebugSphere(
		GetWorld(),
		Perihelion,
		5000.0f,
		12,
		FColor::Yellow,
		false,
		-1.0f
	);

	// Draw a marker at aphelion (farthest point)
	FVector Aphelion = CalculateOrbitPosition(PI);
	DrawDebugSphere(
		GetWorld(),
		Aphelion,
		5000.0f,
		12,
		FColor::Red,
		false,
		-1.0f
	);
}

void APlanetActor::UpdateRotation(float DeltaTime)
{
	if (RotationPeriodDays <= 0.0)
	{
		return;
	}

	// Calculate rotation speed (degrees per second)
	double RotationPeriodSeconds = RotationPeriodDays * 86400.0;
	double DegreesPerSecond = 360.0 / RotationPeriodSeconds;

	// Apply time multiplier
	DegreesPerSecond *= TimeMultiplier;

	// Rotate around Z axis (assuming Z is up)
	FRotator CurrentRotation = GetActorRotation();
	CurrentRotation.Yaw += DegreesPerSecond * DeltaTime;
	SetActorRotation(CurrentRotation);
}

FVector APlanetActor::GetOrbitPosition() const
{
	return GetActorLocation();
}

double APlanetActor::GetDistanceFromCenter() const
{
	return FVector::Dist(GetActorLocation(), OrbitCenter);
}

void APlanetActor::SetTimeMultiplier(double NewMultiplier)
{
	TimeMultiplier = FMath::Max(0.0, NewMultiplier);
}

void APlanetActor::SetOrbitPosition(double NormalizedPosition)
{
	// NormalizedPosition: 0.0 = perihelion, 0.5 = aphelion, 1.0 = back to perihelion
	double MeanAnomaly = NormalizedPosition * 2.0 * PI;
	FVector NewPosition = CalculateOrbitPosition(MeanAnomaly);
	SetActorLocation(NewPosition);

	// Update elapsed time to match this position
	double OrbitalPeriodSeconds = OrbitalPeriodDays * 86400.0;
	ElapsedTime = (MeanAnomaly - FMath::DegreesToRadians(MeanAnomalyAtEpoch)) * OrbitalPeriodSeconds / (2.0 * PI);
}
