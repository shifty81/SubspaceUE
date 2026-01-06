# NPC and Crew System Design Research

**Project:** SubspaceUE - X4-Style Space Simulation  
**Date:** January 6, 2026  
**Purpose:** Comprehensive research on NPC characters, crew management, and character systems

---

## Executive Summary

This document provides comprehensive research on NPC and crew systems based on:
1. **X4: Foundations** crew mechanics (from X4_SYSTEMS_DESIGN.md)
2. **SubspaceUE** current interior system
3. **Industry best practices** for character management in space games

The goal is to implement functional NPC crew members for ships and stations.

---

## 1. Crew Roles and Types (From X4)

### 1.1 Primary Crew Roles

| Role | Assignment | Skills | Responsibilities |
|------|------------|--------|------------------|
| **Captain** | Ships | Piloting, Management | Command ship, make decisions |
| **Pilot** | Small ships | Piloting | Manual ship control |
| **Service Crew** | Ships/Stations | Engineering | Operations, maintenance, repairs |
| **Marine** | Ships | Boarding, Combat | Boarding actions, ship defense |
| **Manager** | Stations | Management | Run station operations |

### 1.2 Crew Skill System

**Skill Categories (0-5 stars):**

```cpp
USTRUCT(BlueprintType)
struct FCrewSkills
{
    GENERATED_BODY()
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skills")
    int32 PilotingSkill = 0;        // 0-5: Ship control, navigation
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skills")
    int32 BoardingSkill = 0;        // 0-5: Combat, boarding effectiveness
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skills")
    int32 ManagementSkill = 0;      // 0-5: Station/fleet efficiency
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skills")
    int32 EngineeringSkill = 0;     // 0-5: Repairs, system maintenance
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skills")
    int32 MoraleSkill = 0;          // 0-5: Crew morale, leadership
};
```

**Skill Effects:**
- **Piloting** - Affects ship speed, turn rate, weapon accuracy
- **Boarding** - Success rate in boarding actions, combat effectiveness
- **Management** - Station production rate, trading efficiency, profit
- **Engineering** - Repair speed, system efficiency, power management
- **Morale** - Crew happiness, work efficiency, reduces desertion

---

## 2. Crew Member Data Structure

### 2.1 Core Crew Data

```cpp
USTRUCT(BlueprintType)
struct FCrewMember
{
    GENERATED_BODY()
    
    // Identity
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Identity")
    FGuid CrewId;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Identity")
    FString FirstName;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Identity")
    FString LastName;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Identity")
    ECrewGender Gender;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Identity")
    FString Species;               // Human, Teladi, Paranid, etc.
    
    // Role & Assignment
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Role")
    ECrewRole PrimaryRole;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Role")
    AActor* AssignedShip;          // Current ship assignment
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Role")
    AActor* AssignedStation;       // Or station assignment
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Role")
    bool bIsPlayerCrew;            // In player's employ?
    
    // Skills
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skills")
    FCrewSkills Skills;
    
    // Status
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
    int32 Experience = 0;          // Total XP
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
    int32 Level = 1;               // Character level
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
    float Morale = 100.0f;         // 0-100 happiness
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
    float Health = 100.0f;         // 0-100 health
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
    bool bIsBusy;                  // Currently working?
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
    ECrewActivity CurrentActivity; // What they're doing
    
    // Employment
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Employment")
    int32 SalaryPerHour;           // Wage in credits
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Employment")
    float TimeEmployed;            // Hours worked
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Employment")
    int32 HiringCost;              // One-time hire cost
};
```

### 2.2 Crew Activity States

```cpp
UENUM(BlueprintType)
enum class ECrewActivity : uint8
{
    Idle            UMETA(DisplayName = "Idle"),
    Piloting        UMETA(DisplayName = "Piloting Ship"),
    Engineering     UMETA(DisplayName = "Engineering/Repairs"),
    Managing        UMETA(DisplayName = "Managing Station"),
    Boarding        UMETA(DisplayName = "Boarding Action"),
    Training        UMETA(DisplayName = "Skill Training"),
    Resting         UMETA(DisplayName = "Rest/Recreation"),
    Combat          UMETA(DisplayName = "Combat"),
    Trading         UMETA(DisplayName = "Trading"),
    Mining          UMETA(DisplayName = "Mining Operations")
};
```

---

## 3. Crew Management System

### 3.1 Hiring System

**Crew Availability:**
- Crew members are available for hire at stations
- Availability depends on station type and sector
- Higher skill levels are rarer and more expensive
- Faction relations affect crew availability

