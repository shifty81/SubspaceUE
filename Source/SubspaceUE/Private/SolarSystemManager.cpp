// Copyright Epic Games, Inc. All Rights Reserved.

#include "SolarSystemManager.h"
#include "Engine/World.h"
#include "Engine/StaticMeshActor.h"
#include "Components/StaticMeshComponent.h"

// Real-world astronomical constants
static constexpr double AU_TO_KM = 149597870.7;  // 1 AU in kilometers
static constexpr double CM_PER_KM = 100000.0;     // Centimeters per kilometer

ASolarSystemManager::ASolarSystemManager()
{
	PrimaryActorTick.bCanEverTick = true;

	// Default scale factors
	// For gameplay: distances scaled down dramatically, but planets kept visible
	DistanceScale = 0.00001;  // 1:100,000 scale for distances
	PlanetSizeScale = 50.0;   // Planets 50x larger than realistic for visibility
	GlobalTimeMultiplier = 10000.0;  // Speed up time 10,000x so we can see orbits
	
	bAutoSpawnPlanets = true;
	bSpawnSun = true;
	bOrbitsPaused = false;
	StoredTimeMultiplier = GlobalTimeMultiplier;

	// Default planet actor class
	PlanetActorClass = APlanetActor::StaticClass();
}

void ASolarSystemManager::BeginPlay()
{
	Super::BeginPlay();

	if (bAutoSpawnPlanets)
	{
		if (bSpawnSun)
		{
			SpawnSunActor();
		}
		SpawnAllPlanets();
	}
}

void ASolarSystemManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASolarSystemManager::SpawnSunActor()
{
	if (GetWorld() == nullptr)
	{
		return;
	}

	// Spawn a static mesh actor for the Sun at the origin
	FActorSpawnParameters SpawnParams;
	SpawnParams.Name = FName(TEXT("Sun"));
	SpawnParams.Owner = this;

	Sun = GetWorld()->SpawnActor<AStaticMeshActor>(
		AStaticMeshActor::StaticClass(),
		GetActorLocation(),
		FRotator::ZeroRotator,
		SpawnParams
	);

	if (Sun)
	{
		// Sun diameter: 1,392,700 km
		double SunDiameterKm = 1392700.0;
		double SunRadiusUU = KmToUnrealUnits(SunDiameterKm / 2.0);
		
		// Scale the sun
		Sun->SetActorScale3D(FVector(SunRadiusUU / 50.0));  // Assuming default sphere radius is 50 units
		
		UE_LOG(LogTemp, Log, TEXT("Solar System: Spawned Sun at origin with radius %.2f units"), SunRadiusUU);
	}
}

void ASolarSystemManager::SpawnAllPlanets()
{
	UE_LOG(LogTemp, Log, TEXT("Solar System: Spawning all planets..."));

	TArray<FPlanetData> PlanetaryData = GetPlanetaryData();

	for (const FPlanetData& Data : PlanetaryData)
	{
		APlanetActor* Planet = CreatePlanet(
			Data.Name,
			Data.SemiMajorAxisAU,
			Data.Eccentricity,
			Data.OrbitalPeriodDays,
			Data.InclinationDeg,
			Data.LongitudeAscendingNodeDeg,
			Data.ArgumentPeriapsisDeg,
			Data.MeanAnomalyAtEpochDeg,
			Data.DiameterKm,
			Data.MassEarthMasses,
			Data.RotationPeriodDays,
			Data.bHasMoons
		);

		if (Planet)
		{
			Planets.Add(Planet);
			UE_LOG(LogTemp, Log, TEXT("Solar System: Spawned %s at distance %.2f units"), 
				*Data.Name, Planet->SemiMajorAxis);
		}
	}

	UE_LOG(LogTemp, Log, TEXT("Solar System: Spawned %d planets"), Planets.Num());
}

