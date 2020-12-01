// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Moonshot/Characters/BartenderCharacter.h"
#include "Moonshot/LevelActors/ItemSlot.h"



#include "Item.generated.h"

UCLASS(Abstract, Blueprintable)
class MOONSHOT_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform &Transform) override;

public:
	UFUNCTION(BlueprintCallable, Category = "ItemManagment")
	virtual void Pickup(class UItemManagerComponent* ItemManager);
	
	UFUNCTION(BlueprintCallable, Category = "ItemManagment")
	virtual void Place(class UItemManagerComponent* ItemManager);
	
	UFUNCTION(Category = "ItemManagment")
	virtual void Use(AActor* User);

	UFUNCTION(BlueprintImplementableEvent, Category = "ItemManagment")
	void OnPickUp();

	UFUNCTION(BlueprintImplementableEvent, Category = "ItemManagment")
	void OnPlace();

	//Here so that we can give 'Use' further implementation in BP
	UFUNCTION(BlueprintImplementableEvent, Category = "ItemManagment")
	void OnUse();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	class AItemPlacer* SnapTarget = nullptr;

	UFUNCTION(BlueprintCallable, Category = "ItemManagment")
	AItemSlot* GetCurrentItemSlot();

	UFUNCTION(BlueprintCallable, Category = "ItemManagment")
	void SetCurrentItemSlot(AItemSlot* NewItemSlot);

protected:
	//Ref to world
	UPROPERTY()
	UWorld* World;

	UPROPERTY()
	ABartenderCharacter* BartenderCharacter;

	UPROPERTY()
	AItemSlot* CurrentItemSlot;
};
