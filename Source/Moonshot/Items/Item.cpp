// Fill out your copyright notice in the Description page of Project Settings.


#include "Moonshot/Items/Item.h"
#include "Moonshot/Components/ItemManagerComponent.h"
#include "Moonshot/LevelActors/ItemPlacer.h"
#include "Moonshot/LevelActors/ItemSlot.h"

// Sets default values
AItem::AItem()
{
	
}

void AItem::OnConstruction(const FTransform &Transform)
{
	if (SnapTarget)
	{
		this->SetActorLocation(SnapTarget->SnapLocation());
	}
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	World = GetWorld();
}



void AItem::Pickup(UItemManagerComponent* ItemManager)
{
	BartenderCharacter = ItemManager->GetBartenderOwner();

	if(CurrentItemSlot)
	{
		CurrentItemSlot->CurrentItem = nullptr;
		CurrentItemSlot = nullptr;
	}
	
	ItemManager->Hold(this);

	OnPickUp();
}

void AItem::Place(UItemManagerComponent* ItemManager)
{
	BartenderCharacter = nullptr;
	ItemManager->Release();

	OnPlace();
}

void AItem::Use(AActor* User)
{
	
}

AItemSlot* AItem::GetCurrentItemSlot()
{
	return CurrentItemSlot;
}

void AItem::SetCurrentItemSlot(AItemSlot* NewItemSlot)
{
	CurrentItemSlot = NewItemSlot;
}



