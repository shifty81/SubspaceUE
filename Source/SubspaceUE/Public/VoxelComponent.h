// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProceduralMeshComponent.h"
#include "VoxelBlock.h"
#include "VoxelComponent.generated.h"

/**
 * Component that manages voxel blocks and generates procedural meshes
 * Used for asteroids, damage visualization, and voxel-based structures
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SUBSPACEUE_API UVoxelComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UVoxelComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** Array of voxel blocks */
	UPROPERTY(BlueprintReadOnly, Category = "Voxel")
	TArray<FVoxelBlock> Blocks;

	/** Procedural mesh component for rendering */
	UPROPERTY(BlueprintReadOnly, Category = "Voxel")
	UProceduralMeshComponent* ProceduralMesh;

	/** Whether to use greedy meshing for optimization */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voxel|Optimization")
	bool bUseGreedyMeshing;

	/** Whether the mesh needs to be rebuilt */
	UPROPERTY(BlueprintReadOnly, Category = "Voxel")
	bool bNeedsRebuild;

	/** Add a voxel block to the structure */
	UFUNCTION(BlueprintCallable, Category = "Voxel")
	void AddBlock(const FVoxelBlock& Block);

	/** Remove a voxel block by ID */
	UFUNCTION(BlueprintCallable, Category = "Voxel")
	bool RemoveBlock(const FGuid& BlockId);

	/** Get a voxel block by ID */
	UFUNCTION(BlueprintCallable, Category = "Voxel")
	bool GetBlock(const FGuid& BlockId, FVoxelBlock& OutBlock) const;

	/** Get all voxel blocks */
	UFUNCTION(BlueprintCallable, Category = "Voxel")
	TArray<FVoxelBlock> GetAllBlocks() const { return Blocks; }

	/** Clear all voxel blocks */
	UFUNCTION(BlueprintCallable, Category = "Voxel")
	void ClearBlocks();

	/** Calculate total mass of all blocks */
	UFUNCTION(BlueprintCallable, Category = "Voxel")
	float CalculateTotalMass() const;

	/** Rebuild the procedural mesh from voxel blocks */
	UFUNCTION(BlueprintCallable, Category = "Voxel")
	void RebuildMesh();

	/** Mark mesh for rebuild on next tick */
	UFUNCTION(BlueprintCallable, Category = "Voxel")
	void MarkForRebuild() { bNeedsRebuild = true; }

protected:
	/** Generate mesh using simple face culling */
	void GenerateSimpleMesh();

	/** Generate mesh using greedy meshing algorithm (optimized) */
	void GenerateGreedyMesh();

	/** Generate faces for a single block with neighbor culling */
	void GenerateBlockFaces(const FVoxelBlock& Block, const TMap<FVector, int32>& BlockLookup,
	                        TArray<FVector>& Vertices, TArray<int32>& Triangles,
	                        TArray<FVector>& Normals, TArray<FColor>& VertexColors);

	/** Add a quad face to the mesh arrays */
	void AddFace(const FVector& Position, const FVector& Size, int32 FaceIndex,
	             const FColor& Color, TArray<FVector>& Vertices, TArray<int32>& Triangles,
	             TArray<FVector>& Normals, TArray<FColor>& VertexColors);

	/** Build spatial lookup for fast neighbor checking */
	TMap<FVector, int32> BuildBlockLookup() const;

	/** Round position for lookup key */
	static FVector RoundPosition(const FVector& Position);

	// Greedy meshing helper functions
	
	/** Process one axis for greedy meshing */
	void GreedyMeshAxis(
		const TArray<const FVoxelBlock*>& VoxelGrid,
		const FIntVector& GridSize,
		const FIntVector& GridMin,
		int32 Axis,
		int32 Direction,
		TArray<FVector>& Vertices,
		TArray<int32>& Triangles,
		TArray<FVector>& Normals,
		TArray<FColor>& VertexColors);

	/** Get grid coordinates based on axis orientation */
	static FIntVector GetAxisCoords(int32 Axis, int32 U, int32 V, int32 W);

	/** Get voxel block from grid with bounds checking */
	static const FVoxelBlock* GetVoxelFromGrid(
		const TArray<const FVoxelBlock*>& VoxelGrid,
		const FIntVector& GridSize,
		const FIntVector& Coords);

	/** Add a greedy-meshed quad to the mesh arrays */
	void AddGreedyQuad(
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
		TArray<FColor>& VertexColors);
};