**Hiring Process:**
```cpp
UCLASS()
class UCrewRecruitmentSystem : public UObject
{
    GENERATED_BODY()
    
public:
    // Get available crew at station
    UFUNCTION(BlueprintCallable, Category = "Crew")
    TArray<FCrewMember> GetAvailableCrewAtStation(AActor* Station);
    
    // Hire a crew member
    UFUNCTION(BlueprintCallable, Category = "Crew")
    bool HireCrewMember(FCrewMember& Crew, int32 PlayerCredits);
    
    // Generate random crew for hiring
    UFUNCTION(BlueprintCallable, Category = "Crew")
    FCrewMember GenerateRandomCrew(ECrewRole Role, int32 MinLevel, int32 MaxLevel);
    
    // Calculate hiring cost based on skills
    UFUNCTION(BlueprintCallable, Category = "Crew")
    int32 CalculateHiringCost(const FCrewMember& Crew);
};
```

**Hiring Cost Formula:**
```cpp
BaseCost = 1000 * Level
SkillBonus = (PilotingSkill + BoardingSkill + ManagementSkill + 
              EngineeringSkill + MoraleSkill) * 500
TotalCost = BaseCost + SkillBonus
```

### 3.2 Assignment System

**Assigning Crew to Ships/Stations:**
```cpp
UCLASS()
class UCrewAssignmentSystem : public UObject
{
    GENERATED_BODY()
    
public:
    // Assign crew to ship
    UFUNCTION(BlueprintCallable, Category = "Crew")
    bool AssignCrewToShip(FCrewMember& Crew, AActor* Ship);
    
    // Assign crew to station
    UFUNCTION(BlueprintCallable, Category = "Crew")
    bool AssignCrewToStation(FCrewMember& Crew, AActor* Station);
    
    // Transfer between ships
    UFUNCTION(BlueprintCallable, Category = "Crew")
    bool TransferCrew(FCrewMember& Crew, AActor* FromShip, AActor* ToShip);
    
    // Promote to new role
    UFUNCTION(BlueprintCallable, Category = "Crew")
    bool PromoteCrewMember(FCrewMember& Crew, ECrewRole NewRole);
    
    // Fire crew member
    UFUNCTION(BlueprintCallable, Category = "Crew")
    void FireCrewMember(FCrewMember& Crew);
    
    // Get crew roster for ship/station
    UFUNCTION(BlueprintCallable, Category = "Crew")
    TArray<FCrewMember> GetCrewRoster(AActor* Asset);
};
```

### 3.3 Training System

**Skill Training:**
- Crew can train at stations with training facilities
- Training costs credits and time
- Increases specific skill by 1 star (max 5)
- Can auto-level skills through experience

```cpp
USTRUCT(BlueprintType)
struct FSeminarInfo
{
    GENERATED_BODY()
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ESkillType SkillToTrain;       // Which skill
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Cost;                    // Training cost
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DurationHours;           // Training time
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 RequiredLevel;           // Minimum level
};

UCLASS()
class UCrewTrainingSystem : public UObject
{
    GENERATED_BODY()
    
public:
    // Enroll crew in training
    UFUNCTION(BlueprintCallable, Category = "Training")
    bool EnrollInSeminar(FCrewMember& Crew, FSeminarInfo Seminar);
    
    // Auto-level skills from experience
    UFUNCTION(BlueprintCallable, Category = "Training")
    void AutoLevelSkills(FCrewMember& Crew);
    
    // Check training progress
    UFUNCTION(BlueprintCallable, Category = "Training")
    float GetTrainingProgress(const FCrewMember& Crew);
};
```

---

## 4. Crew Effects on Gameplay

### 4.1 Ship Performance Modifiers

**Captain/Pilot Effects:**
```cpp
// Applied to ship stats
float SpeedBonus = 1.0f + (PilotingSkill * 0.05f);     // +5% per star
float TurnRateBonus = 1.0f + (PilotingSkill * 0.04f);  // +4% per star
float AccuracyBonus = PilotingSkill * 10.0f;           // +10% per star

ActualSpeed = BaseSpeed * SpeedBonus;
ActualTurnRate = BaseTurnRate * TurnRateBonus;
WeaponAccuracy = BaseAccuracy + AccuracyBonus;
```

