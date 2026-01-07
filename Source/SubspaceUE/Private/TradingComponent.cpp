// Copyright Epic Games, Inc. All Rights Reserved.

#include "TradingComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogTrading, Log, All);

UTradingComponent::UTradingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = 1.0f;  // Update once per second
}

void UTradingComponent::BeginPlay()
{
	Super::BeginPlay();
	
	if (WareLibrary.Num() == 0)
	{
		InitializeWareLibrary();
	}
}

void UTradingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// Update production for stations
	UpdateProduction(DeltaTime);
	
	// TODO: Auto-trade logic for ships
	if (bAutoTradeEnabled)
	{
		// Find and execute profitable trades
	}
}

void UTradingComponent::InitializeWareLibrary()
{
	WareLibrary.Empty();
	
	// Raw Materials
	WareLibrary.Add(TEXT("Ore"), CreateWare(TEXT("Ore"), EWareCategory::RawMaterials, 10.0f, 1.0f, 30.0f));
	WareLibrary.Add(TEXT("Silicon"), CreateWare(TEXT("Silicon"), EWareCategory::RawMaterials, 15.0f, 1.0f, 40.0f));
	WareLibrary.Add(TEXT("Ice"), CreateWare(TEXT("Ice"), EWareCategory::RawMaterials, 8.0f, 1.0f, 20.0f));
	WareLibrary.Add(TEXT("Hydrogen"), CreateWare(TEXT("Hydrogen"), EWareCategory::RawMaterials, 12.0f, 1.0f, 25.0f));
	WareLibrary.Add(TEXT("Helium"), CreateWare(TEXT("Helium"), EWareCategory::RawMaterials, 18.0f, 1.0f, 35.0f));
	
	// Refined Materials
	WareLibrary.Add(TEXT("Steel"), CreateWare(TEXT("Steel"), EWareCategory::RefinedMaterials, 50.0f, 1.0f, 60.0f));
	WareLibrary.Add(TEXT("Titanium"), CreateWare(TEXT("Titanium"), EWareCategory::RefinedMaterials, 80.0f, 1.0f, 90.0f));
	WareLibrary.Add(TEXT("Crystals"), CreateWare(TEXT("Crystals"), EWareCategory::RefinedMaterials, 120.0f, 0.5f, 120.0f));
	
	// Components
	WareLibrary.Add(TEXT("HullParts"), CreateWare(TEXT("Hull Parts"), EWareCategory::Components, 200.0f, 2.0f, 180.0f));
	WareLibrary.Add(TEXT("Microchips"), CreateWare(TEXT("Microchips"), EWareCategory::Components, 350.0f, 0.2f, 240.0f));
	WareLibrary.Add(TEXT("EngineComponents"), CreateWare(TEXT("Engine Components"), EWareCategory::Components, 500.0f, 3.0f, 300.0f));
	
	// Food & Consumables
	WareLibrary.Add(TEXT("Food"), CreateWare(TEXT("Food Rations"), EWareCategory::FoodDrink, 30.0f, 1.0f, 45.0f));
	WareLibrary.Add(TEXT("Water"), CreateWare(TEXT("Water"), EWareCategory::FoodDrink, 15.0f, 1.0f, 30.0f));
	
	// Medical
	WareLibrary.Add(TEXT("Medical"), CreateWare(TEXT("Medical Supplies"), EWareCategory::Medical, 150.0f, 0.5f, 120.0f));
	
	// Technology
	WareLibrary.Add(TEXT("AdvancedElectronics"), CreateWare(TEXT("Advanced Electronics"), EWareCategory::Technology, 800.0f, 0.3f, 360.0f));
	WareLibrary.Add(TEXT("Drones"), CreateWare(TEXT("Drones"), EWareCategory::Technology, 1200.0f, 1.0f, 480.0f));
	
	// Setup production chains
	if (FWare* Steel = WareLibrary.Find(TEXT("Steel")))
	{
		Steel->InputWares.Add(TEXT("Ore"), 2);
	}
	
	if (FWare* HullParts = WareLibrary.Find(TEXT("HullParts")))
	{
		HullParts->InputWares.Add(TEXT("Steel"), 3);
		HullParts->InputWares.Add(TEXT("Titanium"), 1);
	}
	
	if (FWare* EngineComponents = WareLibrary.Find(TEXT("EngineComponents")))
	{
		EngineComponents->InputWares.Add(TEXT("Steel"), 2);
		EngineComponents->InputWares.Add(TEXT("Microchips"), 2);
		EngineComponents->InputWares.Add(TEXT("Crystals"), 1);
	}
	
	UE_LOG(LogTrading, Log, TEXT("Initialized ware library with %d wares"), WareLibrary.Num());
}

