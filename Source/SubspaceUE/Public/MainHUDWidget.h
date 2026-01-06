// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainHUDWidget.generated.h"

/**
 * Main HUD widget for displaying ship status and game information
 * This is the C++ base class - create a Blueprint widget inheriting from this
 */
UCLASS()
class SUBSPACEUE_API UMainHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/** Update health display */
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void UpdateHealth(float CurrentHealth, float MaxHealth);

	/** Update shield display */
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void UpdateShield(float CurrentShield, float MaxShield);

	/** Update energy display */
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void UpdateEnergy(float CurrentEnergy, float MaxEnergy);

	/** Update speed display */
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void UpdateSpeed(float CurrentSpeed, float MaxSpeed);

	/** Update velocity vector */
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void UpdateVelocity(const FVector& Velocity);

	/** Update position display */
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void UpdatePosition(const FVector& Position);

	/** Update target information */
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void UpdateTarget(const FString& TargetName, float Distance);

	/** Clear target information */
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void ClearTarget();

protected:
	// Blueprint implementable events for actual UI updates
	// These should be implemented in the Blueprint child class

	UFUNCTION(BlueprintImplementableEvent, Category = "HUD")
	void OnHealthUpdated(float HealthPercent, const FText& HealthText);

	UFUNCTION(BlueprintImplementableEvent, Category = "HUD")
	void OnShieldUpdated(float ShieldPercent, const FText& ShieldText);

	UFUNCTION(BlueprintImplementableEvent, Category = "HUD")
	void OnEnergyUpdated(float EnergyPercent, const FText& EnergyText);

	UFUNCTION(BlueprintImplementableEvent, Category = "HUD")
	void OnSpeedUpdated(const FText& SpeedText);

	UFUNCTION(BlueprintImplementableEvent, Category = "HUD")
	void OnVelocityUpdated(const FText& VelocityText);

	UFUNCTION(BlueprintImplementableEvent, Category = "HUD")
	void OnPositionUpdated(const FText& PositionText);

	UFUNCTION(BlueprintImplementableEvent, Category = "HUD")
	void OnTargetUpdated(const FText& TargetText);

	UFUNCTION(BlueprintImplementableEvent, Category = "HUD")
	void OnTargetCleared();

protected:
	// Cached values
	UPROPERTY(BlueprintReadOnly, Category = "HUD")
	float CachedHealth;

	UPROPERTY(BlueprintReadOnly, Category = "HUD")
	float CachedMaxHealth;

	UPROPERTY(BlueprintReadOnly, Category = "HUD")
	float CachedShield;

	UPROPERTY(BlueprintReadOnly, Category = "HUD")
	float CachedMaxShield;

	UPROPERTY(BlueprintReadOnly, Category = "HUD")
	float CachedEnergy;

	UPROPERTY(BlueprintReadOnly, Category = "HUD")
	float CachedMaxEnergy;

	UPROPERTY(BlueprintReadOnly, Category = "HUD")
	FVector CachedVelocity;

	UPROPERTY(BlueprintReadOnly, Category = "HUD")
	FVector CachedPosition;
};
