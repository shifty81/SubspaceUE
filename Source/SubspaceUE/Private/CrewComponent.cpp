// Copyright Epic Games, Inc. All Rights Reserved.

#include "CrewComponent.h"
#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"

DEFINE_LOG_CATEGORY_STATIC(LogCrew, Log, All);

UCrewComponent::UCrewComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = 1.0f;  // Update once per second
}

void UCrewComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCrewComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// Update morale
	UpdateMorale(DeltaTime);
	
	// Pay salaries (every hour)
	SalaryTimer += DeltaTime;
	if (SalaryTimer >= 3600.0f)
	{
		SalaryTimer = 0.0f;
		
		// Deduct salaries
		for (const FCrewMember& Crew : CrewMembers)
		{
			Credits -= Crew.SalaryPerHour;
		}
		
		UE_LOG(LogCrew, Verbose, TEXT("Paid crew salaries"));
	}
}

float UCrewComponent::GetAverageMorale() const
{
	if (CrewMembers.Num() == 0)
	{
		return 0.0f;
	}
	
	float TotalMorale = 0.0f;
	for (const FCrewMember& Crew : CrewMembers)
	{
		TotalMorale += Crew.Morale;
	}
	
	return TotalMorale / CrewMembers.Num();
}

TArray<FCrewMember> UCrewComponent::GetCrewByRole(ECrewRole Role) const
{
	TArray<FCrewMember> Result;
	for (const FCrewMember& Crew : CrewMembers)
	{
		if (Crew.Role == Role)
		{
			Result.Add(Crew);
		}
	}
	return Result;
}

bool UCrewComponent::GetCaptain(FCrewMember& OutCaptain)
{
	for (FCrewMember& Crew : CrewMembers)
	{
		if (Crew.Role == ECrewRole::Captain)
		{
			OutCaptain = Crew;
			return true;
		}
	}
	return false;
}

// ===== Hiring & Management =====

bool UCrewComponent::HireCrewMember(const FCrewMember& NewCrew)
{
	if (IsCrewFull())
	{
		UE_LOG(LogCrew, Warning, TEXT("Cannot hire: Crew is full (%d/%d)"), GetCrewCount(), MaxCrew);
		return false;
	}
	
	if (Credits < NewCrew.HiringCost)
	{
		UE_LOG(LogCrew, Warning, TEXT("Cannot hire: Insufficient credits (%d/%d)"), Credits, NewCrew.HiringCost);
		return false;
	}
	
	Credits -= NewCrew.HiringCost;
	CrewMembers.Add(NewCrew);
	
	UE_LOG(LogCrew, Log, TEXT("Hired crew: %s (%s) for %d credits"), 
		*NewCrew.Name, 
		*UEnum::GetValueAsString(NewCrew.Role),
		NewCrew.HiringCost);
	
	return true;
}

bool UCrewComponent::FireCrewMember(int32 Index)
{
	if (!CrewMembers.IsValidIndex(Index))
	{
		return false;
	}
	
	FCrewMember& Crew = CrewMembers[Index];
	UE_LOG(LogCrew, Log, TEXT("Fired crew: %s"), *Crew.Name);
	
	CrewMembers.RemoveAt(Index);
	return true;
}

bool UCrewComponent::TransferCrewMember(int32 Index, AActor* TargetShip)
{
	if (!CrewMembers.IsValidIndex(Index) || !TargetShip)
	{
		return false;
	}
	
	UCrewComponent* TargetCrew = TargetShip->FindComponentByClass<UCrewComponent>();
	if (!TargetCrew)
	{
		UE_LOG(LogCrew, Warning, TEXT("Target ship has no crew component"));
		return false;
	}
	
	if (TargetCrew->IsCrewFull())
	{
		UE_LOG(LogCrew, Warning, TEXT("Target ship crew is full"));
		return false;
	}
	
	FCrewMember TransferredCrew = CrewMembers[Index];
	TransferredCrew.AssignedShip = TargetShip;
	
	if (TargetCrew->CrewMembers.Add(TransferredCrew) >= 0)
	{
		CrewMembers.RemoveAt(Index);
		UE_LOG(LogCrew, Log, TEXT("Transferred crew: %s to %s"), *TransferredCrew.Name, *TargetShip->GetName());
		return true;
	}
	
	return false;
}