float UTradingComponent::CalculatePrice(const FString& WareId, bool bIsBuying) const
{
	const FWare* Ware = WareLibrary.Find(WareId);
	if (!Ware)
	{
		return 0.0f;
	}
	
	float BasePrice = Ware->BasePrice;
	int32 CurrentStock = GetWareStock(WareId);
	int32 OptimalStock = (Ware->MinProduction + Ware->MaxProduction) / 2;
	
	// Supply/demand pricing
	float StockRatio = OptimalStock > 0 ? (float)CurrentStock / (float)OptimalStock : 1.0f;
	float PriceModifier = 1.0f;
	
	if (bIsBuying)
	{
		// High stock = lower sell price
		PriceModifier = FMath::Lerp(1.3f, 0.7f, StockRatio);
	}
	else
	{
		// Low stock = higher buy price
		PriceModifier = FMath::Lerp(1.5f, 0.8f, StockRatio);
	}
	
	return BasePrice * PriceModifier;
}

bool UTradingComponent::BuyWare(AActor* FromStation, const FString& WareId, int32 Quantity, int32& OutCost)
{
	if (!FromStation || Quantity <= 0)
	{
		return false;
	}
	
	UTradingComponent* StationTrading = FromStation->FindComponentByClass<UTradingComponent>();
	if (!StationTrading)
	{
		UE_LOG(LogTrading, Warning, TEXT("Station has no trading component"));
		return false;
	}
	
	// Check station has stock
	int32 StationStock = StationTrading->GetWareStock(WareId);
	if (StationStock < Quantity)
	{
		UE_LOG(LogTrading, Warning, TEXT("Insufficient stock at station: %d/%d"), StationStock, Quantity);
		return false;
	}
	
	// Calculate cost
	float UnitPrice = StationTrading->CalculatePrice(WareId, false);  // Station is selling
	OutCost = FMath::RoundToInt(UnitPrice * Quantity);
	
	// Check we have credits
	if (Credits < OutCost)
	{
		UE_LOG(LogTrading, Warning, TEXT("Insufficient credits: %d/%d"), Credits, OutCost);
		return false;
	}
	
	// Execute transaction
	if (StationTrading->RemoveWareFromStorage(WareId, Quantity) && AddWareToStorage(WareId, Quantity))
	{
		Credits -= OutCost;
		StationTrading->Credits += OutCost;
		
		UE_LOG(LogTrading, Log, TEXT("Bought %d x %s for %d credits"), Quantity, *WareId, OutCost);
		return true;
	}
	
	return false;
}

bool UTradingComponent::SellWare(AActor* ToStation, const FString& WareId, int32 Quantity, int32& OutRevenue)
{
	if (!ToStation || Quantity <= 0)
	{
		return false;
	}
	
	UTradingComponent* StationTrading = ToStation->FindComponentByClass<UTradingComponent>();
	if (!StationTrading)
	{
		return false;
	}
	
	// Check we have stock
	int32 OurStock = GetWareStock(WareId);
	if (OurStock < Quantity)
	{
		return false;
	}
	
	// Calculate revenue
	float UnitPrice = StationTrading->CalculatePrice(WareId, true);  // Station is buying
	OutRevenue = FMath::RoundToInt(UnitPrice * Quantity);
	
	// Check station has credits
	if (StationTrading->Credits < OutRevenue)
	{
		return false;
	}
	
	// Execute transaction
	if (RemoveWareFromStorage(WareId, Quantity) && StationTrading->AddWareToStorage(WareId, Quantity))
	{
		Credits += OutRevenue;
		StationTrading->Credits -= OutRevenue;
		
		UE_LOG(LogTrading, Log, TEXT("Sold %d x %s for %d credits"), Quantity, *WareId, OutRevenue);
		return true;
	}
	
	return false;
}

TArray<FTradeDeal> UTradingComponent::FindProfitableDeals(FVector CurrentLocation, float MaxJumpDistance, int32 MaxResults)
{
	TArray<FTradeDeal> Deals;
	
	// TODO: Query all stations in range
	// For each ware, find best buy/sell station pair
	// Calculate profit considering distance and volume
	
	return Deals;
}

