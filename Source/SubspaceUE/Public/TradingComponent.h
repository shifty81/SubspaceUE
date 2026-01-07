// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TradingComponent.generated.h"

/**
 * Ware categories (X4-inspired)
 */
UENUM(BlueprintType)
enum class EWareCategory : uint8
{
	RawMaterials UMETA(DisplayName = "Raw Materials"),      // Ore, Silicon, Ice, Gas
	RefinedMaterials UMETA(DisplayName = "Refined Materials"),  // Metals, Crystals
	Components UMETA(DisplayName = "Components"),           // Microchips, Hull Parts
	FoodDrink UMETA(DisplayName = "Food & Drink"),         // Consumables
	Medical UMETA(DisplayName = "Medical"),                // Medical supplies
	Technology UMETA(DisplayName = "Technology"),          // Advanced tech
	Weapons UMETA(DisplayName = "Weapons"),                // Ship weapons
	Ships UMETA(DisplayName = "Ships")                     // Completed ships
};

/**
 * Ware data structure
 */
USTRUCT(BlueprintType)
struct FWare
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ware")
	FString WareName = TEXT("Unknown Ware");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ware")
	EWareCategory Category = EWareCategory::RawMaterials;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ware")
	float BasePrice = 100.0f;  // Credits per unit

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ware")
	float Volume = 1.0f;  // Cargo space required per unit

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ware")
	int32 MinProduction = 0;  // Station produces at least this much

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ware")
	int32 MaxProduction = 100;  // Station produces at most this much

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ware")
	float ProductionTime = 60.0f;  // Seconds to produce one unit

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ware")
	TMap<FString, int32> InputWares;  // Required wares to produce this

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ware")
	FString Description = TEXT("");
};

/**
 * Station inventory/storage
 */
USTRUCT(BlueprintType)
struct FStationStorage
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Storage")
	TMap<FString, int32> WareStock;  // WareId -> Quantity

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Storage")
	int32 MaxCapacity = 10000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Storage")
	int32 CurrentUsed = 0;
};

/**
 * Trade order (buy/sell order at station)
 */
USTRUCT(BlueprintType)
struct FTradeOrder
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trade")
	FString WareId = TEXT("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trade")
	bool bIsBuyOrder = true;  // true = buying, false = selling

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trade")
	float PriceModifier = 1.0f;  // Multiplier to base price

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trade")
	int32 MinQuantity = 0;  // Don't buy/sell if stock below this

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trade")
	int32 MaxQuantity = 1000;  // Don't buy/sell if stock above this

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trade")
	bool bIsActive = true;
};

/**
 * Trade deal result
 */
USTRUCT(BlueprintType)
struct FTradeDeal
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Trade")
	AActor* BuyStation = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Trade")
	AActor* SellStation = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Trade")
	FString WareId = TEXT("");

	UPROPERTY(BlueprintReadOnly, Category = "Trade")
	float ProfitPerUnit = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Trade")
	float TotalProfit = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Trade")
	int32 Volume = 0;

	UPROPERTY(BlueprintReadOnly, Category = "Trade")
	float Distance = 0.0f;  // Distance between stations
};

/**
 * Component that manages trading for ships and stations
 * X4-style dynamic economy system
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SUBSPACEUE_API UTradingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTradingComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** Ware library */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trading")
	TMap<FString, FWare> WareLibrary;

	/** Station storage (if this is a station) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trading")
	FStationStorage Storage;

	/** Trade orders (if this is a station) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trading")
	TArray<FTradeOrder> TradeOrders;

	/** Auto-trade enabled (if this is a ship) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trading")
	bool bAutoTradeEnabled = false;

	/** Credits available for trading */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trading")
	int32 Credits = 10000;

	/** Initialize default ware library */
	UFUNCTION(BlueprintCallable, Category = "Trading")
	void InitializeWareLibrary();

	/** Calculate price based on supply/demand */
	UFUNCTION(BlueprintCallable, Category = "Trading")
	float CalculatePrice(const FString& WareId, bool bIsBuying) const;

	/** Buy ware from station */
	UFUNCTION(BlueprintCallable, Category = "Trading")
	bool BuyWare(AActor* FromStation, const FString& WareId, int32 Quantity, int32& OutCost);

	/** Sell ware to station */
	UFUNCTION(BlueprintCallable, Category = "Trading")
	bool SellWare(AActor* ToStation, const FString& WareId, int32 Quantity, int32& OutRevenue);

	/** Find profitable trade routes */
	UFUNCTION(BlueprintCallable, Category = "Trading")
	TArray<FTradeDeal> FindProfitableDeals(FVector CurrentLocation, float MaxJumpDistance, int32 MaxResults = 10);

	/** Add ware to storage */
	UFUNCTION(BlueprintCallable, Category = "Trading")
	bool AddWareToStorage(const FString& WareId, int32 Quantity);

	/** Remove ware from storage */
	UFUNCTION(BlueprintCallable, Category = "Trading")
	bool RemoveWareFromStorage(const FString& WareId, int32 Quantity);

	/** Get current stock of ware */
	UFUNCTION(BlueprintCallable, Category = "Trading")
	int32 GetWareStock(const FString& WareId) const;

	/** Set up default station trade orders */
	UFUNCTION(BlueprintCallable, Category = "Trading")
	void SetupStationTrading(const TArray<FString>& BuyWares, const TArray<FString>& SellWares);

	/** Update production (call periodically for stations) */
	UFUNCTION(BlueprintCallable, Category = "Trading")
	void UpdateProduction(float DeltaTime);

protected:
	/** Create ware definition */
	FWare CreateWare(const FString& Name, EWareCategory Category, float BasePrice, float Volume, float ProductionTime = 60.0f);

	/** Production timer for stations */
	float ProductionTimer = 0.0f;
};
