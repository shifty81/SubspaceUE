// Copyright Epic Games, Inc. All Rights Reserved.

#include "VoxelComponent.h"
#include "Components/SceneComponent.h"

UVoxelComponent::UVoxelComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bUseGreedyMeshing = false;
	bNeedsRebuild = false;
}

void UVoxelComponent::BeginPlay()
{
	Super::BeginPlay();

	// Create procedural mesh component if not already created
	if (!ProceduralMesh)
	{
		ProceduralMesh = NewObject<UProceduralMeshComponent>(GetOwner(), TEXT("VoxelProceduralMesh"));
		ProceduralMesh->RegisterComponent();
		ProceduralMesh->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		ProceduralMesh->bUseAsyncCooking = true; // Enable async collision cooking for performance
	}

	// Initial mesh generation if we have blocks
	if (Blocks.Num() > 0)
	{
		RebuildMesh();
	}
}

void UVoxelComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Rebuild mesh if needed
	if (bNeedsRebuild)
	{
		RebuildMesh();
		bNeedsRebuild = false;
	}
}

void UVoxelComponent::AddBlock(const FVoxelBlock& Block)
{
	Blocks.Add(Block);
	MarkForRebuild();
}

bool UVoxelComponent::RemoveBlock(const FGuid& BlockId)
{
	for (int32 i = 0; i < Blocks.Num(); ++i)
	{
		if (Blocks[i].Id == BlockId)
		{
			Blocks.RemoveAt(i);
			MarkForRebuild();
			return true;
		}
	}
	return false;
}

bool UVoxelComponent::GetBlock(const FGuid& BlockId, FVoxelBlock& OutBlock) const
{
	for (const FVoxelBlock& Block : Blocks)
	{
		if (Block.Id == BlockId)
		{
			OutBlock = Block;
			return true;
		}
	}
	return false;
}

void UVoxelComponent::ClearBlocks()
{
	Blocks.Empty();
	if (ProceduralMesh)
	{
		ProceduralMesh->ClearAllMeshSections();
	}
	MarkForRebuild();
}

float UVoxelComponent::CalculateTotalMass() const
{
	float TotalMass = 0.0f;
	for (const FVoxelBlock& Block : Blocks)
	{
		if (!Block.bIsDestroyed)
		{
			TotalMass += Block.Mass;
		}
	}
	return TotalMass;
}

void UVoxelComponent::RebuildMesh()
{
	if (!ProceduralMesh)
	{
		UE_LOG(LogTemp, Warning, TEXT("VoxelComponent: ProceduralMesh is null, cannot rebuild"));
		return;
	}

	if (Blocks.Num() == 0)
	{
		ProceduralMesh->ClearAllMeshSections();
		return;
	}

	if (bUseGreedyMeshing)
	{
		GenerateGreedyMesh();
	}
	else
	{
		GenerateSimpleMesh();
	}
}

void UVoxelComponent::GenerateSimpleMesh()
{
	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector> Normals;
	TArray<FColor> VertexColors;

	// Build spatial lookup for neighbor checking
	TMap<FVector, int32> BlockLookup = BuildBlockLookup();

	// Generate faces for each block
	for (const FVoxelBlock& Block : Blocks)
	{
		if (!Block.bIsDestroyed)
		{
			GenerateBlockFaces(Block, BlockLookup, Vertices, Triangles, Normals, VertexColors);
		}
	}

	// Create mesh section
	if (Vertices.Num() > 0)
	{
		TArray<FVector2D> UV0; // Empty UV for now
		TArray<FProcMeshTangent> Tangents; // Empty tangents for now
		
		ProceduralMesh->ClearAllMeshSections();
		ProceduralMesh->CreateMeshSection(0, Vertices, Triangles, Normals, UV0, VertexColors, Tangents, true);
	}
}

void UVoxelComponent::GenerateGreedyMesh()
{
	// TODO: Implement greedy meshing algorithm
	// For now, fall back to simple mesh generation
	UE_LOG(LogTemp, Warning, TEXT("VoxelComponent: Greedy meshing not yet implemented, using simple mesh"));
	GenerateSimpleMesh();
}

void UVoxelComponent::GenerateBlockFaces(const FVoxelBlock& Block, const TMap<FVector, int32>& BlockLookup,
                                          TArray<FVector>& Vertices, TArray<int32>& Triangles,
                                          TArray<FVector>& Normals, TArray<FColor>& VertexColors)
{
	// Face directions: Right, Left, Top, Bottom, Front, Back
	static const FVector Directions[] = {
		FVector(1, 0, 0),   // Right (+X)
		FVector(-1, 0, 0),  // Left (-X)
		FVector(0, 0, 1),   // Top (+Z in UE5)
		FVector(0, 0, -1),  // Bottom (-Z in UE5)
		FVector(0, 1, 0),   // Front (+Y)
		FVector(0, -1, 0)   // Back (-Y)
	};

	for (int32 i = 0; i < 6; ++i)
	{
		const FVector& Dir = Directions[i];
		
		// Calculate neighbor position
		FVector Offset = FVector(
			Dir.X != 0 ? Block.Size.X : 0,
			Dir.Y != 0 ? Block.Size.Y : 0,
			Dir.Z != 0 ? Block.Size.Z : 0
		);
		
		FVector NeighborPos = Block.Position + Dir * Offset;
		FVector NeighborKey = RoundPosition(NeighborPos);

		// Only generate face if no neighbor exists
		if (!BlockLookup.Contains(NeighborKey))
		{
			AddFace(Block.Position, Block.Size, i, Block.Color, Vertices, Triangles, Normals, VertexColors);
		}
	}
}

