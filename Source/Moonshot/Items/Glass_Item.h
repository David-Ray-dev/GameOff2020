// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Moonshot/Items/Item.h"
#include "Moonshot/Tools/Enums.h"
#include "Glass_Item.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHOT_API AGlass_Item : public AItem
{
	GENERATED_BODY()
	
	protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	FHitResult Hit;

	UPROPERTY()
	UCameraComponent* Camera;

	public:
	virtual void Pickup(UItemManagerComponent* ItemManager) override;

	virtual void Place(UItemManagerComponent* ItemManager) override;

	virtual void Use(AActor* User) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "ItemManagement")
	void OnFill();

	UFUNCTION(BlueprintCallable, Category = "ItemManagement")
	TArray<TEnumAsByte<EBeverageType>> GetContainedBeverages();

	UFUNCTION(BlueprintCallable, Category = "ItemManagement")
	void AddContainedBeverages(EBeverageType NewBeverage);

	UFUNCTION(BlueprintCallable, Category = "ItemManagment")
	void Recycle();

	UFUNCTION(BlueprintCallable, Category = "ItemManagment")
	bool GetIsInUse();

	UFUNCTION(BlueprintCallable, Category = "ItemManagment")
	void SetIsInUse(bool bNewState);

	UFUNCTION(BlueprintCallable, Category = "ItemManagment")
	AActor* GetSpawner();

	UFUNCTION(BlueprintCallable, Category = "ItemManagment")
	void SetSpawner(AActor* SpawnedBy);

	UFUNCTION(BlueprintImplementableEvent, Category = "ItemManagment")
    void OnRecycle();

	private:
	UPROPERTY()
	TArray<TEnumAsByte<EBeverageType>> ContainedBeverages;

	UPROPERTY()
	bool bIsInUse;

	UPROPERTY()
	AActor* Spawner;
};
