// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Moonshot/Tools/Enums.h"
#include "NPCController.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHOT_API ANPCController : public AAIController
{
	GENERATED_BODY()

public:
	ANPCController(const FObjectInitializer &ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category="Behavior")
	void ChangeAIState(ENPCState state);

	UFUNCTION(BlueprintPure, Category="Behavior")
	ENPCState GetState() const;

protected:
	void OnPossess(APawn *InPawn) override;

private:
	class ANPCBase *PawnRef;
	FVector StartingLocation;
};
