// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCManager.h"
#include "Moonshot/MoonshotGameInstanceBase.h"
#include "Moonshot/MoonshotGameModeBase.h"
#include "Components/BillboardComponent.h"
#include "Engine/DataTable.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "Moonshot/LevelActors/NPCSpawnPoint.h"
#include "Moonshot/LevelActors/MobsterAttackBox.h"

// Sets default values
ANPCManager::ANPCManager()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    //Setup billboard 
    BillboardComponent = CreateDefaultSubobject<UBillboardComponent>(TEXT("BillboardComponent"));
    RootComponent = BillboardComponent;

    static ConstructorHelpers::FObjectFinder<UDataTable> DayTableObj(
        TEXT("DataTable'/Game/Data/DT_DayData.DT_DayData'"));
    if (DayTableObj.Succeeded())
    {
        DayDataTable = DayTableObj.Object;
    }
}

// Called when the game starts or when spawned
void ANPCManager::BeginPlay()
{
    Super::BeginPlay();

    GameInstance = Cast<UMoonshotGameInstanceBase>(GetGameInstance());
    if (GetWorld())
    {
        GameMode = Cast<AMoonshotGameModeBase>(GetWorld()->GetAuthGameMode());
        GetSpawnPoints();
    }

    if (GameInstance)
    {
        GetBarSpots();
        GameInstance->NPCManager = this;
        SetDayData(GameInstance->CurrentDay);
        BeginDay();
    }
}

AMobsterAttackBox* ANPCManager::GetAttackBox() const
{
    for(TActorIterator<AMobsterAttackBox> ActorIterator(GetWorld()); ActorIterator; ++ActorIterator)
        if(ActorIterator)
            return Cast<AMobsterAttackBox>(*ActorIterator);

    return nullptr;
}


void ANPCManager::SetDayData(int32 Day)
{
    ClearDayData();
    CurrentSetDay = Day;
    static const FString DayDataText(TEXT("DayDataText"));
    FName RowName = FName(*FString::FromInt(Day));
    DayData = *DayDataTable->FindRow<FDayData>(RowName, DayDataText, true);
}

TArray<ABarSpot*> ANPCManager::GetBarSpots()
{
    for (TActorIterator<ABarSpot> ActorIterator(GetWorld()); ActorIterator; ++ActorIterator)
    {
        if (ActorIterator)
        {
            ABarSpot* BarSpot = Cast<ABarSpot>(*ActorIterator);

            BarSpots.AddUnique(BarSpot);
        }
    }

    return BarSpots;
}

void ANPCManager::GetSpawnPoints()
{
    for (TActorIterator<ANPCSpawnPoint> ActorIterator(GetWorld()); ActorIterator; ++ActorIterator)
    {
        if (ActorIterator)
        {
            ANPCSpawnPoint* SpawnPoint = Cast<ANPCSpawnPoint>(*ActorIterator);

            SpawnPoint->AddPointToManager(this);
        }
    }
}

bool ANPCManager::AllStoolsFilled()
{
    if(BarSpots.Num() > 0)
    {
        for (ABarSpot* BarSpot : BarSpots)
        {
            if(!BarSpot->bOccupied)
            {
                return false;
            }
        }
    }

    return true;
}

void ANPCManager::SpawnNPC()
{
    if(DayData.SpawnerData.CurrentlySpawnedNPCs.Contains(nullptr))
    {
        DayData.SpawnerData.CurrentlySpawnedNPCs.Remove(nullptr);
    }
    
    if (DayData.SpawnerData.CurrentlySpawnedNPCs.Num() < DayData.SpawnerData.MaxSpawnsAllowed)
    {
        DayData.SpawnerData.SpawnWeight.ChangeWeight(DayData.SpawnerData.LastSpawnedNPC);
        float RandomWeight = FMath::RandRange(0.0f, 10.0f);
        
        if(AllStoolsFilled())
        {
            if (RandomWeight <= DayData.SpawnerData.SpawnWeight.MobWeight)
            {
                if(GameInstance->CurrentDay <= 1)
                {
                    return;
                }
                SpawnMobster();
                DayData.SpawnerData.LastSpawnedNPC = ENPCType::NPC_Mobster;
                DayData.SpawnerData.SpawnCount++;            
            }
            
        }else
        {
            if (RandomWeight <= DayData.SpawnerData.SpawnWeight.MobWeight)
            {
                if(GameInstance->CurrentDay <= 1)
                {
                    return;
                }
                SpawnMobster();
                DayData.SpawnerData.LastSpawnedNPC = ENPCType::NPC_Mobster;
                DayData.SpawnerData.SpawnCount++;            
            }
            else
            {
                SpawnCustomer();
                DayData.SpawnerData.LastSpawnedNPC = ENPCType::NPC_Customer;
                DayData.SpawnerData.SpawnCount++;            
            }
        }

    }


    if (DayData.SpawnerData.CurrentlySpawnedNPCs.Num() > DayData.SpawnerData.MaxSpawnsAllowed)
    {
        GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
    }
}

float ANPCManager::GetSpawnTimeVariance(float Variant)
{
    float RandomFloat = FMath::RandRange((Variant * -1), Variant);

    return DayData.SpawnerData.SpawnInterval + RandomFloat;
}

void ANPCManager::ClearDayData()
{
    if (GetWorldTimerManager().IsTimerActive(SpawnTimerHandle))
    {
        GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
    }
}

void ANPCManager::RemoveNPC(ANPCBase* RemovedNPC)
{
    if (RemovedNPC)
    {
        DayData.SpawnerData.CurrentlySpawnedNPCs.Remove(RemovedNPC);
    }else
    {
        DayData.SpawnerData.CurrentlySpawnedNPCs.Remove(nullptr);
    }

    if (DayData.SpawnerData.CurrentlySpawnedNPCs.Num() < DayData.SpawnerData.MaxSpawnsAllowed)
    {
        GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &ANPCManager::SpawnNPC,
                                        GetSpawnTimeVariance(DayData.SpawnerData.IntervalVariance), true);
    }
}


float ANPCManager::GetRemainingDayTime()
{
    if (GetWorldTimerManager().IsTimerActive(DayTimerHandle))
    {
        return GetWorldTimerManager().GetTimerRemaining(DayTimerHandle);
    }
    return 0.0f;
}

void ANPCManager::EndDay()
{
    // GameInstance->CurrentDay += 1;
    GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
}

void ANPCManager::BeginDay()
{
    if (GetWorld())
    {        
        GetWorldTimerManager().SetTimer(DayTimerHandle, this, &ANPCManager::EndDay, DayData.TimerValue, false);
        GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &ANPCManager::SpawnNPC,
                                        GetSpawnTimeVariance(DayData.SpawnerData.IntervalVariance), true);
    }
}


void ANPCManager::AddNPCToArray(ANPCBase* NPC)
{
    DayData.SpawnerData.CurrentlySpawnedNPCs.AddUnique(NPC);
}


FVector ANPCManager::GetRandomSpawnPoint()
{
    if (SpawnPoints.Num() > 0)
    {
        return SpawnPoints[FMath::RandRange(0, SpawnPoints.Num() - 1)]->GetActorLocation();
    }

    return GetActorLocation();
}

// Called every frame
void ANPCManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