bool UCrewComponent::PromoteCrewMember(int32 Index, ECrewRole NewRole)
{
	if (!CrewMembers.IsValidIndex(Index))
	{
		return false;
	}
	
	FCrewMember& Crew = CrewMembers[Index];
	ECrewRole OldRole = Crew.Role;
	Crew.Role = NewRole;
	
	UE_LOG(LogCrew, Log, TEXT("Promoted %s from %s to %s"), 
		*Crew.Name,
		*UEnum::GetValueAsString(OldRole),
		*UEnum::GetValueAsString(NewRole));
	
	return true;
}

TArray<FCrewMember> UCrewComponent::GenerateAvailableCrew(int32 Count, int32 MinSkill, int32 MaxSkill)
{
	TArray<FCrewMember> Available;
	for (int32 i = 0; i < Count; ++i)
	{
		Available.Add(GenerateRandomCrew(MinSkill, MaxSkill));
	}
	return Available;
}

// ===== Training =====

bool UCrewComponent::TrainCrewMember(int32 Index, ESeminarType Type)
{
	if (!CrewMembers.IsValidIndex(Index))
	{
		return false;
	}
	
	int32 Cost = GetTrainingCost(Type);
	if (Credits < Cost)
	{
		UE_LOG(LogCrew, Warning, TEXT("Insufficient credits for training: %d/%d"), Credits, Cost);
		return false;
	}
	
	FCrewMember& Crew = CrewMembers[Index];
	Credits -= Cost;
	
	// Increase skill based on seminar type
	switch (Type)
	{
	case ESeminarType::Piloting:
		Crew.PilotingSkill = FMath::Min(5, Crew.PilotingSkill + 1);
		break;
	case ESeminarType::Boarding:
		Crew.BoardingSkill = FMath::Min(5, Crew.BoardingSkill + 1);
		break;
	case ESeminarType::Management:
		Crew.ManagementSkill = FMath::Min(5, Crew.ManagementSkill + 1);
		break;
	case ESeminarType::Engineering:
		Crew.EngineeringSkill = FMath::Min(5, Crew.EngineeringSkill + 1);
		break;
	case ESeminarType::Morale:
		Crew.MoraleSkill = FMath::Min(5, Crew.MoraleSkill + 1);
		break;
	}
	
	UE_LOG(LogCrew, Log, TEXT("Trained %s in %s"), *Crew.Name, *UEnum::GetValueAsString(Type));
	return true;
}

int32 UCrewComponent::GetTrainingCost(ESeminarType Type) const
{
	// Base cost increases with skill level
	return 5000;
}

void UCrewComponent::AutoLevelSkills(int32 Index)
{
	if (!CrewMembers.IsValidIndex(Index))
	{
		return;
	}
	
	FCrewMember& Crew = CrewMembers[Index];
	
	// Auto-level skills based on experience
	// Every 1000 XP grants skill improvements
	int32 SkillPoints = Crew.Experience / 1000;
	
	// Distribute skill points based on role
	switch (Crew.Role)
	{
	case ECrewRole::Captain:
		Crew.ManagementSkill = FMath::Min(5, SkillPoints / 2);
		Crew.PilotingSkill = FMath::Min(5, SkillPoints / 3);
		break;
	case ECrewRole::Pilot:
		Crew.PilotingSkill = FMath::Min(5, SkillPoints);
		break;
	case ECrewRole::ServiceCrew:
		Crew.EngineeringSkill = FMath::Min(5, SkillPoints / 2);
		break;
	case ECrewRole::Marine:
		Crew.BoardingSkill = FMath::Min(5, SkillPoints);
		break;
	case ECrewRole::Manager:
		Crew.ManagementSkill = FMath::Min(5, SkillPoints);
		break;
	}
}

// ===== Experience & Skills =====

void UCrewComponent::AwardExperience(int32 Index, int32 XP)
{
	if (!CrewMembers.IsValidIndex(Index))
	{
		return;
	}
	
	FCrewMember& Crew = CrewMembers[Index];
	Crew.Experience += XP;
	
	// Auto-level if enabled
	AutoLevelSkills(Index);
}

void UCrewComponent::AwardExperienceToAll(int32 XP)
{
	for (int32 i = 0; i < CrewMembers.Num(); ++i)
	{
		AwardExperience(i, XP);
	}
}

