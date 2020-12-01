// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "ItemPlacer.generated.h"

UCLASS(Abstract, Blueprintable, BlueprintType)
class MOONSHOT_API AItemPlacer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemPlacer();

	UFUNCTION(BlueprintPure, Category = "Location")
	FVector SnapLocation() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UBoxComponent* BoxCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	USceneComponent* ItemLocation;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
