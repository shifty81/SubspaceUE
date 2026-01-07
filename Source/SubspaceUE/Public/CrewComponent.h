// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CrewComponent.generated.h"

/**
 * Crew roles (X4-inspired)
 */
UENUM(BlueprintType)
enum class ECrewRole : uint8
{
	Captain UMETA(DisplayName = "Captain"),         // Ship commander
	Pilot UMETA(DisplayName = "Pilot"),            // For smaller ships
	ServiceCrew UMETA(DisplayName = "Service Crew"), // Engineering/operations
	Marine UMETA(DisplayName = "Marine"),          // Boarding/defense
	Manager UMETA(DisplayName = "Manager")         // Station management
};

/**
 * Crew member data
 */
USTRUCT(BlueprintType)
struct FCrewMember
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crew")
	FString Name = TEXT("Unknown Crew");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crew")
	ECrewRole Role = ECrewRole::ServiceCrew;

	// Skills (0-5 stars)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crew|Skills")
	int32 PilotingSkill = 0;  // Ship maneuvering

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crew|Skills")
	int32 BoardingSkill = 0;  // Boarding actions

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crew|Skills")
	int32 ManagementSkill = 0;  // Station/fleet management

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crew|Skills")
	int32 EngineeringSkill = 0;  // Repair/maintenance

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crew|Skills")
	int32 MoraleSkill = 0;  // Crew morale boost

	// Status
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crew|Status")
	int32 Experience = 0;  // Total XP earned

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crew|Status")
	float Morale = 100.0f;  // 0-100

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crew|Status")
	bool bIsBusy = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crew|Status")
	AActor* AssignedShip = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crew|Status")
	AActor* AssignedStation = nullptr;

	// Traits (optional special abilities)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crew|Traits")
	TArray<FString> Traits;

	// Hiring cost
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crew")
	int32 HiringCost = 1000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crew")
	int32 SalaryPerHour = 50;
};

/**
 * Seminar/training type
 */
UENUM(BlueprintType)
enum class ESeminarType : uint8
{
	Piloting UMETA(DisplayName = "Piloting"),
	Boarding UMETA(DisplayName = "Boarding"),
	Management UMETA(DisplayName = "Management"),
	Engineering UMETA(DisplayName = "Engineering"),
	Morale UMETA(DisplayName = "Morale")
};

/**
 * Training seminar data
 */
USTRUCT(BlueprintType)
struct FTrainingSeminar
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Training")
	ESeminarType Type = ESeminarType::Piloting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Training")
	int32 Cost = 5000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Training")
	float Duration = 3600.0f;  // Seconds

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Training")
	int32 SkillGain = 1;  // Stars gained
};

