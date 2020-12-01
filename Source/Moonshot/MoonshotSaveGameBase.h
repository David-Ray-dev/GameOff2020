// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MoonshotSaveGameBase.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHOT_API UMoonshotSaveGameBase : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	FString Filename;
	
	UPROPERTY(EditAnywhere, Category = "Money")
    // Total money stored in instance
    int32 TotalMoney = 0;

	UPROPERTY(EditAnywhere, Category = "Gameplay", meta = (ClampMin = "1", ClampMax = "7"))
	int32 CurrentDay = 1;
};
