// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun_Item.h"

#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "Moonshot/Characters/NPCBase.h"
#include "Framework/MultiBox/MultiBoxDefs.h"
#include "Kismet/GameplayStatics.h"

void AGun_Item::BeginPlay()
{
    Super::BeginPlay();

    CurrentAmmo = MaxAmmo;
    bIsReloading = false;
    World = GetWorld();
}

void AGun_Item::Pickup(UItemManagerComponent* ItemManager)
{
    Super::Pickup(ItemManager);

    Camera = BartenderCharacter->GetCamera();
}

void AGun_Item::Place(UItemManagerComponent* ItemManager)
{
    Super::Place(ItemManager);

    Camera = nullptr;
}

void AGun_Item::Use(AActor* User)
{
    if(CurrentAmmo <= 0)
    {
        Reload();
        return;
    }
    if(bIsReloading)
    {
        return;
    }

    CurrentAmmo--;
    
    FVector StartLocation = Camera->GetComponentLocation();
    FVector EndLocation = StartLocation + Camera->GetForwardVector() * FireRange;
    FCollisionQueryParams CollisionQueryParams;
    CollisionQueryParams.AddIgnoredActor(GetAttachParentActor());
    CollisionQueryParams.AddIgnoredActor(this);
    
    if (User)
    {
        CollisionQueryParams.AddIgnoredActor(User);
    }
    
    FCollisionShape traceShape = FCollisionShape::MakeCapsule(50.f, 50.f);

    //DrawDebugLine(World, StartLocation, EndLocation, FColor::Green, false, 1.f, 0.f, 1.f);
    //DrawDebugCapsule(World, GetActorLocation(), 50.f, 50.f, FQuat::Identity, FColor::Green, true);

    /*if(World->SweepMultiByChannel(Hit, StartLocation, EndLocation, FQuat::Identity, ECC_Visibility, traceShape))
    {
        //Add VFX here is done in cpp. Opted to do this in BP after OnUse()
        //UGameplayStatics::SpawnEmitterAtLocation(World, )

        for(FHitResult hit : Hit)
        {
            if(hit.GetActor())
            {
                GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Orange, FString::Printf(TEXT("Hit: %s"), *hit.GetActor()->GetName()));

                ANPCBase* Npc = Cast<ANPCBase>(hit.GetActor());
            
                //If NPC, call OnShot in NPC class
                if (Npc)
                {
                    UGameplayStatics::ApplyDamage(Npc, GunDamage, GetWorld()->GetFirstPlayerController(), this, nullptr);
                }
            }
        }
        
        /*if(Hit.GetActor())
        {
            GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Orange, FString::Printf(TEXT("Hit: %s"), *Hit.GetActor()->GetName()));

            ANPCBase* Npc = Cast<ANPCBase>(Hit.GetActor());
            
            //If NPC, call OnShot in NPC class
            if (Npc)
            {
                UGameplayStatics::ApplyDamage(Npc, GunDamage, GetWorld()->GetFirstPlayerController(), this, nullptr);
            }
        }#1#
    }*/
    OnUse();
}

void AGun_Item::Reload()
{
    if(bIsReloading || CurrentAmmo >= MaxAmmo)
    {
        return;
    }
    
    bIsReloading = true;
    //When available, use anim notify for the timing of reload and reload sounds
    
    //CurrentAmmo = MaxAmmo;

    //Timing and sounds will temporarily be done here
    OnReload();
}

TArray<FHitResult> AGun_Item::GetHit()
{
    return Hit;
}