float UCrewComponent::GetSkillBonus(ECrewRole Role) const
{
	TArray<FCrewMember> RoleCrew = GetCrewByRole(Role);
	if (RoleCrew.Num() == 0)
	{
		return 0.0f;
	}
	
	int32 TotalSkill = 0;
	for (const FCrewMember& Crew : RoleCrew)
	{
		switch (Role)
		{
		case ECrewRole::Pilot:
			TotalSkill += Crew.PilotingSkill;
			break;
		case ECrewRole::Manager:
			TotalSkill += Crew.ManagementSkill;
			break;
		case ECrewRole::ServiceCrew:
			TotalSkill += Crew.EngineeringSkill;
			break;
		case ECrewRole::Marine:
			TotalSkill += Crew.BoardingSkill;
			break;
		default:
			break;
		}
	}
	
	// Average skill converted to 0-1 bonus (5 stars = 1.0 bonus)
	return (float)TotalSkill / (RoleCrew.Num() * 5);
}

float UCrewComponent::GetPilotingEffectiveness() const
{
	float Bonus = GetSkillBonus(ECrewRole::Pilot);
	float MoraleModifier = GetAverageMorale() / 100.0f;
	return FMath::Clamp(0.5f + (Bonus * 0.5f) * MoraleModifier, 0.5f, 1.5f);
}

float UCrewComponent::GetManagementEffectiveness() const
{
	float Bonus = GetSkillBonus(ECrewRole::Manager);
	float MoraleModifier = GetAverageMorale() / 100.0f;
	return FMath::Clamp(0.5f + (Bonus * 0.5f) * MoraleModifier, 0.5f, 1.5f);
}

float UCrewComponent::GetEngineeringEffectiveness() const
{
	float Bonus = GetSkillBonus(ECrewRole::ServiceCrew);
	float MoraleModifier = GetAverageMorale() / 100.0f;
	return FMath::Clamp(0.5f + (Bonus * 0.5f) * MoraleModifier, 0.5f, 1.5f);
}

// ===== Morale =====

void UCrewComponent::UpdateMorale(float DeltaTime)
{
	// Morale gradually normalizes to 70
	float TargetMorale = 70.0f;
	float ChangeRate = 1.0f * DeltaTime;  // 1 point per second
	
	for (FCrewMember& Crew : CrewMembers)
	{
		if (Crew.Morale < TargetMorale)
		{
			Crew.Morale = FMath::Min(TargetMorale, Crew.Morale + ChangeRate);
		}
		else if (Crew.Morale > TargetMorale)
		{
			Crew.Morale = FMath::Max(TargetMorale, Crew.Morale - ChangeRate);
		}
	}
}

void UCrewComponent::BoostMorale(float Amount)
{
	for (FCrewMember& Crew : CrewMembers)
	{
		Crew.Morale = FMath::Clamp(Crew.Morale + Amount, 0.0f, 100.0f);
	}
	
	UE_LOG(LogCrew, Log, TEXT("Boosted morale by %.1f"), Amount);
}

void UCrewComponent::ReduceMorale(float Amount)
{
	for (FCrewMember& Crew : CrewMembers)
	{
		Crew.Morale = FMath::Clamp(Crew.Morale - Amount, 0.0f, 100.0f);
	}
	
	UE_LOG(LogCrew, Log, TEXT("Reduced morale by %.1f"), Amount);
}

// ===== Boarding Actions =====

int32 UCrewComponent::GetBoardingStrength() const
{
	TArray<FCrewMember> Marines = GetCrewByRole(ECrewRole::Marine);
	
	int32 Strength = 0;
	for (const FCrewMember& Marine : Marines)
	{
		// Each marine contributes based on boarding skill and morale
		float MoraleModifier = Marine.Morale / 100.0f;
		Strength += FMath::RoundToInt((Marine.BoardingSkill + 1) * 10 * MoraleModifier);
	}
	
	return Strength;
}

