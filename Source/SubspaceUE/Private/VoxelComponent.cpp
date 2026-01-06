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
	if (Blocks.Num() == 0)
	{
		ProceduralMesh->ClearAllMeshSections();
		return;
	}

	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector> Normals;
	TArray<FColor> VertexColors;

	// Build a 3D voxel grid for greedy meshing
	// Find bounds
	FVector Min(MAX_flt);
	FVector Max(-MAX_flt);
	
	for (const FVoxelBlock& Block : Blocks)
	{
		if (!Block.bIsDestroyed)
		{
			FVector HalfSize = Block.Size * 0.5f;
			Min = FVector::Min(Min, Block.Position - HalfSize);
			Max = FVector::Max(Max, Block.Position + HalfSize);
		}
	}

	// Convert to integer grid coordinates
	FIntVector GridMin(
		FMath::FloorToInt(Min.X),
		FMath::FloorToInt(Min.Y),
		FMath::FloorToInt(Min.Z)
	);
	FIntVector GridMax(
		FMath::CeilToInt(Max.X),
		FMath::CeilToInt(Max.Y),
		FMath::CeilToInt(Max.Z)
	);

	FIntVector GridSize = GridMax - GridMin + FIntVector(1);

	// Prevent excessive memory allocation
	if (GridSize.X > 1000 || GridSize.Y > 1000 || GridSize.Z > 1000)
	{
		UE_LOG(LogTemp, Warning, TEXT("VoxelComponent: Grid too large for greedy meshing, using simple mesh"));
		GenerateSimpleMesh();
		return;
	}

	// Create 3D array for voxel grid
	TArray<const FVoxelBlock*> VoxelGrid;
	int32 TotalSize = GridSize.X * GridSize.Y * GridSize.Z;
	VoxelGrid.Init(nullptr, TotalSize);

	// Fill grid with block pointers
	for (const FVoxelBlock& Block : Blocks)
	{
		if (!Block.bIsDestroyed)
		{
			FIntVector GridPos(
				FMath::RoundToInt(Block.Position.X) - GridMin.X,
				FMath::RoundToInt(Block.Position.Y) - GridMin.Y,
				FMath::RoundToInt(Block.Position.Z) - GridMin.Z
			);

			if (GridPos.X >= 0 && GridPos.X < GridSize.X &&
				GridPos.Y >= 0 && GridPos.Y < GridSize.Y &&
				GridPos.Z >= 0 && GridPos.Z < GridSize.Z)
			{
				int32 Index = GridPos.X + GridPos.Y * GridSize.X + GridPos.Z * GridSize.X * GridSize.Y;
				VoxelGrid[Index] = &Block;
			}
		}
	}

	// Process each axis (X=0, Y=1, Z=2) and both directions
	for (int32 Axis = 0; Axis < 3; ++Axis)
	{
		for (int32 Direction = -1; Direction <= 1; Direction += 2)
		{
			GreedyMeshAxis(VoxelGrid, GridSize, GridMin, Axis, Direction, Vertices, Triangles, Normals, VertexColors);
		}
	}

	// Create mesh section
	if (Vertices.Num() > 0)
	{
		TArray<FVector2D> UV0;
		TArray<FProcMeshTangent> Tangents;
		
		ProceduralMesh->ClearAllMeshSections();
		ProceduralMesh->CreateMeshSection(0, Vertices, Triangles, Normals, UV0, VertexColors, Tangents, true);
		
		UE_LOG(LogTemp, Log, TEXT("VoxelComponent: Greedy mesh generated with %d vertices, %d triangles"), 
			Vertices.Num(), Triangles.Num() / 3);
	}
}

