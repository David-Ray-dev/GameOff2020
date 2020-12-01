// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Moonshot/Items/Item.h"
#include "Bottle_Item.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHOT_API ABottle_Item : public AItem
{
	GENERATED_BODY()

	protected:
	virtual void BeginPlay() override;

	public:
	virtual void Pickup(UItemManagerComponent* ItemManager) override;
	
	virtual void Place(UItemManagerComponent* ItemManager) override;

	virtual void Use(AActor* User) override;

protected:
	UPROPERTY(BlueprintReadOnly)
	FHitResult Hit;

	UPROPERTY()
	UCameraComponent* Camera;
};
