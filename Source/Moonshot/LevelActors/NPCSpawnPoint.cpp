// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCSpawnPoint.h"
#include "Components/BillboardComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ANPCSpawnPoint::ANPCSpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Setup billboard 
	BillboardComponent = CreateDefaultSubobject<UBillboardComponent>(TEXT("BillboardComponent"));
	RootComponent = BillboardComponent;

}

void ANPCSpawnPoint::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

}

// Called when the game starts or when spawned
void ANPCSpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANPCSpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANPCSpawnPoint::AddPointToManager(ANPCManager* Manager)
{
	Manager->SpawnPoints.AddUnique(this);
			
	if(Manager->SpawnPoints.Contains(nullptr))
	{
		Manager->SpawnPoints.Remove(nullptr);
	}
}