void UVoxelComponent::GreedyMeshAxis(
	const TArray<const FVoxelBlock*>& VoxelGrid,
	const FIntVector& GridSize,
	const FIntVector& GridMin,
	int32 Axis,
	int32 Direction,
	TArray<FVector>& Vertices,
	TArray<int32>& Triangles,
	TArray<FVector>& Normals,
	TArray<FColor>& VertexColors)
{
	// Determine dimensions based on axis
	int32 USize, VSize, WSize;
	
	switch (Axis)
	{
	case 0: // X axis
		USize = GridSize.Y;
		VSize = GridSize.Z;
		WSize = GridSize.X;
		break;
	case 1: // Y axis
		USize = GridSize.X;
		VSize = GridSize.Z;
		WSize = GridSize.Y;
		break;
	default: // Z axis
		USize = GridSize.X;
		VSize = GridSize.Y;
		WSize = GridSize.Z;
		break;
	}

	// Process each slice along the axis
	for (int32 D = 0; D < WSize; ++D)
	{
		// Create mask for this slice
		TArray<const FVoxelBlock*> Mask;
		Mask.Init(nullptr, USize * VSize);

		// Fill mask by checking which faces are exposed
		for (int32 I = 0; I < USize; ++I)
		{
			for (int32 J = 0; J < VSize; ++J)
			{
				FIntVector Coords = GetAxisCoords(Axis, I, J, D);
				const FVoxelBlock* Block = GetVoxelFromGrid(VoxelGrid, GridSize, Coords);

				if (Block != nullptr)
				{
					// Check neighbor in direction
					FIntVector NeighborCoords = GetAxisCoords(Axis, I, J, D + Direction);
					const FVoxelBlock* Neighbor = GetVoxelFromGrid(VoxelGrid, GridSize, NeighborCoords);

					// Face is exposed if no neighbor
					if (Neighbor == nullptr)
					{
						Mask[I + J * USize] = Block;
					}
				}
			}
		}

		// Generate mesh from mask using greedy algorithm
		for (int32 I = 0; I < USize; ++I)
		{
			for (int32 J = 0; J < VSize; ++J)
			{
				int32 MaskIndex = I + J * USize;
				const FVoxelBlock* Face = Mask[MaskIndex];
				
				if (Face == nullptr)
					continue;

				// Find width of this quad
				int32 QuadWidth = 1;
				while (I + QuadWidth < USize)
				{
					int32 NextMaskIndex = (I + QuadWidth) + J * USize;
					const FVoxelBlock* NextFace = Mask[NextMaskIndex];
					
					if (NextFace == nullptr || NextFace->Color != Face->Color || 
						NextFace->MaterialType != Face->MaterialType)
					{
						break;
					}
					QuadWidth++;
				}

				// Find height of this quad
				int32 QuadHeight = 1;
				bool bCanExtend = true;
				
				while (J + QuadHeight < VSize && bCanExtend)
				{
					// Check entire row
					for (int32 K = I; K < I + QuadWidth; ++K)
					{
						int32 CheckMaskIndex = K + (J + QuadHeight) * USize;
						const FVoxelBlock* CheckFace = Mask[CheckMaskIndex];
						
						if (CheckFace == nullptr || CheckFace->Color != Face->Color ||
							CheckFace->MaterialType != Face->MaterialType)
						{
							bCanExtend = false;
							break;
						}
					}
					
					if (bCanExtend)
						QuadHeight++;
				}

				// Add merged quad to mesh
				AddGreedyQuad(GridMin, Axis, Direction, D, I, J, QuadWidth, QuadHeight, *Face,
					Vertices, Triangles, Normals, VertexColors);

				// Clear processed cells in mask
				for (int32 W = I; W < I + QuadWidth; ++W)
				{
					for (int32 H = J; H < J + QuadHeight; ++H)
					{
						Mask[W + H * USize] = nullptr;
					}
				}
			}
		}
	}
}

FIntVector UVoxelComponent::GetAxisCoords(int32 Axis, int32 U, int32 V, int32 W)
{
	switch (Axis)
	{
	case 0: // X axis: W=X, U=Y, V=Z
		return FIntVector(W, U, V);
	case 1: // Y axis: U=X, W=Y, V=Z
		return FIntVector(U, W, V);
	default: // Z axis: U=X, V=Y, W=Z
		return FIntVector(U, V, W);
	}
}

const FVoxelBlock* UVoxelComponent::GetVoxelFromGrid(
	const TArray<const FVoxelBlock*>& VoxelGrid,
	const FIntVector& GridSize,
	const FIntVector& Coords)
{
	if (Coords.X < 0 || Coords.X >= GridSize.X ||
		Coords.Y < 0 || Coords.Y >= GridSize.Y ||
		Coords.Z < 0 || Coords.Z >= GridSize.Z)
	{
		return nullptr;
	}

	int32 Index = Coords.X + Coords.Y * GridSize.X + Coords.Z * GridSize.X * GridSize.Y;
	if (Index >= 0 && Index < VoxelGrid.Num())
	{
		return VoxelGrid[Index];
	}

	return nullptr;
}

