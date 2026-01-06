// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SubspacePlayerController.generated.h"

/**
 * Player Controller for Codename:Subspace
 * 
 * Handles player input, UI management, and camera control
 */
UCLASS()
class SUBSPACEUE_API ASubspacePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ASubspacePlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	/** Toggle between camera mode and ship control mode */
	UFUNCTION(BlueprintCallable, Category = "Subspace|Input")
	void ToggleControlMode();

	/** Open galaxy map */
	UFUNCTION(BlueprintCallable, Category = "Subspace|UI")
	void OpenGalaxyMap();

	/** Toggle inventory UI */
	UFUNCTION(BlueprintCallable, Category = "Subspace|UI")
	void ToggleInventory();

	/** Toggle ship builder UI */
	UFUNCTION(BlueprintCallable, Category = "Subspace|UI")
	void ToggleShipBuilder();

public:
	/** Is player in ship control mode (vs camera mode) */
	UPROPERTY(BlueprintReadWrite, Category = "Subspace|Control")
	bool bIsShipControlMode = true;

	/** Main HUD widget class to spawn */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subspace|UI")
	TSubclassOf<class UMainHUDWidget> MainHUDClass;

	/** Reference to spawned main HUD widget */
	UPROPERTY(BlueprintReadOnly, Category = "Subspace|UI")
	class UMainHUDWidget* MainHUDWidget;

	/** Create and display the main HUD */
	UFUNCTION(BlueprintCallable, Category = "Subspace|UI")
	void CreateMainHUD();

	/** Update HUD with current ship stats */
	UFUNCTION(BlueprintCallable, Category = "Subspace|UI")
	void UpdateHUD();

protected:
	/** Enhanced Input configuration */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	class USubspaceInputConfig* InputConfig;

	/** Bind Enhanced Input actions */
	void SetupEnhancedInput();

	// Enhanced Input action handlers
	void OnMoveForward(const struct FInputActionValue& Value);
	void OnMoveRight(const struct FInputActionValue& Value);
	void OnMoveUp(const struct FInputActionValue& Value);
	void OnPitch(const struct FInputActionValue& Value);
	void OnYaw(const struct FInputActionValue& Value);
	void OnRoll(const struct FInputActionValue& Value);
	void OnLook(const struct FInputActionValue& Value);
	void OnBrake(const struct FInputActionValue& Value);
	void OnToggleControlMode(const struct FInputActionValue& Value);
	void OnOpenGalaxyMap(const struct FInputActionValue& Value);
	void OnToggleInventory(const struct FInputActionValue& Value);
	void OnToggleShipBuilder(const struct FInputActionValue& Value);
	void OnPauseGame(const struct FInputActionValue& Value);
};
