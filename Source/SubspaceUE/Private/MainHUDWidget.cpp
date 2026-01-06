// Copyright Epic Games, Inc. All Rights Reserved.

#include "MainHUDWidget.h"

void UMainHUDWidget::UpdateHealth(float CurrentHealth, float MaxHealth)
{
	CachedHealth = CurrentHealth;
	CachedMaxHealth = MaxHealth;

	float HealthPercent = MaxHealth > 0.0f ? (CurrentHealth / MaxHealth) : 0.0f;
	FText HealthText = FText::Format(
		FText::FromString(TEXT("{0} / {1}")),
		FText::AsNumber(FMath::RoundToInt(CurrentHealth)),
		FText::AsNumber(FMath::RoundToInt(MaxHealth))
	);

	OnHealthUpdated(HealthPercent, HealthText);
}

void UMainHUDWidget::UpdateShield(float CurrentShield, float MaxShield)
{
	CachedShield = CurrentShield;
	CachedMaxShield = MaxShield;

	float ShieldPercent = MaxShield > 0.0f ? (CurrentShield / MaxShield) : 0.0f;
	FText ShieldText = FText::Format(
		FText::FromString(TEXT("{0} / {1}")),
		FText::AsNumber(FMath::RoundToInt(CurrentShield)),
		FText::AsNumber(FMath::RoundToInt(MaxShield))
	);

	OnShieldUpdated(ShieldPercent, ShieldText);
}

void UMainHUDWidget::UpdateEnergy(float CurrentEnergy, float MaxEnergy)
{
	CachedEnergy = CurrentEnergy;
	CachedMaxEnergy = MaxEnergy;

	float EnergyPercent = MaxEnergy > 0.0f ? (CurrentEnergy / MaxEnergy) : 0.0f;
	FText EnergyText = FText::Format(
		FText::FromString(TEXT("{0} / {1}")),
		FText::AsNumber(FMath::RoundToInt(CurrentEnergy)),
		FText::AsNumber(FMath::RoundToInt(MaxEnergy))
	);

	OnEnergyUpdated(EnergyPercent, EnergyText);
}

void UMainHUDWidget::UpdateSpeed(float CurrentSpeed, float MaxSpeed)
{
	FText SpeedText = FText::Format(
		FText::FromString(TEXT("Speed: {0} / {1} m/s")),
		FText::AsNumber(FMath::RoundToInt(CurrentSpeed)),
		FText::AsNumber(FMath::RoundToInt(MaxSpeed))
	);

	OnSpeedUpdated(SpeedText);
}

void UMainHUDWidget::UpdateVelocity(const FVector& Velocity)
{
	CachedVelocity = Velocity;

	FText VelocityText = FText::Format(
		FText::FromString(TEXT("Velocity: {0}, {1}, {2}")),
		FText::AsNumber(FMath::RoundToInt(Velocity.X)),
		FText::AsNumber(FMath::RoundToInt(Velocity.Y)),
		FText::AsNumber(FMath::RoundToInt(Velocity.Z))
	);

	OnVelocityUpdated(VelocityText);
}

void UMainHUDWidget::UpdatePosition(const FVector& Position)
{
	CachedPosition = Position;

	FText PositionText = FText::Format(
		FText::FromString(TEXT("Pos: {0}, {1}, {2}")),
		FText::AsNumber(FMath::RoundToInt(Position.X)),
		FText::AsNumber(FMath::RoundToInt(Position.Y)),
		FText::AsNumber(FMath::RoundToInt(Position.Z))
	);

	OnPositionUpdated(PositionText);
}

void UMainHUDWidget::UpdateTarget(const FString& TargetName, float Distance)
{
	FText TargetText = FText::Format(
		FText::FromString(TEXT("Target: {0} ({1}m)")),
		FText::FromString(TargetName),
		FText::AsNumber(FMath::RoundToInt(Distance))
	);

	OnTargetUpdated(TargetText);
}

void UMainHUDWidget::ClearTarget()
{
	OnTargetCleared();
}
