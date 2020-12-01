// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BarSpot.generated.h"

UCLASS()
class MOONSHOT_API ABarSpot : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABarSpot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stool Mesh")
	class UStaticMeshComponent* StoolMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Status")
	bool bOccupied = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Status")
	class ANPCBase* Occupier;

	
		
};