**Service Crew Effects:**
```cpp
// Applied to repairs and maintenance
float RepairRateBonus = 1.0f + (EngineeringSkill * 0.1f);   // +10% per star
float PowerEfficiency = 1.0f + (EngineeringSkill * 0.05f);  // +5% per star

RepairRate = BaseRepairRate * RepairRateBonus;
PowerConsumption = BasePower / PowerEfficiency;
```

**Marine Effects:**
```cpp
// Applied in boarding actions
float BoardingSuccessRate = 0.5f + (BoardingSkill * 0.1f);  // +10% per star
float CombatDamage = BaseDamage * (1.0f + BoardingSkill * 0.15f);

SuccessChance = BoardingSuccessRate * CrewCount / EnemyCrewCount;
```

### 4.2 Station Performance Modifiers

**Manager Effects:**
```cpp
// Applied to station operations
float ProductionBonus = 1.0f + (ManagementSkill * 0.08f);   // +8% per star
float TradingEfficiency = 1.0f + (ManagementSkill * 0.1f);  // +10% per star
float ProfitMargin = 1.0f + (ManagementSkill * 0.05f);      // +5% per star

ProductionRate = BaseProduction * ProductionBonus;
TradeVolume = BaseVolume * TradingEfficiency;
Profit = BaseProfit * ProfitMargin;
```

**Workforce Effects:**
```cpp
// Service crew working at station
float StationEfficiency = 1.0f + (AverageEngineeringSkill * 0.05f);
float RepairSpeed = 1.0f + (AverageEngineeringSkill * 0.1f);

AllOperations *= StationEfficiency;
DockedShipRepairs *= RepairSpeed;
```

---

## 5. Crew Morale System

### 5.1 Morale Factors

**Morale affects:**
- Work efficiency (low morale = lower performance)
- Desertion risk (very low morale = crew may leave)
- Skill gain rate (high morale = faster training)

**Morale Modifiers:**

```cpp
USTRUCT(BlueprintType)
struct FMoraleModifiers
{
    GENERATED_BODY()
    
    // Positive
    float BonusFromSalary = 10.0f;          // Paid well
    float BonusFromVictories = 15.0f;       // Won battles
    float BonusFromLeadership = 5.0f;       // Good captain/manager
    float BonusFromFacilities = 10.0f;      // Good living conditions
    
    // Negative
    float PenaltyFromDanger = -20.0f;       // In combat zones
    float PenaltyFromDamage = -15.0f;       // Ship heavily damaged
    float PenaltyFromOverwork = -10.0f;     // Too many hours
    float PenaltyFromLowPay = -25.0f;       // Underpaid
    float PenaltyFromDeaths = -30.0f;       // Crew casualties
};
```

### 5.2 Morale Management

```cpp
UCLASS()
class UCrewMoraleSystem : public UObject
{
    GENERATED_BODY()
    
public:
    // Update morale based on conditions
    UFUNCTION(BlueprintCallable, Category = "Morale")
    void UpdateCrewMorale(FCrewMember& Crew, float DeltaTime);
    
    // Check desertion risk
    UFUNCTION(BlueprintCallable, Category = "Morale")
    bool CheckDesertion(FCrewMember& Crew);
    
    // Get morale-based efficiency multiplier
    UFUNCTION(BlueprintCallable, Category = "Morale")
    float GetEfficiencyMultiplier(float Morale);
    
    // Apply morale modifier
    UFUNCTION(BlueprintCallable, Category = "Morale")
    void ApplyMoraleModifier(FCrewMember& Crew, float Modifier, FString Reason);
};
```

---

## 6. NPC Character Actor Implementation

### 6.1 Base NPC Actor

```cpp
UCLASS()
class SUBSPACEUE_API ANPCCharacter : public ACharacter
{
    GENERATED_BODY()
    
public:
    ANPCCharacter();
    
    // Crew data
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crew")
    FCrewMember CrewData;
    
    // Current location
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Location")
    AActor* CurrentShip;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Location")
    AActor* CurrentStation;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Location")
    FString CurrentRoom;           // Interior cell name
    
    // Visual representation
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
    USkeletalMeshComponent* CharacterMesh;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
    UMaterialInstanceDynamic* CharacterMaterial;
    
    // AI behavior
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    UBehaviorTree* BehaviorTree;
    
    // Interaction
    UFUNCTION(BlueprintCallable, Category = "Interaction")
    void OnInteract(AActor* Interactor);
    
    UFUNCTION(BlueprintCallable, Category = "Interaction")
    FString GetInteractionPrompt();
    
    // Movement
    UFUNCTION(BlueprintCallable, Category = "Movement")
    void MoveToRoom(FString RoomName);
    
    UFUNCTION(BlueprintCallable, Category = "Movement")
    void PerformDuty();
    
protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    
private:
    void UpdateActivity(float DeltaTime);
    void UpdateMorale(float DeltaTime);
    void UpdateSkills(float DeltaTime);
};
```

