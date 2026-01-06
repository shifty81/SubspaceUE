// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShipInteriorComponent.h"

UShipInteriorComponent::UShipInteriorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bInteriorAccessible = true;
}

void UShipInteriorComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UShipInteriorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UShipInteriorComponent::AddCell(const FInteriorCell& Cell)
{
	Cells.Add(Cell);
}

bool UShipInteriorComponent::GetCellByType(EInteriorCellType Type, FInteriorCell& OutCell) const
{
	for (const FInteriorCell& Cell : Cells)
	{
		if (Cell.Type == Type)
		{
			OutCell = Cell;
			return true;
		}
	}
	return false;
}

TArray<FInteriorCell> UShipInteriorComponent::GetCellsByType(EInteriorCellType Type) const
{
	TArray<FInteriorCell> Result;
	for (const FInteriorCell& Cell : Cells)
	{
		if (Cell.Type == Type)
		{
			Result.Add(Cell);
		}
	}
	return Result;
}

int32 UShipInteriorComponent::GetTotalCrewCapacity() const
{
	int32 Total = 0;
	for (const FInteriorCell& Cell : Cells)
	{
		Total += Cell.CrewCapacity;
	}
	return Total;
}

void UShipInteriorComponent::GenerateUlyssesInterior()
{
	Cells.Empty();

	// Generate 4 standard Ulysses rooms
	AddCell(GenerateCockpit());
	AddCell(GenerateCrewQuarters());
	AddCell(GenerateCargoBay());
	AddCell(GenerateEngineRoom());

	UE_LOG(LogTemp, Log, TEXT("Generated Ulysses interior: %d rooms, %d crew capacity"), 
		Cells.Num(), GetTotalCrewCapacity());
}

FInteriorCell UShipInteriorComponent::GenerateCockpit()
{
	FInteriorCell Cell;
	Cell.Type = EInteriorCellType::Cockpit;
	Cell.CellName = TEXT("Bridge");
	Cell.MinBounds = FVector(800.0f, -300.0f, 0.0f);
	Cell.MaxBounds = FVector(1200.0f, 300.0f, 300.0f);
	Cell.bHasGravity = true;
	Cell.bHasAtmosphere = true;
	Cell.CrewCapacity = 3;

	// Add captain's chair
	FInteriorObject CaptainChair;
	CaptainChair.Type = EInteriorObjectType::Chair;
	CaptainChair.Position = FVector(1000.0f, 0.0f, 50.0f);
	CaptainChair.Rotation = FRotator(0.0f, 0.0f, 0.0f);
	CaptainChair.Size = FVector(100.0f, 100.0f, 150.0f);
	CaptainChair.bIsInteractive = true;
	CaptainChair.InteractionText = TEXT("Sit in Captain's Chair");
	Cell.PlacedObjects.Add(CaptainChair);

	// Add helm console
	FInteriorObject HelmConsole;
	HelmConsole.Type = EInteriorObjectType::Console;
	HelmConsole.Position = FVector(1150.0f, 0.0f, 100.0f);
	HelmConsole.Rotation = FRotator(0.0f, 180.0f, 0.0f);
	HelmConsole.Size = FVector(150.0f, 80.0f, 120.0f);
	HelmConsole.bIsInteractive = true;
	HelmConsole.InteractionText = TEXT("Access Helm Controls");
	Cell.PlacedObjects.Add(HelmConsole);

	// Add navigation terminal
	FInteriorObject NavTerminal;
	NavTerminal.Type = EInteriorObjectType::Terminal;
	NavTerminal.Position = FVector(900.0f, -200.0f, 100.0f);
	NavTerminal.Rotation = FRotator(0.0f, 90.0f, 0.0f);
	NavTerminal.Size = FVector(80.0f, 50.0f, 100.0f);
	NavTerminal.bIsInteractive = true;
	NavTerminal.InteractionText = TEXT("Access Navigation System");
	Cell.PlacedObjects.Add(NavTerminal);

	// Add tactical terminal
	FInteriorObject TacTerminal;
	TacTerminal.Type = EInteriorObjectType::Terminal;
	TacTerminal.Position = FVector(900.0f, 200.0f, 100.0f);
	TacTerminal.Rotation = FRotator(0.0f, -90.0f, 0.0f);
	TacTerminal.Size = FVector(80.0f, 50.0f, 100.0f);
	TacTerminal.bIsInteractive = true;
	TacTerminal.InteractionText = TEXT("Access Tactical Systems");
	Cell.PlacedObjects.Add(TacTerminal);

	// Door to corridor
	Cell.DoorPositions.Add(FVector(800.0f, 0.0f, 100.0f));

	return Cell;
}