bool UTradingComponent::AddWareToStorage(const FString& WareId, int32 Quantity)
{
	const FWare* Ware = WareLibrary.Find(WareId);
	if (!Ware || Quantity <= 0)
	{
		return false;
	}
	
	int32 RequiredSpace = FMath::RoundToInt(Ware->Volume * Quantity);
	if (Storage.CurrentUsed + RequiredSpace > Storage.MaxCapacity)
	{
		UE_LOG(LogTrading, Warning, TEXT("Insufficient storage space: %d/%d (need %d)"),
			Storage.CurrentUsed, Storage.MaxCapacity, RequiredSpace);
		return false;
	}
	
	int32* CurrentStock = Storage.WareStock.Find(WareId);
	if (CurrentStock)
	{
		*CurrentStock += Quantity;
	}
	else
	{
		Storage.WareStock.Add(WareId, Quantity);
	}
	
	Storage.CurrentUsed += RequiredSpace;
	return true;
}

bool UTradingComponent::RemoveWareFromStorage(const FString& WareId, int32 Quantity)
{
	const FWare* Ware = WareLibrary.Find(WareId);
	if (!Ware || Quantity <= 0)
	{
		return false;
	}
	
	int32* CurrentStock = Storage.WareStock.Find(WareId);
	if (!CurrentStock || *CurrentStock < Quantity)
	{
		return false;
	}
	
	*CurrentStock -= Quantity;
	int32 FreedSpace = FMath::RoundToInt(Ware->Volume * Quantity);
	Storage.CurrentUsed = FMath::Max(0, Storage.CurrentUsed - FreedSpace);
	
	return true;
}

int32 UTradingComponent::GetWareStock(const FString& WareId) const
{
	const int32* Stock = Storage.WareStock.Find(WareId);
	return Stock ? *Stock : 0;
}

void UTradingComponent::SetupStationTrading(const TArray<FString>& BuyWares, const TArray<FString>& SellWares)
{
	TradeOrders.Empty();
	
	// Create buy orders
	for (const FString& WareId : BuyWares)
	{
		FTradeOrder Order;
		Order.WareId = WareId;
		Order.bIsBuyOrder = true;
		Order.PriceModifier = 1.1f;  // Buy at 110% base price
		Order.MinQuantity = 0;
		Order.MaxQuantity = 5000;
		Order.bIsActive = true;
		TradeOrders.Add(Order);
	}
	
	// Create sell orders
	for (const FString& WareId : SellWares)
	{
		FTradeOrder Order;
		Order.WareId = WareId;
		Order.bIsBuyOrder = false;
		Order.PriceModifier = 0.9f;  // Sell at 90% base price
		Order.MinQuantity = 100;  // Keep minimum stock
		Order.MaxQuantity = 10000;
		Order.bIsActive = true;
		TradeOrders.Add(Order);
	}
	
	UE_LOG(LogTrading, Log, TEXT("Setup station trading: %d buy orders, %d sell orders"),
		BuyWares.Num(), SellWares.Num());
}

void UTradingComponent::UpdateProduction(float DeltaTime)
{
	ProductionTimer += DeltaTime;
	
	// Process production every 10 seconds
	if (ProductionTimer < 10.0f)
	{
		return;
	}
	
	ProductionTimer = 0.0f;
	
	// Check each sell order for production
	for (const FTradeOrder& Order : TradeOrders)
	{
		if (!Order.bIsBuyOrder && Order.bIsActive)
		{
			const FWare* Ware = WareLibrary.Find(Order.WareId);
			if (!Ware)
			{
				continue;
			}
			
			int32 CurrentStock = GetWareStock(Order.WareId);
			if (CurrentStock < Order.MaxQuantity)
			{
				// Check if we have input materials
				bool bCanProduce = true;
				for (const TPair<FString, int32>& Input : Ware->InputWares)
				{
					if (GetWareStock(Input.Key) < Input.Value)
					{
						bCanProduce = false;
						break;
					}
				}
				
				if (bCanProduce)
				{
					// Consume input materials
					for (const TPair<FString, int32>& Input : Ware->InputWares)
					{
						RemoveWareFromStorage(Input.Key, Input.Value);
					}
					
					// Produce output
					AddWareToStorage(Order.WareId, 1);
					UE_LOG(LogTrading, Verbose, TEXT("Produced 1x %s"), *Order.WareId);
				}
			}
		}
	}
}

FWare UTradingComponent::CreateWare(const FString& Name, EWareCategory Category, float BasePrice, float Volume, float ProductionTime)
{
	FWare Ware;
	Ware.WareName = Name;
	Ware.Category = Category;
	Ware.BasePrice = BasePrice;
	Ware.Volume = Volume;
	Ware.ProductionTime = ProductionTime;
	Ware.MinProduction = 0;
	Ware.MaxProduction = 100;
	return Ware;
}
