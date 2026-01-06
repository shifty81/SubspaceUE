// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "SubspaceInputConfig.generated.h"

/**
 * Configuration data asset for Subspace input actions
 * This defines all the Enhanced Input actions used in the game
 */
UCLASS(BlueprintType)
class SUBSPACEUE_API USubspaceInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	// Movement Actions
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Movement")
	class UInputAction* MoveForwardAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Movement")
	class UInputAction* MoveRightAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Movement")
	class UInputAction* MoveUpAction;

	// Rotation Actions (Keyboard)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Rotation")
	class UInputAction* PitchAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Rotation")
	class UInputAction* YawAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Rotation")
	class UInputAction* RollAction;

	// Look Actions (Mouse)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Look")
	class UInputAction* LookAction;

	// Action Buttons
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Actions")
	class UInputAction* BrakeAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Actions")
	class UInputAction* ToggleControlModeAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Actions")
	class UInputAction* FireWeaponAction;

	// UI Actions
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|UI")
	class UInputAction* OpenGalaxyMapAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|UI")
	class UInputAction* ToggleInventoryAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|UI")
	class UInputAction* ToggleShipBuilderAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|UI")
	class UInputAction* PauseGameAction;

	// Input Mapping Context
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	class UInputMappingContext* DefaultInputMappingContext;
};
