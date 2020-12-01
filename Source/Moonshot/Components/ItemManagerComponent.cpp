// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemManagerComponent.h"
#include "Moonshot/Items/Item.h"
#include "Moonshot/Characters/BartenderCharacter.h"

//ABartenderCharacter* BartenderOwner = nullptr;

// Sets default values for this component's properties
UItemManagerComponent::UItemManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UItemManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	
	BartenderOwner = Cast<ABartenderCharacter>(GetOwner());
}

void UItemManagerComponent::Hold(AItem* Item)
{
	if(HeldItem)
	{
		return;
	}
	
	//Store Item reference
	HeldItem = Item;

	/*//Print Item name to screen
	if(HeldItem)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor:: Green, FString::Printf(TEXT("Picked up %s"), *HeldItem->GetName()));
	}*/
	
	
	//Move object to socket
	if(BartenderOwner)
	{
		if(BartenderOwner->GetSkelMesh())
		{
			FAttachmentTransformRules myRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, false);
			HeldItem->AttachToComponent(BartenderOwner->GetSkelMesh(), myRules, "item_socket");

			HeldItem->SetActorEnableCollision(false);
		}
	}
}

AItem* UItemManagerComponent::Release()
{
	AItem* ReleasedItem = nullptr;
	
	if(HeldItem)
	{
		ReleasedItem = HeldItem;
		HeldItem->SetActorEnableCollision(true);
		const FDetachmentTransformRules myRules(EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld,EDetachmentRule::KeepWorld, false);
		HeldItem->DetachFromActor(myRules);
		HeldItem = nullptr;
		ReleasedItem->OnPlace();
	}

	return ReleasedItem;
}

AItem* UItemManagerComponent::GetHeldItem()
{
	return HeldItem;
}

ABartenderCharacter* UItemManagerComponent::GetBartenderOwner()
{
	return BartenderOwner;
}


