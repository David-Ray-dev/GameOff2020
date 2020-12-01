// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Moonshot/Tools/Enums.h"
#include "Moonshot/Characters/NPCBase.h"
#include "MoonshotStructs.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FSpawnWeight
{
	GENERATED_BODY()

	FSpawnWeight()
	{
		TotalWeight = MobWeight + CustomerWeight;
		if(TotalWeight > 10)
		{
			TotalWeight = 10;
		}
	}
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (ClampMax = "10"))
	float MobWeight = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (ClampMax = "10"))
	float CustomerWeight = 9.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (ClampMax = "10"))
	float TotalWeight;

	
	
	void ChangeWeight(ENPCType LastNPCType)
	{
		switch(LastNPCType)
		{
		case ENPCType::NPC_Customer:
			CustomerWeight += -.1f;
			MobWeight += .1f;				
			break;

		case ENPCType::NPC_Mobster:
			MobWeight = 1.0f;
			CustomerWeight = 9.0f;
			break;
		}
	}
	
	
};


USTRUCT(BlueprintType)
struct FSpawnerData
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<ANPCBase*> CurrentlySpawnedNPCs;

	//Max amount of spawns allowed in the room
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin = "1"))
	int32 MaxSpawnsAllowed;	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 SpawnCount = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin = "0.1"))
	float SpawnInterval = 1.0f;	

	//Plus or Minus this value for some spawn interval variance between 0 and the set number, set to 0 for none
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin = 0))
	float IntervalVariance;	

	//Type of the last spawned NPC, will factor into the weight of the type of next spawned NPC
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ENPCType LastSpawnedNPC;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FSpawnWeight SpawnWeight;
	
};



USTRUCT(BlueprintType, Category = "Gameplay")
struct FDayData : public FTableRowBase
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0"))
		int32 TargetRent = 1000;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0"))
		int32 TimerValue = 1000;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FSpawnerData SpawnerData;
};

USTRUCT(BlueprintType, Category = "Gameplay")
struct FLevelEvaluationModifiers
// Information based on player performance in current level
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0"))
	// Number of mobsters killed during level
		int32 MobstersKilled = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0"))
	// Number of customers killed during level
		int32 CustomersKilled = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0"))
	// Number of customers injured (and not killed) during level
		int32 CustomersInjured = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0"))
	// Number of bullets used during level
		int32 BulletsUsed = 0;
	
};

