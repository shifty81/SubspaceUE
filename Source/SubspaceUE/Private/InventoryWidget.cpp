// Copyright Epic Games, Inc. All Rights Reserved.

#include "InventoryWidget.h"

void UInventoryWidget::UpdateInventory(const TArray<FResourceEntry>& Resources)
{
	CachedResources = Resources;
	OnInventoryUpdated(Resources);
}

void UInventoryWidget::UpdateCargoCapacity(int32 CurrentCargo, int32 MaxCargo)
{
	CachedCurrentCargo = CurrentCargo;
	CachedMaxCargo = MaxCargo;

	float CargoPercent = MaxCargo > 0 ? (float)CurrentCargo / (float)MaxCargo : 0.0f;
	OnCargoCapacityUpdated(CurrentCargo, MaxCargo, CargoPercent);
}
