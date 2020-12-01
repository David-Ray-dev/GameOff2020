// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Tools/MoonshotStructs.h"
#include "Delegates/Delegate.h"


#include "MoonshotGameInstanceBase.generated.h"


/**
 * 
 */
UCLASS()
class MOONSHOT_API UMoonshotGameInstanceBase : public UGameInstance
{
	GENERATED_BODY()

public:

	
	
	UFUNCTION(Exec, BlueprintCallable, Category = "Saving", meta = (DeprecatedFunction))
		void SaveGame();

	UFUNCTION(BlueprintCallable, Category = "Saving", meta = (DeprecatedFunction))
		void NewGame(FString Filename);
	
	UFUNCTION(BlueprintCallable, Category = "Saving", meta = (DeprecatedFunction))
		void LoadGame(FString Filename);

	UFUNCTION(BlueprintCallable, Category = "Money", meta = (DeprecatedFunction))
		int32 GetSavedMoneyFromFile();

	UFUNCTION(BlueprintCallable, Category = "Money", meta = (DeprecatedFunction))
		void SetSavedMoneyInFile(UPARAM(meta = (ClampMin = "0")) int32 Money = 0);

	UFUNCTION(BlueprintCallable, Category = "Gameplay", meta = (DeprecatedFunction))
		void UpdateSaveFileOnLevelComplete(UPARAM(meta = (ClampMin = "0")) int32 Money = 0);

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	int32 UpdateOnLevelComplete(UPARAM(meta = (ClampMin = "0"))int32 Money);
	
	UFUNCTION(BlueprintCallable, Category = "Money", meta = (DeprecatedFunction))
		bool AttemptTransaction(UPARAM(meta = (ClampMin = "0")) int32 Money = 0, bool SaveOnPurchase = true);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
        UDataTable* DayDataTable;
        
    UFUNCTION(BlueprintCallable, Category = "Gameplay")
    	void ReturnToFirstDay();
	
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
		FDayData GetCurrentDayData();

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
		FDayData GetDayData(UPARAM(meta = (ClampMin = "1", ClampMax = "7"))int32 Day);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Day", meta = (ClampMin = "1", ClampMax = "8"))
		int32 CurrentDay = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Money")
		int32 TotalMoney = 0;

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Day")
		ANPCManager* NPCManager;
	
	// UPROPERTY()
           // FAsyncSaveGameToSlotDelegate SaveDelegate;
	
	/*
	 * Console command functions below
	 */

	// Moving these functions over to GameMode, GameInstance is keeping tracking of total money via save data
	
	// UFUNCTION(Exec, Category = "Money", meta = (DevelopmentOnly))
	// void InflateMoney(UPARAM(meta = (ClampMin = "0")) int32 Money = 0);

	// UFUNCTION(Exec, Category = "Money", meta = (DevelopmentOnly))
    // void ClearMoney();

	
	
protected:
	UFUNCTION()
		virtual void BeginPlay();
	
	UFUNCTION(BlueprintImplementableEvent)
	// Notify when the game is saved
		void OnSave();
	// void OnSave(const FString &Filename, const int32 Slot, bool Succeeded);

private:
	UPROPERTY()
	class UMoonshotSaveGameBase* LoadedFile;

	
};
