// Fill out your copyright notice in the Description page of Project Settings.


#include "Bottle_Item.h"


#include "Glass_Item.h"
#include "DrawDebugHelpers.h"
#include "Camera/CameraComponent.h"

void ABottle_Item::BeginPlay()
{
    Super::BeginPlay();
}

void ABottle_Item::Pickup(UItemManagerComponent* ItemManager)
{
    Super::Pickup(ItemManager);
    
    Camera = BartenderCharacter->GetCamera();
}

void ABottle_Item::Place(UItemManagerComponent* ItemManager)
{
    Super::Place(ItemManager);

    Camera = nullptr;
}

void ABottle_Item::Use(AActor* User)
{
    FCollisionQueryParams CollisionQueryParams;
    // Added this line so the trace can't hit the player
    if (User)
    {
        CollisionQueryParams.AddIgnoredActor(User);
    }
    float TraceLength = 1000.f;
    //FCollisionShape UseTraceShape = FCollisionShape::MakeBox(FVector(5.f, 5.f, 5.f));
    FVector StartLocation = Camera->GetComponentLocation();
    FVector EndLocation = StartLocation + Camera->GetForwardVector() * TraceLength;
    //FQuat TraceRot = BartenderCharacter->GetActorRotation().Quaternion();

    if(World->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, ECC_Visibility, CollisionQueryParams))
    {
        if(Hit.GetActor())
        {
            OnUse();
        }
    }
}