FInteriorCell UShipInteriorComponent::GenerateCrewQuarters()
{
	FInteriorCell Cell;
	Cell.Type = EInteriorCellType::CrewQuarters;
	Cell.CellName = TEXT("Crew Quarters");
	Cell.MinBounds = FVector(200.0f, -300.0f, 0.0f);
	Cell.MaxBounds = FVector(600.0f, 300.0f, 300.0f);
	Cell.bHasGravity = true;
	Cell.bHasAtmosphere = true;
	Cell.CrewCapacity = 4;

	// Add beds (4 crew bunks)
	for (int32 i = 0; i < 4; ++i)
	{
		FInteriorObject Bed;
		Bed.Type = EInteriorObjectType::Bed;
		Bed.Position = FVector(250.0f + (i / 2) * 200.0f, -200.0f + (i % 2) * 400.0f, 80.0f);
		Bed.Rotation = FRotator(0.0f, (i % 2 == 0) ? 90.0f : -90.0f, 0.0f);
		Bed.Size = FVector(200.0f, 100.0f, 100.0f);
		Bed.bIsInteractive = true;
		Bed.InteractionText = TEXT("Rest");
		Cell.PlacedObjects.Add(Bed);
	}

	// Add lockers
	for (int32 i = 0; i < 4; ++i)
	{
		FInteriorObject Locker;
		Locker.Type = EInteriorObjectType::Locker;
		Locker.Position = FVector(550.0f, -225.0f + i * 150.0f, 100.0f);
		Locker.Rotation = FRotator(0.0f, -90.0f, 0.0f);
		Locker.Size = FVector(80.0f, 60.0f, 200.0f);
		Locker.bIsInteractive = true;
		Locker.InteractionText = TEXT("Open Locker");
		Cell.PlacedObjects.Add(Locker);
	}

	// Add table
	FInteriorObject Table;
	Table.Type = EInteriorObjectType::Table;
	Table.Position = FVector(400.0f, 0.0f, 80.0f);
	Table.Size = FVector(150.0f, 200.0f, 80.0f);
	Cell.PlacedObjects.Add(Table);

	// Door to corridor
	Cell.DoorPositions.Add(FVector(600.0f, 0.0f, 100.0f));

	return Cell;
}

FInteriorCell UShipInteriorComponent::GenerateCargoBay()
{
	FInteriorCell Cell;
	Cell.Type = EInteriorCellType::CargoBay;
	Cell.CellName = TEXT("Cargo Bay");
	Cell.MinBounds = FVector(-200.0f, -400.0f, 0.0f);
	Cell.MaxBounds = FVector(200.0f, 400.0f, 400.0f);
	Cell.bHasGravity = true;
	Cell.bHasAtmosphere = true;
	Cell.CrewCapacity = 0;

	// Add cargo crates (6 crates in a grid)
	for (int32 x = 0; x < 2; ++x)
	{
		for (int32 y = 0; y < 3; ++y)
		{
			FInteriorObject Crate;
			Crate.Type = EInteriorObjectType::Crate;
			Crate.Position = FVector(-100.0f + x * 200.0f, -300.0f + y * 300.0f, 100.0f);
			Crate.Size = FVector(150.0f, 150.0f, 150.0f);
			Crate.bIsInteractive = true;
			Crate.InteractionText = TEXT("Access Cargo");
			Cell.PlacedObjects.Add(Crate);
		}
	}

	// Add storage containers on walls
	for (int32 i = 0; i < 4; ++i)
	{
		FInteriorObject Storage;
		Storage.Type = EInteriorObjectType::Storage;
		Storage.Position = FVector(180.0f, -350.0f + i * 233.0f, 200.0f);
		Storage.Rotation = FRotator(0.0f, -90.0f, 0.0f);
		Storage.Size = FVector(100.0f, 80.0f, 150.0f);
		Storage.bIsInteractive = true;
		Storage.InteractionText = TEXT("Open Storage");
		Cell.PlacedObjects.Add(Storage);
	}

	// Door to corridor
	Cell.DoorPositions.Add(FVector(200.0f, 0.0f, 100.0f));

	return Cell;
}

FInteriorCell UShipInteriorComponent::GenerateEngineRoom()
{
	FInteriorCell Cell;
	Cell.Type = EInteriorCellType::EngineRoom;
	Cell.CellName = TEXT("Engine Room");
	Cell.MinBounds = FVector(-600.0f, -300.0f, 0.0f);
	Cell.MaxBounds = FVector(-200.0f, 300.0f, 300.0f);
	Cell.bHasGravity = true;
	Cell.bHasAtmosphere = true;
	Cell.CrewCapacity = 2;

	// Add power nodes (3 major systems)
	for (int32 i = 0; i < 3; ++i)
	{
		FInteriorObject PowerNode;
		PowerNode.Type = EInteriorObjectType::PowerNode;
		PowerNode.Position = FVector(-500.0f, -200.0f + i * 200.0f, 150.0f);
		PowerNode.Size = FVector(100.0f, 100.0f, 200.0f);
		PowerNode.bIsInteractive = true;
		PowerNode.InteractionText = TEXT("Access Power System");
		Cell.PlacedObjects.Add(PowerNode);
	}

	// Add engineering terminal
	FInteriorObject EngTerminal;
	EngTerminal.Type = EInteriorObjectType::Terminal;
	EngTerminal.Position = FVector(-250.0f, 0.0f, 100.0f);
	EngTerminal.Rotation = FRotator(0.0f, 180.0f, 0.0f);
	EngTerminal.Size = FVector(80.0f, 60.0f, 120.0f);
	EngTerminal.bIsInteractive = true;
	EngTerminal.InteractionText = TEXT("Access Engineering Controls");
	Cell.PlacedObjects.Add(EngTerminal);

	// Add workbench
	FInteriorObject Workbench;
	Workbench.Type = EInteriorObjectType::Workbench;
	Workbench.Position = FVector(-300.0f, 250.0f, 100.0f);
	Workbench.Rotation = FRotator(0.0f, 180.0f, 0.0f);
	Workbench.Size = FVector(150.0f, 100.0f, 100.0f);
	Workbench.bIsInteractive = true;
	Workbench.InteractionText = TEXT("Use Workbench");
	Cell.PlacedObjects.Add(Workbench);

	// Door to corridor
	Cell.DoorPositions.Add(FVector(-200.0f, 0.0f, 100.0f));

	return Cell;
}
