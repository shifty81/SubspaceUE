// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SubspaceHUD.generated.h"

/**
 * HUD for displaying game information
 */
UCLASS()
class SUBSPACEUE_API ASubspaceHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	ASubspaceHUD();

	/** Called every frame to draw the HUD */
	virtual void DrawHUD() override;

protected:
	/** Font for rendering text */
	UPROPERTY()
	UFont* HUDFont;
};
