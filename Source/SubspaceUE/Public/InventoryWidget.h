// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

/**
 * Resource entry for displaying in inventory
 */
USTRUCT(BlueprintType)
struct FResourceEntry
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	FString ResourceName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 Quantity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	FColor ResourceColor;

	FResourceEntry()
		: ResourceName(TEXT("Unknown"))
		, Quantity(0)
		, ResourceColor(FColor::White)
	{
	}

	FResourceEntry(const FString& InName, int32 InQuantity, const FColor& InColor)
		: ResourceName(InName)
		, Quantity(InQuantity)
		, ResourceColor(InColor)
	{
	}
};

/**
 * Inventory widget for displaying resources and cargo
 */
UCLASS()
class SUBSPACEUE_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/** Update inventory display with resources */
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void UpdateInventory(const TArray<FResourceEntry>& Resources);

	/** Update cargo capacity display */
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void UpdateCargoCapacity(int32 CurrentCargo, int32 MaxCargo);

protected:
	// Blueprint implementable events
	UFUNCTION(BlueprintImplementableEvent, Category = "Inventory")
	void OnInventoryUpdated(const TArray<FResourceEntry>& Resources);

	UFUNCTION(BlueprintImplementableEvent, Category = "Inventory")
	void OnCargoCapacityUpdated(int32 CurrentCargo, int32 MaxCargo, float CargoPercent);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	TArray<FResourceEntry> CachedResources;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	int32 CachedCurrentCargo;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	int32 CachedMaxCargo;
};
