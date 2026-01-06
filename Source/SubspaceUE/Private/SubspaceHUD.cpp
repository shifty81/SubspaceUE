// Copyright Epic Games, Inc. All Rights Reserved.

#include "SubspaceHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Font.h"
#include "GameFramework/PlayerController.h"
#include "SubspacePlayerPawn.h"
#include "Kismet/GameplayStatics.h"

ASubspaceHUD::ASubspaceHUD()
{
	// Load default font
	static ConstructorHelpers::FObjectFinder<UFont> FontObj(TEXT("/Engine/EngineFonts/Roboto"));
	if (FontObj.Succeeded())
	{
		HUDFont = FontObj.Object;
	}
}

void ASubspaceHUD::DrawHUD()
{
	Super::DrawHUD();

	if (!Canvas || !HUDFont)
	{
		return;
	}

	// Get player pawn
	APlayerController* PC = GetOwningPlayerController();
	if (!PC)
	{
		return;
	}

	ASubspacePlayerPawn* PlayerPawn = Cast<ASubspacePlayerPawn>(PC->GetPawn());
	if (!PlayerPawn)
	{
		return;
	}

	// Set drawing color
	FLinearColor TextColor = FLinearColor::Green;

	// Draw title
	FString TitleText = TEXT("CODENAME: SUBSPACE - UE5 Alpha");
	float XPos = 50.0f;
	float YPos = 50.0f;
	DrawText(TitleText, TextColor, XPos, YPos, HUDFont, 1.5f);

	YPos += 60.0f;

	// Draw ship status
	FVector Velocity = PlayerPawn->Velocity;
	float Speed = Velocity.Size();
	FString SpeedText = FString::Printf(TEXT("Speed: %.1f m/s"), Speed);
	DrawText(SpeedText, TextColor, XPos, YPos, HUDFont, 1.2f);
	
	YPos += 40.0f;

	// Draw position
	FVector Position = PlayerPawn->GetActorLocation();
	FString PosText = FString::Printf(TEXT("Position: X=%.1f Y=%.1f Z=%.1f"), Position.X, Position.Y, Position.Z);
	DrawText(PosText, TextColor, XPos, YPos, HUDFont, 1.0f);
	
	YPos += 35.0f;

	// Draw velocity vector
	FString VelText = FString::Printf(TEXT("Velocity: X=%.1f Y=%.1f Z=%.1f"), Velocity.X, Velocity.Y, Velocity.Z);
	DrawText(VelText, TextColor, XPos, YPos, HUDFont, 1.0f);
	
	YPos += 35.0f;

	// Draw angular velocity
	FVector AngVel = PlayerPawn->AngularVelocity;
	FString AngVelText = FString::Printf(TEXT("Angular Vel: X=%.1f Y=%.1f Z=%.1f"), AngVel.X, AngVel.Y, AngVel.Z);
	DrawText(AngVelText, TextColor, XPos, YPos, HUDFont, 1.0f);

	// Draw controls at bottom
	YPos = Canvas->SizeY - 250.0f;
	DrawText(TEXT("=== CONTROLS ==="), FLinearColor::Yellow, XPos, YPos, HUDFont, 1.2f);
	YPos += 40.0f;
	DrawText(TEXT("W/S - Forward/Backward | A/D - Strafe | Space/Shift - Up/Down"), FLinearColor::White, XPos, YPos, HUDFont, 1.0f);
	YPos += 30.0f;
	DrawText(TEXT("Arrow Keys - Pitch/Yaw | Q/E - Roll | B - Emergency Brake"), FLinearColor::White, XPos, YPos, HUDFont, 1.0f);
	
	// Draw crosshair in center
	float CenterX = Canvas->SizeX * 0.5f;
	float CenterY = Canvas->SizeY * 0.5f;
	float CrosshairSize = 10.0f;
	
	DrawLine(CenterX - CrosshairSize, CenterY, CenterX + CrosshairSize, CenterY, FLinearColor::Green, 2.0f);
	DrawLine(CenterX, CenterY - CrosshairSize, CenterX, CenterY + CrosshairSize, FLinearColor::Green, 2.0f);
}