APlanetActor* ASolarSystemManager::SpawnPlanet(FString PlanetName)
{
	TArray<FPlanetData> PlanetaryData = GetPlanetaryData();
	
	for (const FPlanetData& Data : PlanetaryData)
	{
		if (Data.Name.Equals(PlanetName, ESearchCase::IgnoreCase))
		{
			return CreatePlanet(
				Data.Name,
				Data.SemiMajorAxisAU,
				Data.Eccentricity,
				Data.OrbitalPeriodDays,
				Data.InclinationDeg,
				Data.LongitudeAscendingNodeDeg,
				Data.ArgumentPeriapsisDeg,
				Data.MeanAnomalyAtEpochDeg,
				Data.DiameterKm,
				Data.MassEarthMasses,
				Data.RotationPeriodDays,
				Data.bHasMoons
			);
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Solar System: Planet '%s' not found in database"), *PlanetName);
	return nullptr;
}

APlanetActor* ASolarSystemManager::CreatePlanet(
	const FString& Name,
	double SemiMajorAxisAU,
	double Eccentricity,
	double OrbitalPeriodDays,
	double InclinationDeg,
	double LongitudeAscendingNodeDeg,
	double ArgumentPeriapsisDeg,
	double MeanAnomalyDeg,
	double DiameterKm,
	double MassEarthMasses,
	double RotationPeriodDays,
	bool bHasMoons)
{
	if (GetWorld() == nullptr || PlanetActorClass == nullptr)
	{
		return nullptr;
	}

	// Spawn the planet actor
	FActorSpawnParameters SpawnParams;
	SpawnParams.Name = FName(*Name);
	SpawnParams.Owner = this;

	FVector SpawnLocation = GetActorLocation();  // Will be repositioned by orbit calculation
	
	APlanetActor* Planet = GetWorld()->SpawnActor<APlanetActor>(
		PlanetActorClass,
		SpawnLocation,
		FRotator::ZeroRotator,
		SpawnParams
	);

	if (Planet)
	{
		// Set planet properties
		Planet->PlanetName = Name;
		Planet->SemiMajorAxis = AUToUnrealUnits(SemiMajorAxisAU);
		Planet->Eccentricity = Eccentricity;
		Planet->OrbitalPeriodDays = OrbitalPeriodDays;
		Planet->Inclination = InclinationDeg;
		Planet->LongitudeOfAscendingNode = LongitudeAscendingNodeDeg;
		Planet->ArgumentOfPeriapsis = ArgumentPeriapsisDeg;
		Planet->MeanAnomalyAtEpoch = MeanAnomalyDeg;
		Planet->TimeMultiplier = GlobalTimeMultiplier;
		Planet->OrbitCenter = GetActorLocation();
		Planet->DiameterKm = DiameterKm;
		Planet->MassEarthMasses = MassEarthMasses;
		Planet->bHasMoons = bHasMoons;
		Planet->RotationPeriodDays = RotationPeriodDays;

		// Scale the planet mesh based on diameter
		double PlanetRadiusUU = KmToUnrealUnits(DiameterKm / 2.0);
		Planet->SetActorScale3D(FVector(PlanetRadiusUU / 50.0));  // Assuming default sphere radius is 50 units
	}

	return Planet;
}

APlanetActor* ASolarSystemManager::GetPlanetByName(FString PlanetName) const
{
	for (APlanetActor* Planet : Planets)
	{
		if (Planet && Planet->PlanetName.Equals(PlanetName, ESearchCase::IgnoreCase))
		{
			return Planet;
		}
	}
	return nullptr;
}

void ASolarSystemManager::SetGlobalTimeMultiplier(double NewMultiplier)
{
	GlobalTimeMultiplier = FMath::Max(0.0, NewMultiplier);
	
	// Update all planets
	for (APlanetActor* Planet : Planets)
	{
		if (Planet)
		{
			Planet->SetTimeMultiplier(GlobalTimeMultiplier);
		}
	}

	if (!bOrbitsPaused)
	{
		StoredTimeMultiplier = GlobalTimeMultiplier;
	}
}

void ASolarSystemManager::SetOrbitsPaused(bool bPaused)
{
	if (bPaused == bOrbitsPaused)
	{
		return;
	}

	bOrbitsPaused = bPaused;

	if (bPaused)
	{
		// Store current multiplier and set to 0
		StoredTimeMultiplier = GlobalTimeMultiplier;
		SetGlobalTimeMultiplier(0.0);
	}
	else
	{
		// Restore previous multiplier
		SetGlobalTimeMultiplier(StoredTimeMultiplier);
	}
}

FVector ASolarSystemManager::GetSunPosition() const
{
	return GetActorLocation();
}

void ASolarSystemManager::SetAllPlanetsOrbitPosition(double NormalizedPosition)
{
	for (APlanetActor* Planet : Planets)
	{
		if (Planet)
		{
			Planet->SetOrbitPosition(NormalizedPosition);
		}
	}
}

double ASolarSystemManager::AUToUnrealUnits(double AU) const
{
	// 1 AU = 149,597,870.7 km
	// 1 km = 100,000 cm (Unreal units)
	// Apply distance scale factor
	return AU * AU_TO_KM * CM_PER_KM * DistanceScale;
}

double ASolarSystemManager::KmToUnrealUnits(double Km) const
{
	// 1 km = 100,000 cm (Unreal units)
	// Apply size scale factor for planets
	return Km * CM_PER_KM * PlanetSizeScale;
}

TArray<ASolarSystemManager::FPlanetData> ASolarSystemManager::GetPlanetaryData() const
{
	// Real-world orbital data for all 8 planets
	// Data sourced from NASA/JPL Horizons system (J2000 epoch)
	TArray<FPlanetData> Data;

	// Mercury
	Data.Add({
		TEXT("Mercury"),
		0.38709893,      // Semi-major axis (AU)
		0.20563069,      // Eccentricity
		87.969,          // Orbital period (days)
		7.00487,         // Inclination (degrees)
		48.33167,        // Longitude of ascending node
		77.45645,        // Argument of periapsis
		252.25084,       // Mean anomaly at epoch
		4879.4,          // Diameter (km)
		0.0553,          // Mass (Earth masses)
		58.646,          // Rotation period (days)
		false            // Has moons
	});

	// Venus
	Data.Add({
		TEXT("Venus"),
		0.72333199,
		0.00677323,
		224.701,
		3.39471,
		76.68069,
		131.53298,
		181.97973,
		12103.6,
		0.815,
		243.018,         // Retrograde rotation
		false
	});

	// Earth
	Data.Add({
		TEXT("Earth"),
		1.00000011,
		0.01671022,
		365.256,
		0.00005,
		-11.26064,
		102.94719,
		100.46435,
		12742.0,
		1.0,
		1.0,
		true             // Has Moon
	});

	// Mars
	Data.Add({
		TEXT("Mars"),
		1.52366231,
		0.09341233,
		686.980,
		1.85061,
		49.57854,
		336.04084,
		355.45332,
		6779.0,
		0.107,
		1.026,
		true             // Has 2 moons
	});

	// Jupiter
	Data.Add({
		TEXT("Jupiter"),
		5.20336301,
		0.04839266,
		4332.589,
		1.30530,
		100.55615,
		14.75385,
		34.40438,
		139820.0,
		317.8,
		0.414,
		true             // Has 79+ moons
	});

	// Saturn
	Data.Add({
		TEXT("Saturn"),
		9.53707032,
		0.05415060,
		10759.22,
		2.48446,
		113.71504,
		92.43194,
		49.94432,
		116460.0,
		95.2,
		0.444,
		true             // Has 82+ moons
	});

	// Uranus
	Data.Add({
		TEXT("Uranus"),
		19.19126393,
		0.04716771,
		30688.5,
		0.76986,
		74.22988,
		170.96424,
		313.23218,
		50724.0,
		14.5,
		0.718,           // Retrograde rotation
		true             // Has 27 moons
	});

	// Neptune
	Data.Add({
		TEXT("Neptune"),
		30.06896348,
		0.00858587,
		60182.0,
		1.76917,
		131.72169,
		44.97135,
		304.88003,
		49244.0,
		17.1,
		0.671,
		true             // Has 14 moons
	});

	return Data;
}
