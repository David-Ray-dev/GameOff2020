// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MoonPrint.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHOT_API UMoonPrint : public UObject
{
	GENERATED_BODY()

public:
	
#pragma region WarningLogs
	
	//Print a FString to the warning log, cast the string to an FString to make sure the value is entered correctly
	void WarningLog(FString String) const;

	//Print an integer to the warning log
	void WarningLog(int32 Integer) const;

	//Print a float to the warning log
	void WarningLog(float Float) const;

	//Print a FVector to the warning log
	void WarningLog(FVector Vector) const;

	//Print a FRotator to the warning log
	void WarningLog(FRotator Rotator) const;
	
	//Print a bool to the warning log
	void WarningLog(bool Bool) const;

	//Print a FString and integer to the warning log
	void WarningLog(FString String, int32 Integer) const;

	//Print a FString and float to the warning log
	void WarningLog(FString String, float Float) const;

	//Print a FString and FVector to the warning log
	void WarningLog(FString String, FVector Vector) const;

	//Print a FString and FRotator to the warning log
	void WarningLog(FString String, FRotator Rotator) const;

	//Print a FString and bool to the warning log, cast the string to an FString to make sure the value is entered correctly
	void WarningLog(FString String, bool Bool) const;
#pragma endregion 

#pragma region OnScreenDebugs

	//Print a FString to the screen, cast the string to an FString to make sure the value is entered correctly
	void ScreenDebug(FString String, FColor Color, float DisplayTime, int32 Key = -1) const;

	//Print an integer to the screen
	void ScreenDebug(int32 Integer, FColor Color, float DisplayTime, int32 Key = -1) const;

	//Print a float value to the screen
	void ScreenDebug(float Float, FColor Color, float DisplayTime, int32 Key = -1) const;

	//Print a FVector to the screen
	void ScreenDebug(FVector Vector, FColor Color, float DisplayTime, int32 Key = -1) const;

	//Print a FRotator to the screen
	void ScreenDebug(FRotator Rotator, FColor Color, float DisplayTime, int32 Key = -1) const;

	//Print a bool value to the screen
	void ScreenDebug(bool Bool, FColor Color, float DisplayTime, int32 Key = -1) const;

	//Print a FString and an integer value to the screen
	void ScreenDebug(FString String, int32 Integer, FColor Color, float DisplayTime, int32 Key = -1) const;

	//Print a FString and float value to the screen
	void ScreenDebug(FString String, float Float, FColor Color, float DisplayTime, int32 Key = -1) const;

	//Print a FString and FVector to the screen
	void ScreenDebug(FString String, FVector Vector, FColor Color, float DisplayTime, int32 Key = -1) const;

	//Print a FString and FRotator to the screen
	void ScreenDebug(FString String, FRotator Rotator, FColor Color, float DisplayTime, int32 Key = -1) const;

	//Print a FString and bool to the screen, cast the string to an FString to make sure the value is entered correctly
	void ScreenDebug(FString String, bool Bool, FColor Color, float DisplayTime, int32 Key = -1) const;
#pragma endregion

#pragma region Logs
	//Print a FString to the log, cast the string to an FString to make sure the value is entered correctly
	void Log(FString String) const;

	//Print an integer to the log
	void Log(int32 Integer) const;

	//Print a float to the log
	void Log(float Float) const;

	//Print a FVector to the log
	void Log(FVector Vector) const;

	//Print a FRotator to the log
	void Log(FRotator Rotator) const;
	
	//Print a bool to the log
	void Log(bool Bool) const;

	//Print a FString and integer to the log
	void Log(FString String, int32 Integer) const;

	//Print a FString and float to the log
	void Log(FString String, float Float) const;

	//Print a FString and FVector to the log
	void Log(FString String, FVector Vector) const;

	//Print a FString and FRotator to the log
	void Log(FString String, FRotator Rotator) const;

	//Print a FString and bool to the log, cast the string to an FString to make sure the value is entered correctly
	void Log(FString String, bool Bool) const;
#pragma endregion 
};
