// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlanetActor.h"
#include "SolarSystemManager.generated.h"

/**
 * Manages the entire solar system, spawning planets with real-world orbital parameters
 * Supports different scale modes for gameplay vs realism
 */
UCLASS()
class SUBSPACEUE_API ASolarSystemManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ASolarSystemManager();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	/** Scale factor for distances (1.0 = real scale, 0.0001 = 1/10000 scale for gameplay) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Solar System|Scale")
	double DistanceScale;

	/** Scale factor for planet sizes (independent of orbital distances) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Solar System|Scale")
	double PlanetSizeScale;

	/** Time multiplier for all orbits (affects simulation speed) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Solar System|Time")
	double GlobalTimeMultiplier;

	/** Whether to automatically spawn all planets on BeginPlay */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Solar System|Setup")
	bool bAutoSpawnPlanets;

	/** Whether to spawn the Sun actor */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Solar System|Setup")
	bool bSpawnSun;

	/** Class to use for planet actors (allows for custom planet classes) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Solar System|Setup")
	TSubclassOf<APlanetActor> PlanetActorClass;

	/** Reference to the Sun actor */
	UPROPERTY(BlueprintReadOnly, Category = "Solar System|Celestial Bodies")
	AActor* Sun;

	/** References to all spawned planets */
	UPROPERTY(BlueprintReadOnly, Category = "Solar System|Celestial Bodies")
	TArray<APlanetActor*> Planets;

	/** Spawn all planets in the solar system */
	UFUNCTION(BlueprintCallable, Category = "Solar System")
	void SpawnAllPlanets();

	/** Spawn a specific planet by name */
	UFUNCTION(BlueprintCallable, Category = "Solar System")
	APlanetActor* SpawnPlanet(FString PlanetName);

	/** Get planet by name */
	UFUNCTION(BlueprintCallable, Category = "Solar System")
	APlanetActor* GetPlanetByName(FString PlanetName) const;

	/** Set time multiplier for all planets */
	UFUNCTION(BlueprintCallable, Category = "Solar System")
	void SetGlobalTimeMultiplier(double NewMultiplier);

	/** Pause/resume all planetary orbits */
	UFUNCTION(BlueprintCallable, Category = "Solar System")
	void SetOrbitsPaused(bool bPaused);

	/** Get the position of the Sun (orbit center) */
	UFUNCTION(BlueprintCallable, Category = "Solar System")
	FVector GetSunPosition() const;

	/** Teleport all planets to specific positions in their orbits */
	UFUNCTION(BlueprintCallable, Category = "Solar System")
	void SetAllPlanetsOrbitPosition(double NormalizedPosition);

private:
	/** Spawn the Sun at the center */
	void SpawnSunActor();

	/** Create planet with specific orbital parameters */
	APlanetActor* CreatePlanet(
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
		bool bHasMoons = false
	);

	/** Convert Astronomical Units to Unreal units with scale factor */
	double AUToUnrealUnits(double AU) const;

	/** Convert kilometers to Unreal units with scale factor */
	double KmToUnrealUnits(double Km) const;

	/** Real-world planetary data */
	struct FPlanetData
	{
		FString Name;
		double SemiMajorAxisAU;
		double Eccentricity;
		double OrbitalPeriodDays;
		double InclinationDeg;
		double LongitudeAscendingNodeDeg;
		double ArgumentPeriapsisDeg;
		double MeanAnomalyAtEpochDeg;
		double DiameterKm;
		double MassEarthMasses;
		double RotationPeriodDays;
		bool bHasMoons;
	};

	/** Get real-world data for all planets */
	TArray<FPlanetData> GetPlanetaryData() const;

	/** Whether orbits are currently paused */
	bool bOrbitsPaused;

	/** Stored time multiplier before pause */
	double StoredTimeMultiplier;
};
