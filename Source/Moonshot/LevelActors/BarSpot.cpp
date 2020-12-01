// Fill out your copyright notice in the Description page of Project Settings.


#include "BarSpot.h"

// Sets default values
ABarSpot::ABarSpot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StoolMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Stool Mesh"));
	RootComponent = StoolMesh;

}

// Called when the game starts or when spawned
void ABarSpot::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABarSpot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