### 6.2 NPC Spawning System

```cpp
UCLASS()
class UNPCSpawnSystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()
    
public:
    // Spawn NPC at location
    UFUNCTION(BlueprintCallable, Category = "NPC")
    ANPCCharacter* SpawnNPC(const FCrewMember& CrewData, 
                            FVector Location, 
                            FRotator Rotation);
    
    // Spawn crew for ship
    UFUNCTION(BlueprintCallable, Category = "NPC")
    TArray<ANPCCharacter*> SpawnShipCrew(AActor* Ship);
    
    // Spawn personnel for station
    UFUNCTION(BlueprintCallable, Category = "NPC")
    TArray<ANPCCharacter*> SpawnStationPersonnel(AActor* Station);
    
    // Despawn NPC (when fired/killed)
    UFUNCTION(BlueprintCallable, Category = "NPC")
    void DespawnNPC(ANPCCharacter* NPC);
    
    // Get all active NPCs
    UFUNCTION(BlueprintCallable, Category = "NPC")
    TArray<ANPCCharacter*> GetAllNPCs();
};
```

---

## 7. Crew UI Components

### 7.1 Crew Management Widget

```cpp
UCLASS()
class UCrewManagementWidget : public UUserWidget
{
    GENERATED_BODY()
    
public:
    // Display crew roster
    UFUNCTION(BlueprintCallable, Category = "UI")
    void PopulateCrewRoster(AActor* Ship);
    
    // Show crew details
    UFUNCTION(BlueprintCallable, Category = "UI")
    void ShowCrewDetails(const FCrewMember& Crew);
    
    // Hire interface
    UFUNCTION(BlueprintCallable, Category = "UI")
    void ShowHiringInterface(AActor* Station);
    
    // Assignment interface
    UFUNCTION(BlueprintCallable, Category = "UI")
    void ShowAssignmentInterface();
    
    // Training interface
    UFUNCTION(BlueprintCallable, Category = "UI")
    void ShowTrainingInterface();
    
protected:
    // UI elements
    UPROPERTY(meta = (BindWidget))
    class UListView* CrewListView;
    
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* CrewNameText;
    
    UPROPERTY(meta = (BindWidget))
    class UProgressBar* MoraleBar;
    
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* SkillsText;
};
```

### 7.2 Crew List Item Widget

```cpp
UCLASS()
class UCrewListItemWidget : public UUserWidget
{
    GENERATED_BODY()
    
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
    FCrewMember CrewMember;
    
    UFUNCTION(BlueprintImplementableEvent, Category = "UI")
    void UpdateDisplay();
    
protected:
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* NameText;
    
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* RoleText;
    
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* SkillLevelText;
    
    UPROPERTY(meta = (BindWidget))
    class UButton* SelectButton;
};
```

---

## 8. Integration with Ship Interior System

### 8.1 Crew Stations in Interior

**Map Crew to Interior Cells:**
- **Captain** → Cockpit/Bridge
- **Pilot** → Cockpit
- **Service Crew** → Engine Room, Corridors
- **Marines** → Armory, Crew Quarters

**Interior Cell Crew Capacity:**
```cpp
// In FInteriorCell struct (already exists)
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interior Cell")
int32 CrewCapacity = 0;           // How many crew can work here

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interior Cell")
TArray<ANPCCharacter*> AssignedCrew;  // Crew working in this room
```

### 8.2 Crew Visualization

**3D Character Models in Interior:**
- Spawn ANPCCharacter actors in interior cells
- NPCs walk between stations using navmesh
- Perform animations based on activity:
  - Piloting: Sitting at controls
  - Engineering: Using tools on consoles
  - Resting: Sitting/lying in quarters
  - Combat: Standing alert with weapons

---

## 9. Name Generation System

### 9.1 Procedural Name Generation