void UVoxelComponent::AddFace(const FVector& Position, const FVector& Size, int32 FaceIndex,
                               const FColor& Color, TArray<FVector>& Vertices, TArray<int32>& Triangles,
                               TArray<FVector>& Normals, TArray<FColor>& VertexColors)
{
	FVector HalfSize = Size * 0.5f;
	int32 BaseIndex = Vertices.Num();

	// Define face vertices based on face index
	// UE5 uses Z-up coordinate system
	TArray<FVector> FaceVertices;
	FVector Normal;

	switch (FaceIndex)
	{
	case 0: // Right (+X)
		FaceVertices = {
			Position + FVector(HalfSize.X, -HalfSize.Y, -HalfSize.Z),
			Position + FVector(HalfSize.X, HalfSize.Y, -HalfSize.Z),
			Position + FVector(HalfSize.X, HalfSize.Y, HalfSize.Z),
			Position + FVector(HalfSize.X, -HalfSize.Y, HalfSize.Z)
		};
		Normal = FVector(1, 0, 0);
		break;
		
	case 1: // Left (-X)
		FaceVertices = {
			Position + FVector(-HalfSize.X, HalfSize.Y, -HalfSize.Z),
			Position + FVector(-HalfSize.X, -HalfSize.Y, -HalfSize.Z),
			Position + FVector(-HalfSize.X, -HalfSize.Y, HalfSize.Z),
			Position + FVector(-HalfSize.X, HalfSize.Y, HalfSize.Z)
		};
		Normal = FVector(-1, 0, 0);
		break;
		
	case 2: // Top (+Z)
		FaceVertices = {
			Position + FVector(-HalfSize.X, -HalfSize.Y, HalfSize.Z),
			Position + FVector(HalfSize.X, -HalfSize.Y, HalfSize.Z),
			Position + FVector(HalfSize.X, HalfSize.Y, HalfSize.Z),
			Position + FVector(-HalfSize.X, HalfSize.Y, HalfSize.Z)
		};
		Normal = FVector(0, 0, 1);
		break;
		
	case 3: // Bottom (-Z)
		FaceVertices = {
			Position + FVector(-HalfSize.X, HalfSize.Y, -HalfSize.Z),
			Position + FVector(HalfSize.X, HalfSize.Y, -HalfSize.Z),
			Position + FVector(HalfSize.X, -HalfSize.Y, -HalfSize.Z),
			Position + FVector(-HalfSize.X, -HalfSize.Y, -HalfSize.Z)
		};
		Normal = FVector(0, 0, -1);
		break;
		
	case 4: // Front (+Y)
		FaceVertices = {
			Position + FVector(-HalfSize.X, HalfSize.Y, -HalfSize.Z),
			Position + FVector(-HalfSize.X, HalfSize.Y, HalfSize.Z),
			Position + FVector(HalfSize.X, HalfSize.Y, HalfSize.Z),
			Position + FVector(HalfSize.X, HalfSize.Y, -HalfSize.Z)
		};
		Normal = FVector(0, 1, 0);
		break;
		
	case 5: // Back (-Y)
		FaceVertices = {
			Position + FVector(HalfSize.X, -HalfSize.Y, -HalfSize.Z),
			Position + FVector(HalfSize.X, -HalfSize.Y, HalfSize.Z),
			Position + FVector(-HalfSize.X, -HalfSize.Y, HalfSize.Z),
			Position + FVector(-HalfSize.X, -HalfSize.Y, -HalfSize.Z)
		};
		Normal = FVector(0, -1, 0);
		break;
		
	default:
		return;
	}

	// Add vertices
	for (const FVector& Vertex : FaceVertices)
	{
		Vertices.Add(Vertex);
		Normals.Add(Normal);
		VertexColors.Add(Color);
	}

	// Add triangles (two triangles per quad)
	Triangles.Add(BaseIndex + 0);
	Triangles.Add(BaseIndex + 1);
	Triangles.Add(BaseIndex + 2);

	Triangles.Add(BaseIndex + 0);
	Triangles.Add(BaseIndex + 2);
	Triangles.Add(BaseIndex + 3);
}

TMap<FVector, int32> UVoxelComponent::BuildBlockLookup() const
{
	TMap<FVector, int32> Lookup;
	for (int32 i = 0; i < Blocks.Num(); ++i)
	{
		if (!Blocks[i].bIsDestroyed)
		{
			FVector Key = RoundPosition(Blocks[i].Position);
			Lookup.Add(Key, i);
		}
	}
	return Lookup;
}

FVector UVoxelComponent::RoundPosition(const FVector& Position)
{
	// Round to nearest integer for lookup
	return FVector(
		FMath::RoundToFloat(Position.X),
		FMath::RoundToFloat(Position.Y),
		FMath::RoundToFloat(Position.Z)
	);
}