void UVoxelComponent::AddGreedyQuad(
	const FIntVector& GridMin,
	int32 Axis,
	int32 Direction,
	int32 Depth,
	int32 U,
	int32 V,
	int32 Width,
	int32 Height,
	const FVoxelBlock& Block,
	TArray<FVector>& Vertices,
	TArray<int32>& Triangles,
	TArray<FVector>& Normals,
	TArray<FColor>& VertexColors)
{
	// Convert grid coordinates back to world space
	FVector WorldOffset(GridMin);
	
	// Calculate quad corners based on axis and direction
	FVector QuadVertices[4];
	FVector Normal;

	// Get quad position in grid space
	FIntVector GridCoords = GetAxisCoords(Axis, U, V, Depth);
	FVector QuadPos = FVector(GridCoords) + WorldOffset;

	// Calculate quad extents
	float QuadWidth = static_cast<float>(Width);
	float QuadHeight = static_cast<float>(Height);

	// Generate quad vertices based on axis and direction
	switch (Axis)
	{
	case 0: // X axis
		if (Direction > 0)
		{
			QuadVertices[0] = QuadPos + FVector(0.5f, 0, 0);
			QuadVertices[1] = QuadPos + FVector(0.5f, QuadWidth, 0);
			QuadVertices[2] = QuadPos + FVector(0.5f, QuadWidth, QuadHeight);
			QuadVertices[3] = QuadPos + FVector(0.5f, 0, QuadHeight);
			Normal = FVector(1, 0, 0);
		}
		else
		{
			QuadVertices[0] = QuadPos + FVector(-0.5f, QuadWidth, 0);
			QuadVertices[1] = QuadPos + FVector(-0.5f, 0, 0);
			QuadVertices[2] = QuadPos + FVector(-0.5f, 0, QuadHeight);
			QuadVertices[3] = QuadPos + FVector(-0.5f, QuadWidth, QuadHeight);
			Normal = FVector(-1, 0, 0);
		}
		break;

	case 1: // Y axis
		if (Direction > 0)
		{
			QuadVertices[0] = QuadPos + FVector(0, 0.5f, 0);
			QuadVertices[1] = QuadPos + FVector(QuadWidth, 0.5f, 0);
			QuadVertices[2] = QuadPos + FVector(QuadWidth, 0.5f, QuadHeight);
			QuadVertices[3] = QuadPos + FVector(0, 0.5f, QuadHeight);
			Normal = FVector(0, 1, 0);
		}
		else
		{
			QuadVertices[0] = QuadPos + FVector(QuadWidth, -0.5f, 0);
			QuadVertices[1] = QuadPos + FVector(0, -0.5f, 0);
			QuadVertices[2] = QuadPos + FVector(0, -0.5f, QuadHeight);
			QuadVertices[3] = QuadPos + FVector(QuadWidth, -0.5f, QuadHeight);
			Normal = FVector(0, -1, 0);
		}
		break;

	default: // Z axis
		if (Direction > 0)
		{
			QuadVertices[0] = QuadPos + FVector(0, 0, 0.5f);
			QuadVertices[1] = QuadPos + FVector(QuadWidth, 0, 0.5f);
			QuadVertices[2] = QuadPos + FVector(QuadWidth, QuadHeight, 0.5f);
			QuadVertices[3] = QuadPos + FVector(0, QuadHeight, 0.5f);
			Normal = FVector(0, 0, 1);
		}
		else
		{
			QuadVertices[0] = QuadPos + FVector(QuadWidth, 0, -0.5f);
			QuadVertices[1] = QuadPos + FVector(0, 0, -0.5f);
			QuadVertices[2] = QuadPos + FVector(0, QuadHeight, -0.5f);
			QuadVertices[3] = QuadPos + FVector(QuadWidth, QuadHeight, -0.5f);
			Normal = FVector(0, 0, -1);
		}
		break;
	}

	// Add vertices to mesh
	int32 BaseIndex = Vertices.Num();
	for (int32 i = 0; i < 4; ++i)
	{
		Vertices.Add(QuadVertices[i]);
		Normals.Add(Normal);
		VertexColors.Add(Block.Color);
	}

	// Add triangles (two triangles per quad)
	Triangles.Add(BaseIndex + 0);
	Triangles.Add(BaseIndex + 1);
	Triangles.Add(BaseIndex + 2);

	Triangles.Add(BaseIndex + 0);
	Triangles.Add(BaseIndex + 2);
	Triangles.Add(BaseIndex + 3);
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
