// Fill out your copyright notice in the Description page of Project Settings.


#include "Glass_Item.h"

#include "Camera/CameraComponent.h"

void AGlass_Item::BeginPlay()
{
    Super::BeginPlay();
}

void AGlass_Item::Pickup(UItemManagerComponent* ItemManager)
{
    Super::Pickup(ItemManager);
    
    Camera = BartenderCharacter->GetCamera();
}

void AGlass_Item::Place(UItemManagerComponent* ItemManager)
{
    Super::Place(ItemManager);

    Camera = nullptr;
}

void AGlass_Item::Use(AActor* User)
{
    FCollisionQueryParams CollisionQueryParams;

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

TArray<TEnumAsByte<EBeverageType>> AGlass_Item::GetContainedBeverages()
{
    return ContainedBeverages;
}

void AGlass_Item::AddContainedBeverages(EBeverageType NewBeverage)
{
    if(ContainedBeverages.Contains(NewBeverage))
    {
        return;
    }
    
    ContainedBeverages.Add(NewBeverage);
    OnFill();
}

void AGlass_Item::Recycle()
{
    bIsInUse = false;
    ContainedBeverages.Empty();
    Reset();
    
    OnRecycle();
}

bool AGlass_Item::GetIsInUse()
{
    return bIsInUse;
}

void AGlass_Item::SetIsInUse(bool bNewState)
{
    bIsInUse = bNewState;
}

AActor* AGlass_Item::GetSpawner()
{
    return Spawner;
}

void AGlass_Item::SetSpawner(AActor* SpawnedBy)
{
    Spawner = SpawnedBy;
}


