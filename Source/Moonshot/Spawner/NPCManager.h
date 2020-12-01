// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "Moonshot/Characters/NPCBase.h"
#include "Moonshot/LevelActors/BarSpot.h"
#include "Moonshot/Tools/Enums.h"
#include "Moonshot/Tools/MoonPrint.h"
#include "Moonshot/Tools/MoonshotStructs.h"

#include "NPCManager.generated.h"





class AMoonshotGameModeBase;
class UMoonshotGameInstanceBase;
class ANPCSpawnPoint;
class AMobsterAttackBox;

UCLASS()
class MOONSHOT_API ANPCManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANPCManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Billboard")
	class UBillboardComponent* BillboardComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "References")
	AMoonshotGameModeBase* GameMode;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "References")
	UMoonshotGameInstanceBase* GameInstance;
	
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawn Data")
	int32 CurrentSetDay;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Day Data")
	UDataTable* DayDataTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Day Data")
	FDayData DayData;
	
	UPROPERTY()
	FTimerHandle SpawnTimerHandle;

	UPROPERTY()
	FTimerHandle DayTimerHandle;
	
	UFUNCTION()
	void SpawnNPC();

	UFUNCTION()
	void ClearDayData();
	
	float GetSpawnTimeVariance(float Variant);

	UFUNCTION(BlueprintImplementableEvent, Category = "Spawn")
	void SpawnMobster();

	UFUNCTION(BlueprintImplementableEvent, Category = "Spawn")
	void SpawnCustomer();

	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void AddNPCToArray(ANPCBase* NPC);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Spawn")
	FVector GetRandomSpawnPoint();

	UFUNCTION(BlueprintPure, Category="Mobster")
	AMobsterAttackBox *GetAttackBox() const;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bar Spots")
	TArray<ABarSpot*> BarSpots;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Mobster")
	AMobsterAttackBox *MobsterAttackBox;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
    void RemoveNPC(ANPCBase* RemovedNPC);


	UFUNCTION()
	float GetRemainingDayTime();

	UFUNCTION()
	void EndDay();

	UFUNCTION()
	void BeginDay();

	UFUNCTION()
	void SetDayData(UPARAM(meta = (ClampMin = "1",ClampMax = "7")) int32 Day = 1);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Bar Spots")
	TArray<ABarSpot*> GetBarSpots();

	UFUNCTION()
	void GetSpawnPoints();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Points")
	TArray<ANPCSpawnPoint*> SpawnPoints;

	UFUNCTION()
	bool AllStoolsFilled();
	
};
