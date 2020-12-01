// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Tools/MoonshotStructs.h"
#include "MoonshotGameInstanceBase.h"
#include "MoonshotGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHOT_API AMoonshotGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	AMoonshotGameModeBase();
	
public:
	
	UPROPERTY(BlueprintReadOnly, Category = "Timer")
	// Current countdown time measured in seconds
	int32 CurrentTime = 0;

	UPROPERTY(BlueprintReadOnly, Category = "Money")
	// Current tips the player has
	int32 CurrentTips = 0;
	
	UPROPERTY(BlueprintReadOnly, Category = "Gameplay")
	// Current day value
	FDayData CurrentDay;

	UPROPERTY(BlueprintReadOnly, Category = "Gameplay")
	// Data to be added to money total at end of level
	FLevelEvaluationModifiers LevelStatistics;
	
	UFUNCTION(BlueprintCallable, Category = "Timer")
	// Starts the level countdown
	void StartCountdown(UPARAM(meta = (ClampMin = "0")) int Seconds = 0);

	UFUNCTION(BlueprintCallable, Category = "Money")
	// Add tips to player
	void EarnTips(UPARAM(meta = (ClampMin = "0")) int Money = 0);

	UFUNCTION(Exec, BlueprintCallable, Category = "Gameplay")
	// Adds killed mobster to level statistics
	void AddKilledMobsterToStatistics(int32 Number = 1);

	UFUNCTION(Exec, BlueprintCallable, Category = "Gameplay")
    // Adds killed mobster to level statistics
    void AddKilledCustomerToStatistics(int32 Number = 1);

	UFUNCTION(Exec, BlueprintCallable, Category = "Gameplay")
    // Adds killed mobster to level statistics
    void AddInjuredCustomerToStatistics(int32 Number = 1);

	UFUNCTION(Exec, BlueprintCallable, Category = "Gameplay")
    // Adds killed mobster to level statistics
    void AddBulletsToStatistics(int32 Number = 1);

	UFUNCTION(Exec, meta = (DevelopmentOnly), Category = "Timer")
	// Pauses timer. Only used in debug.
	void ToggleCountdown();

	UFUNCTION(Exec, meta = (DevelopmentOnly), Category = "Timer")
	// Overrides timer. Only used in debug.
	void OverrideCountdown(UPARAM(meta = (ClampMin = "0")) const int Seconds = 0);

	UFUNCTION(Exec, meta = (DevelopmentOnly), Category = "Money")
	// Overrides tips. Only used in debug.
	void SetTips(UPARAM(meta = (ClampMin = "0")) const int Money = 0);

	UFUNCTION(Exec, meta = (DevelopmentOnly), Category = "Gameplay")
	void BeatLevel();

	UFUNCTION(Exec, meta = (DevelopmentOnly), Category = "Gameplay")
	void LoseLevel();
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Timer")
    // Notify executed when level countdown ends
    void OnCountdownEnd(bool bProperEnd = true);

	UFUNCTION(BlueprintImplementableEvent, Category = "Money")
	void OnTipsEarned(int32 Money = 0);
	
protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Timer")
	// Notify executed when level countdown starts
	void OnCountdownBegin();

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
    void PrepareLevelByDay(UPARAM(meta = (ClampMin = "1", ClampMax = "7")) int32 Day = 1);
	
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	// Prepare Level
	void PrepareLevelByCurrentDay();
	
private:

	UPROPERTY()
		FTimerHandle CountdownHandle;

	UFUNCTION()
		void UpdateCountdown();
};
