// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Moonshot/Spawner/NPCManager.h"

#include "NPCSpawnPoint.generated.h"

UCLASS()
class MOONSHOT_API ANPCSpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANPCSpawnPoint();

	virtual void OnConstruction(const FTransform &Transform) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Billboard")
	class UBillboardComponent* BillboardComponent;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void AddPointToManager(ANPCManager* Manager);

};


