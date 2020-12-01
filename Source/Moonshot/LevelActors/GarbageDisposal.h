// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GarbageDisposal.generated.h"

UCLASS()
class MOONSHOT_API AGarbageDisposal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGarbageDisposal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	


};