/**
 * Component that manages ship crew
 * X4-style crew system with skills, morale, and assignments
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SUBSPACEUE_API UCrewComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCrewComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** All crew members on this ship/station */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crew")
	TArray<FCrewMember> CrewMembers;

	/** Maximum crew capacity */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crew")
	int32 MaxCrew = 10;

	/** Minimum crew required for operation */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crew")
	int32 MinCrew = 1;

	/** Credits available for hiring */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crew")
	int32 Credits = 10000;

	/** Get current crew count */
	UFUNCTION(BlueprintCallable, Category = "Crew")
	int32 GetCrewCount() const { return CrewMembers.Num(); }

	/** Check if has minimum crew */
	UFUNCTION(BlueprintCallable, Category = "Crew")
	bool HasMinimumCrew() const { return CrewMembers.Num() >= MinCrew; }

	/** Check if crew is full */
	UFUNCTION(BlueprintCallable, Category = "Crew")
	bool IsCrewFull() const { return CrewMembers.Num() >= MaxCrew; }

	/** Get average morale */
	UFUNCTION(BlueprintCallable, Category = "Crew")
	float GetAverageMorale() const;

	/** Get crew by role */
	UFUNCTION(BlueprintCallable, Category = "Crew")
	TArray<FCrewMember> GetCrewByRole(ECrewRole Role) const;

	/** Get captain - returns true if captain exists and fills OutCaptain */
	UFUNCTION(BlueprintCallable, Category = "Crew")
	bool GetCaptain(FCrewMember& OutCaptain);

	// ===== Hiring & Management =====

	/** Hire a crew member */
	UFUNCTION(BlueprintCallable, Category = "Crew")
	bool HireCrewMember(const FCrewMember& NewCrew);

	/** Fire a crew member */
	UFUNCTION(BlueprintCallable, Category = "Crew")
	bool FireCrewMember(int32 Index);

	/** Transfer crew member to another ship */
	UFUNCTION(BlueprintCallable, Category = "Crew")
	bool TransferCrewMember(int32 Index, AActor* TargetShip);

	/** Promote crew member to role */
	UFUNCTION(BlueprintCallable, Category = "Crew")
	bool PromoteCrewMember(int32 Index, ECrewRole NewRole);

	/** Generate available crew at station */
	UFUNCTION(BlueprintCallable, Category = "Crew")
	TArray<FCrewMember> GenerateAvailableCrew(int32 Count, int32 MinSkill = 0, int32 MaxSkill = 3);

	// ===== Training =====

	/** Train crew member in specific skill */
	UFUNCTION(BlueprintCallable, Category = "Crew")
	bool TrainCrewMember(int32 Index, ESeminarType Type);

	/** Get training cost for seminar */
	UFUNCTION(BlueprintCallable, Category = "Crew")
	int32 GetTrainingCost(ESeminarType Type) const;

	/** Auto-level skills based on experience */
	UFUNCTION(BlueprintCallable, Category = "Crew")
	void AutoLevelSkills(int32 Index);

	// ===== Experience & Skills =====

	/** Award experience to crew member */
	UFUNCTION(BlueprintCallable, Category = "Crew")
	void AwardExperience(int32 Index, int32 XP);

	/** Award experience to all crew */
	UFUNCTION(BlueprintCallable, Category = "Crew")
	void AwardExperienceToAll(int32 XP);

	/** Get skill bonus for role */
	UFUNCTION(BlueprintCallable, Category = "Crew")
	float GetSkillBonus(ECrewRole Role) const;

	/** Get piloting effectiveness (0-1 multiplier) */
	UFUNCTION(BlueprintCallable, Category = "Crew")
	float GetPilotingEffectiveness() const;

	/** Get management effectiveness (0-1 multiplier) */
	UFUNCTION(BlueprintCallable, Category = "Crew")
	float GetManagementEffectiveness() const;

	/** Get engineering effectiveness (0-1 multiplier) */
	UFUNCTION(BlueprintCallable, Category = "Crew")
	float GetEngineeringEffectiveness() const;

	// ===== Morale =====

	/** Update morale for all crew */
	UFUNCTION(BlueprintCallable, Category = "Crew")
	void UpdateMorale(float DeltaTime);

	/** Boost morale */
	UFUNCTION(BlueprintCallable, Category = "Crew")
	void BoostMorale(float Amount);

	/** Reduce morale */
	UFUNCTION(BlueprintCallable, Category = "Crew")
	void ReduceMorale(float Amount);

	// ===== Boarding Actions =====

	/** Get total boarding strength */
	UFUNCTION(BlueprintCallable, Category = "Crew")
	int32 GetBoardingStrength() const;

	/** Execute boarding action */
	UFUNCTION(BlueprintCallable, Category = "Crew")
	bool BoardShip(AActor* TargetShip);

	/** Defend against boarding */
	UFUNCTION(BlueprintCallable, Category = "Crew")
	bool DefendAgainstBoarding();

protected:
	/** Generate random crew name */
	FString GenerateRandomName() const;

	/** Generate random crew member */
	FCrewMember GenerateRandomCrew(int32 MinSkill = 0, int32 MaxSkill = 3) const;

	/** Calculate skill level from experience */
	int32 CalculateSkillLevel(int32 Experience) const;

	/** Salary payment timer */
	float SalaryTimer = 0.0f;
};