bool UCrewComponent::BoardShip(AActor* TargetShip)
{
	if (!TargetShip)
	{
		return false;
	}
	
	UCrewComponent* TargetCrew = TargetShip->FindComponentByClass<UCrewComponent>();
	if (!TargetCrew)
	{
		UE_LOG(LogCrew, Warning, TEXT("Target ship has no crew"));
		return false;
	}
	
	int32 OurStrength = GetBoardingStrength();
	int32 TheirStrength = TargetCrew->GetBoardingStrength();
	
	UE_LOG(LogCrew, Log, TEXT("Boarding action: Our strength %d vs Their strength %d"), 
		OurStrength, TheirStrength);
	
	// Simple boarding resolution
	if (OurStrength > TheirStrength)
	{
		// Success - reduce target crew
		if (TargetCrew->CrewMembers.Num() > 0)
		{
			int32 Casualties = FMath::Min(3, TargetCrew->CrewMembers.Num());
			for (int32 i = 0; i < Casualties; ++i)
			{
				TargetCrew->CrewMembers.RemoveAt(0);
			}
		}
		
		// Reduce our morale slightly
		ReduceMorale(10.0f);
		
		UE_LOG(LogCrew, Log, TEXT("Boarding successful!"));
		return true;
	}
	else
	{
		// Failure - lose some of our crew
		if (CrewMembers.Num() > 0)
		{
			int32 Casualties = FMath::Min(2, CrewMembers.Num());
			for (int32 i = 0; i < Casualties; ++i)
			{
				CrewMembers.RemoveAt(0);
			}
		}
		
		ReduceMorale(20.0f);
		
		UE_LOG(LogCrew, Warning, TEXT("Boarding failed!"));
		return false;
	}
}

bool UCrewComponent::DefendAgainstBoarding()
{
	// Called when being boarded
	ReduceMorale(15.0f);
	return GetBoardingStrength() > 0;
}

// ===== Protected Helper Methods =====

FString UCrewComponent::GenerateRandomName() const
{
	TArray<FString> FirstNames = {
		TEXT("John"), TEXT("Jane"), TEXT("Alex"), TEXT("Maria"), TEXT("David"),
		TEXT("Sarah"), TEXT("Michael"), TEXT("Emma"), TEXT("Robert"), TEXT("Lisa"),
		TEXT("James"), TEXT("Anna"), TEXT("William"), TEXT("Sofia"), TEXT("Thomas")
	};
	
	TArray<FString> LastNames = {
		TEXT("Smith"), TEXT("Johnson"), TEXT("Williams"), TEXT("Brown"), TEXT("Jones"),
		TEXT("Garcia"), TEXT("Miller"), TEXT("Davis"), TEXT("Rodriguez"), TEXT("Martinez"),
		TEXT("Chen"), TEXT("Kim"), TEXT("Patel"), TEXT("Singh"), TEXT("O'Brien")
	};
	
	int32 FirstIndex = FMath::RandRange(0, FirstNames.Num() - 1);
	int32 LastIndex = FMath::RandRange(0, LastNames.Num() - 1);
	
	return FirstNames[FirstIndex] + TEXT(" ") + LastNames[LastIndex];
}

FCrewMember UCrewComponent::GenerateRandomCrew(int32 MinSkill, int32 MaxSkill) const
{
	FCrewMember Crew;
	Crew.Name = GenerateRandomName();
	
	// Random role
	int32 RoleIndex = FMath::RandRange(0, 4);
	Crew.Role = (ECrewRole)RoleIndex;
	
	// Random skills
	Crew.PilotingSkill = FMath::RandRange(MinSkill, MaxSkill);
	Crew.BoardingSkill = FMath::RandRange(MinSkill, MaxSkill);
	Crew.ManagementSkill = FMath::RandRange(MinSkill, MaxSkill);
	Crew.EngineeringSkill = FMath::RandRange(MinSkill, MaxSkill);
	Crew.MoraleSkill = FMath::RandRange(MinSkill, MaxSkill);
	
	// Initial state
	Crew.Experience = 0;
	Crew.Morale = FMath::FRandRange(60.0f, 90.0f);
	Crew.bIsBusy = false;
	
	// Calculate hiring cost based on skills
	int32 TotalSkills = Crew.PilotingSkill + Crew.BoardingSkill + Crew.ManagementSkill + 
	                    Crew.EngineeringSkill + Crew.MoraleSkill;
	Crew.HiringCost = 1000 + (TotalSkills * 200);
	Crew.SalaryPerHour = 50 + (TotalSkills * 10);
	
	return Crew;
}

int32 UCrewComponent::CalculateSkillLevel(int32 Experience) const
{
	// 1000 XP per skill level, max 5 stars
	return FMath::Min(5, Experience / 1000);
}
