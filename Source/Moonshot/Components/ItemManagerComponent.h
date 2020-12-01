// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "ItemManagerComponent.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MOONSHOT_API UItemManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UItemManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	UFUNCTION(BlueprintCallable, Category = "ItemManagement")
	void Hold(class AItem* Item);

	UFUNCTION(BlueprintCallable, Category = "ItemManagement")
	AItem* Release();

	UFUNCTION(BlueprintCallable, Category = "ItemManagement")
	AItem* GetHeldItem();

	UFUNCTION(BlueprintCallable, Category = "ItemManagement")
	class ABartenderCharacter* GetBartenderOwner();

private:
	UPROPERTY()
	class AItem* HeldItem = nullptr;
	UPROPERTY()
	class ABartenderCharacter* BartenderOwner = nullptr;
};
