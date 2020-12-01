// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemPlacer.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"

// Sets default values
AItemPlacer::AItemPlacer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	//BoxCollider->RegisterComponent(); This causes an error when staring the engine. Can't register during moments when World isn't present.
	RootComponent = BoxCollider;
	BoxCollider->SetCollisionProfileName(TEXT("Contextual"));

	ItemLocation = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	//ItemLocation->RegisterComponent(); This causes an error when staring the engine. Can't register during moments when World isn't present.
	ItemLocation->SetupAttachment(BoxCollider);	
	ItemLocation->SetRelativeLocation(FVector(0, 0,-BoxCollider->GetScaledBoxExtent().Z));
	
}

FVector AItemPlacer::SnapLocation() const
{
	return ItemLocation->GetComponentLocation();
}

// Called when the game starts or when spawned
void AItemPlacer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemPlacer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

