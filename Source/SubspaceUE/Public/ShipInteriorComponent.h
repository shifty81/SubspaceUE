// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShipInteriorComponent.generated.h"

/**
 * Type of interior cell/room
 */
UENUM(BlueprintType)
enum class EInteriorCellType : uint8
{
	Cockpit UMETA(DisplayName = "Cockpit/Bridge"),
	CrewQuarters UMETA(DisplayName = "Crew Quarters"),
	CargoBay UMETA(DisplayName = "Cargo Bay"),
	EngineRoom UMETA(DisplayName = "Engine Room"),
	MedBay UMETA(DisplayName = "Medical Bay"),
	Armory UMETA(DisplayName = "Armory"),
	Laboratory UMETA(DisplayName = "Laboratory"),
	Recreation UMETA(DisplayName = "Recreation"),
	Corridor UMETA(DisplayName = "Corridor"),
	Airlock UMETA(DisplayName = "Airlock")
};

/**
 * Type of interior object/furniture
 */
UENUM(BlueprintType)
enum class EInteriorObjectType : uint8
{
	Terminal UMETA(DisplayName = "Computer Terminal"),
	Chair UMETA(DisplayName = "Chair/Seat"),
	Storage UMETA(DisplayName = "Storage Container"),
	Bed UMETA(DisplayName = "Bed"),
	Locker UMETA(DisplayName = "Locker"),
	Crate UMETA(DisplayName = "Cargo Crate"),
	Workbench UMETA(DisplayName = "Workbench"),
	PowerNode UMETA(DisplayName = "Power Node"),
	Console UMETA(DisplayName = "Control Console"),
	Table UMETA(DisplayName = "Table"),
	Lamp UMETA(DisplayName = "Light Fixture"),
	Door UMETA(DisplayName = "Door")
};

/**
 * Interior object placement data
 */
USTRUCT(BlueprintType)
struct FInteriorObject
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interior Object")
	EInteriorObjectType Type = EInteriorObjectType::Chair;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interior Object")
	FVector Position = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interior Object")
	FRotator Rotation = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interior Object")
	FVector Size = FVector(100.0f, 100.0f, 100.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interior Object")
	bool bIsInteractive = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interior Object")
	FString InteractionText = TEXT("");
};

/**
 * Interior cell/room data
 */
USTRUCT(BlueprintType)
struct FInteriorCell
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interior Cell")
	EInteriorCellType Type = EInteriorCellType::Corridor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interior Cell")
	FString CellName = TEXT("Unnamed Room");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interior Cell")
	FVector MinBounds = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interior Cell")
	FVector MaxBounds = FVector(400.0f, 400.0f, 300.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interior Cell")
	TArray<FInteriorObject> PlacedObjects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interior Cell")
	TArray<FVector> DoorPositions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interior Cell")
	bool bHasGravity = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interior Cell")
	bool bHasAtmosphere = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interior Cell")
	int32 CrewCapacity = 0;
};

/**
 * Component that manages ship interior spaces
 * Defines rooms, furniture, and interior objects for X4-style ship interiors
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SUBSPACEUE_API UShipInteriorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UShipInteriorComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** Array of interior cells/rooms */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interior")
	TArray<FInteriorCell> Cells;

	/** Whether interior is accessible (crew can walk inside) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interior")
	bool bInteriorAccessible;

	/** Add an interior cell */
	UFUNCTION(BlueprintCallable, Category = "Interior")
	void AddCell(const FInteriorCell& Cell);

	/** Get cell by type */
	UFUNCTION(BlueprintCallable, Category = "Interior")
	bool GetCellByType(EInteriorCellType Type, FInteriorCell& OutCell) const;

	/** Get all cells of a specific type */
	UFUNCTION(BlueprintCallable, Category = "Interior")
	TArray<FInteriorCell> GetCellsByType(EInteriorCellType Type) const;

	/** Get total crew capacity */
	UFUNCTION(BlueprintCallable, Category = "Interior")
	int32 GetTotalCrewCapacity() const;

	/** Generate standard Ulysses interior (4 rooms) */
	UFUNCTION(BlueprintCallable, Category = "Interior")
	void GenerateUlyssesInterior();

protected:
	/** Generate cockpit/bridge room */
	FInteriorCell GenerateCockpit();

	/** Generate crew quarters */
	FInteriorCell GenerateCrewQuarters();

	/** Generate cargo bay */
	FInteriorCell GenerateCargoBay();

	/** Generate engine room */
	FInteriorCell GenerateEngineRoom();
};
