// Copyright Epic Games, Inc. All Rights Reserved.


#include "MoonshotGameModeBase.h"

#include "Framework/MultiBox/MultiBoxDefs.h"


AMoonshotGameModeBase::AMoonshotGameModeBase()
{
    
}

void AMoonshotGameModeBase::StartCountdown(const int32 Seconds)
{
    CurrentTime = Seconds;
    GetWorldTimerManager().SetTimer(CountdownHandle, this, &AMoonshotGameModeBase::UpdateCountdown, 1.0f, true);
    OnCountdownBegin();
}

void AMoonshotGameModeBase::ToggleCountdown()
{
    if (GetWorldTimerManager().IsTimerPaused(CountdownHandle))
    {
        GetWorldTimerManager().UnPauseTimer(CountdownHandle);
    }

    else
    {
        GetWorldTimerManager().PauseTimer(CountdownHandle);
    }
}

void AMoonshotGameModeBase::OverrideCountdown(const int32 Seconds)
{
    if (GetWorldTimerManager().TimerExists(CountdownHandle))
    {
        CurrentTime = Seconds;
    }
}

void AMoonshotGameModeBase::EarnTips(const int32 Money)
{
    CurrentTips += Money;
    OnTipsEarned(Money);
}

void AMoonshotGameModeBase::AddKilledMobsterToStatistics(const int32 Number)
{
    LevelStatistics.MobstersKilled += Number;
}

void AMoonshotGameModeBase::AddKilledCustomerToStatistics(const int32 Number)
{
    LevelStatistics.CustomersKilled += Number;
}

void AMoonshotGameModeBase::AddInjuredCustomerToStatistics(const int32 Number)
{
    LevelStatistics.CustomersInjured += Number;
}

void AMoonshotGameModeBase::AddBulletsToStatistics(const int32 Number)
{
    LevelStatistics.BulletsUsed += Number;
}

void AMoonshotGameModeBase::SetTips(const int32 Money)
{
    CurrentTips = Money;
}

void AMoonshotGameModeBase::BeatLevel()
{
    const int32 VictoryMoney = CurrentDay.TargetRent + 1000;
    SetTips(VictoryMoney);
    OverrideCountdown(0);    
}

void AMoonshotGameModeBase::LoseLevel()
{
    SetTips(0);
    OverrideCountdown(0);
}


void AMoonshotGameModeBase::PrepareLevelByDay(const int32 Day)
{
    #if UE_BUILD_SHIPPING

    // If the game is in shipping build remove this
    
    PrepareLevelByCurrentDay();
    
    #endif
    
    UMoonshotGameInstanceBase* InstanceRef = Cast<UMoonshotGameInstanceBase>(GetGameInstance());

    if (InstanceRef)
    {
        CurrentDay = InstanceRef->GetDayData(Day);
        CurrentTips = InstanceRef->TotalMoney;
        
        // if (LoadMoneyFromFile)
        // {
        //     CurrentTips = InstanceRef->GetSavedMoneyFromFile();
        // }
        
        StartCountdown(CurrentDay.TimerValue);
    }
}

void AMoonshotGameModeBase::PrepareLevelByCurrentDay()
{
    UMoonshotGameInstanceBase* InstanceRef = Cast<UMoonshotGameInstanceBase>(GetGameInstance());

    if (InstanceRef)
    {
        CurrentDay = InstanceRef->GetCurrentDayData();
        CurrentTips = InstanceRef->TotalMoney;
        
        // if (LoadMoneyFromFile)
        // {
        //     CurrentTips = InstanceRef->GetSavedMoneyFromFile();
        // }
        
        StartCountdown(CurrentDay.TimerValue);
    }
}

void AMoonshotGameModeBase::UpdateCountdown()
{
    if (CurrentTime <= 0)
    {
        GetWorldTimerManager().ClearTimer(CountdownHandle);
        OnCountdownEnd(true);
    }

    else
    {
        CurrentTime--;
    }
}