```cpp
UCLASS()
class UCrewNameGenerator : public UObject
{
    GENERATED_BODY()
    
public:
    // Generate random name
    UFUNCTION(BlueprintCallable, Category = "Names")
    static FString GenerateRandomFirstName(ECrewGender Gender, FString Species);
    
    UFUNCTION(BlueprintCallable, Category = "Names")
    static FString GenerateRandomLastName(FString Species);
    
    UFUNCTION(BlueprintCallable, Category = "Names")
    static FString GenerateFullName(ECrewGender Gender, FString Species);
    
private:
    // Name databases
    static TArray<FString> HumanMaleFirstNames;
    static TArray<FString> HumanFemaleFirstNames;
    static TArray<FString> HumanLastNames;
    
    static TArray<FString> AlienFirstNames;
    static TArray<FString> AlienLastNames;
};
```

**Name Databases:**
- Human male: 100+ first names
- Human female: 100+ first names
- Human surnames: 200+ last names
- Alien species: Unique name patterns per species

---

## 10. Implementation Phases

### Phase 1: Core Crew System (Week 10)

**Objective:** Basic crew data and management

**Tasks:**
1. Create `FCrewMember` struct with all data
2. Create `ECrewRole` and `ECrewActivity` enums
3. Implement `UCrewRecruitmentSystem`
4. Implement `UCrewAssignmentSystem`
5. Create crew database/storage

### Phase 2: Crew Effects & Skills (Week 10)

**Objective:** Crew affects gameplay

**Tasks:**
1. Implement skill-based performance modifiers
2. Create `UCrewMoraleSystem`
3. Implement experience and leveling
4. Create `UCrewTrainingSystem`
5. Apply crew bonuses to ships/stations

### Phase 3: NPC Actors (Week 11)

**Objective:** Visual crew representation

**Tasks:**
1. Create `ANPCCharacter` base actor
2. Implement `UNPCSpawnSystem`
3. Create character meshes and materials
4. Integrate with interior system
5. Add AI behavior trees for crew activities

### Phase 4: UI & Polish (Week 11)

**Objective:** Player crew management interface

**Tasks:**
1. Create `UCrewManagementWidget`
2. Build crew roster display
3. Implement hiring interface
4. Add assignment/transfer UI
5. Create training interface

---

## 11. Testing & Validation

### Test Scenarios

1. **Hiring Crew**
   - Visit station
   - Open hiring interface
   - View available crew
   - Hire crew member
   - Pay hiring cost
   - Crew added to roster

2. **Assigning Crew**
   - Open crew management
   - Select crew member
   - Assign to ship
   - Verify role assignment
   - Check ship performance boost

3. **Skill Training**
   - Select crew for training
   - Enroll in seminar
   - Wait for completion
   - Verify skill increase
   - Check performance improvement

4. **Morale Management**
   - Monitor crew morale
   - Apply morale modifiers
   - Check efficiency changes
   - Handle low morale
   - Prevent desertion

5. **Visual Representation**
   - Enter ship interior
   - See crew at stations
   - Crew performs activities
   - Interact with crew
   - View status information

---

## 12. Advanced Features (Future)

### 12.1 Crew Personalities

**Personality Traits:**
- **Brave** - Better in combat, less morale loss from danger
- **Cautious** - Better navigation, avoids risky situations
- **Greedy** - Wants higher pay, better trader
- **Loyal** - Less likely to desert, morale bonus
- **Skilled** - Learns faster, bonus to all skills

### 12.2 Crew Relationships

**Social Dynamics:**
- Crew members can become friends
- Friends work better together
- Rivalries can develop
- Captain's morale skill affects crew cohesion

### 12.3 Crew Perks & Specializations

**Special Abilities:**
- **Ace Pilot** - +50% piloting effectiveness
- **Master Engineer** - Repairs 2x faster
- **Veteran Marine** - +75% boarding success
- **Trade Expert** - +30% profit margins
- **Navigator** - Reduced travel times

---

## Summary

This research document provides complete foundation for NPC/crew systems in SubspaceUE:

1. **5 Crew Roles** (Captain, Pilot, Service Crew, Marine, Manager)
2. **5 Skill Types** (Piloting, Boarding, Management, Engineering, Morale)
3. **Hiring System** with cost calculation and recruitment
4. **Assignment System** for ships and stations
5. **Training System** with seminars and auto-leveling
6. **Morale System** affecting performance and desertion
7. **Performance Modifiers** for ships and stations
8. **NPC Actors** for visual representation
9. **UI Components** for crew management
10. **Integration** with existing interior system

Implementation can begin immediately following the 4-phase plan aligned with ROADMAP.md Weeks 10-11.

---

**Document Status:** ✅ Complete  
**Last Updated:** January 6, 2026  
**Next Document:** SHIP_INTERIOR_EXPANSION_RESEARCH.md
