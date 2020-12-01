// Fill out your copyright notice in the Description page of Project Settings.


#include "MoonshotGameInstanceBase.h"
#include "Kismet/GameplayStatics.h"
#include "Moonshot/MoonshotSaveGameBase.h"
#include "GameFramework/SaveGame.h"

void UMoonshotGameInstanceBase::SaveGame()
{
    if (LoadedFile)
    {
        UGameplayStatics::SaveGameToSlot(LoadedFile, LoadedFile->Filename, 0);
        OnSave();
    }
}

void UMoonshotGameInstanceBase::NewGame(const FString Filename)
{
    LoadedFile = Cast<UMoonshotSaveGameBase>(UGameplayStatics::CreateSaveGameObject(UMoonshotSaveGameBase::StaticClass()));
    LoadedFile->Filename = Filename;
    SaveGame();
}

void UMoonshotGameInstanceBase::LoadGame(const FString Filename)
{
    if (!UGameplayStatics::DoesSaveGameExist(Filename, 0))
    {
        NewGame(Filename);
    }

    else
    {
        LoadedFile = Cast<UMoonshotSaveGameBase>(UGameplayStatics::LoadGameFromSlot(Filename, 0));
        CurrentDay = LoadedFile->CurrentDay;
    }
}

int32 UMoonshotGameInstanceBase::GetSavedMoneyFromFile()
{
    if (LoadedFile)
    {
        return LoadedFile->TotalMoney;
    }

    return 0;
}

void UMoonshotGameInstanceBase::SetSavedMoneyInFile(const int32 Money)
{
    if (LoadedFile)
    {
        LoadedFile->TotalMoney = Money;  
        SaveGame();
    }
}

void UMoonshotGameInstanceBase::UpdateSaveFileOnLevelComplete(const int32 Money)
{
    if (LoadedFile)
    {
        LoadedFile->CurrentDay += 1;
        LoadedFile->TotalMoney = Money;  
        SaveGame();
    }
}

int32 UMoonshotGameInstanceBase::UpdateOnLevelComplete(const int32 Money)
{
    TotalMoney = Money;
    CurrentDay += 1;

    return CurrentDay;
}

bool UMoonshotGameInstanceBase::AttemptTransaction(const int32 Money, const bool SaveOnPurchase)
{
    if (LoadedFile)
    {
        if (LoadedFile->TotalMoney < Money)
        {
            return false;
        }

        LoadedFile->TotalMoney -= Money;
    
        if (SaveOnPurchase)
        {
            SaveGame();
        }
    
        return true;
    }

    return false;
}

void UMoonshotGameInstanceBase::ReturnToFirstDay()
{
    CurrentDay = 1;
}

FDayData UMoonshotGameInstanceBase::GetCurrentDayData()
{
    FDayData ReturnVal = GetDayData(CurrentDay);

    return ReturnVal;   
}

FDayData UMoonshotGameInstanceBase::GetDayData(const int32 Day)
{
    if (DayDataTable)
    {        
        const FName DayTableRowName = FName(*FString::FromInt(Day));

        return *DayDataTable->FindRow<FDayData>(DayTableRowName, FString(""), true);
    }

    FDayData DefaultDay;

    return DefaultDay;
}

void UMoonshotGameInstanceBase::BeginPlay()
{
    // SaveDelegate.BindThreadSafeSP(this, &UMoonshotGameInstanceBase::OnSave);
}

/*void UMoonshotGameInstanceBase::InflateMoney(const int32 Money)
{
    LoadedFile->TotalMoney += Money;
}

void UMoonshotGameInstanceBase::ClearMoney()
{
    LoadedFile->TotalMoney = 0;
}*/
