// Fill out your copyright notice in the Description page of Project Settings.


#include "MoonPrint.h"

#pragma region Warning_Logs
void UMoonPrint::WarningLog(FString String) const
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *String);
}

void UMoonPrint::WarningLog(int32 Integer) const
{
	UE_LOG(LogTemp, Warning, TEXT("%d"), Integer);
}

void UMoonPrint::WarningLog(float Float) const
{
	UE_LOG(LogTemp, Warning, TEXT("%f"), Float);
}

void UMoonPrint::WarningLog(FVector Vector) const
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Vector.ToString());
}

void UMoonPrint::WarningLog(FRotator Rotator) const
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Rotator.ToString());	
}

void UMoonPrint::WarningLog(bool Bool) const
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), (Bool ? TEXT("True") : TEXT("False")));
}

void UMoonPrint::WarningLog(FString String, int32 Integer) const
{
	UE_LOG(LogTemp, Warning, TEXT("%s %d"), *String, Integer);
}

void UMoonPrint::WarningLog(FString String, float Float) const
{
	UE_LOG(LogTemp, Warning, TEXT("%s %f"), *String, Float);
}

void UMoonPrint::WarningLog(FString String, FVector Vector) const
{
	UE_LOG(LogTemp, Warning, TEXT("%s %s"), *String, *Vector.ToString());
}

void UMoonPrint::WarningLog(FString String, FRotator Rotator) const
{
	UE_LOG(LogTemp, Warning, TEXT("%s %s"), *String, *Rotator.ToString());
}

void UMoonPrint::WarningLog(FString String, bool Bool) const
{
	UE_LOG(LogTemp, Warning, TEXT("%s %s"), *String, (Bool ? TEXT("True") : TEXT("False")));
}

#pragma endregion Warning_Logs

#pragma region OnScreenDebugs
void UMoonPrint::ScreenDebug(FString String, FColor Color, float DisplayTime, int32 Key) const
{
	GEngine->AddOnScreenDebugMessage(Key, DisplayTime, Color, FString::Printf(TEXT("%s"), *String));
}

void UMoonPrint::ScreenDebug(int32 Integer, FColor Color, float DisplayTime, int32 Key) const
{
	GEngine->AddOnScreenDebugMessage(Key, DisplayTime, Color, FString::Printf(TEXT("%d"), Integer));
}

void UMoonPrint::ScreenDebug(float Float, FColor Color, float DisplayTime, int32 Key) const
{
	GEngine->AddOnScreenDebugMessage(Key, DisplayTime, Color, FString::Printf(TEXT("%f"), Float));
}

void UMoonPrint::ScreenDebug(FVector Vector, FColor Color, float DisplayTime, int32 Key) const
{
	GEngine->AddOnScreenDebugMessage(Key, DisplayTime, Color, FString::Printf(TEXT("%s"), *Vector.ToString()));
}

void UMoonPrint::ScreenDebug(FRotator Rotator, FColor Color, float DisplayTime, int32 Key) const
{
	GEngine->AddOnScreenDebugMessage(Key, DisplayTime, Color, FString::Printf(TEXT("%s"), *Rotator.ToString()));
}

void UMoonPrint::ScreenDebug(bool Bool, FColor Color, float DisplayTime, int32 Key) const
{
	GEngine->AddOnScreenDebugMessage(Key, DisplayTime, Color, FString::Printf(TEXT("%s"), (Bool ? TEXT("True") : TEXT("False"))));
}

void UMoonPrint::ScreenDebug(FString String, int32 Integer, FColor Color, float DisplayTime, int32 Key) const
{
	GEngine->AddOnScreenDebugMessage(Key, DisplayTime, Color, FString::Printf(TEXT("%s %d"), *String, Integer));
}

void UMoonPrint::ScreenDebug(FString String, float Float, FColor Color, float DisplayTime, int32 Key) const
{
	GEngine->AddOnScreenDebugMessage(Key, DisplayTime, Color, FString::Printf(TEXT("%s %f"), *String, Float));
}

void UMoonPrint::ScreenDebug(FString String, FVector Vector, FColor Color, float DisplayTime, int32 Key) const
{
	GEngine->AddOnScreenDebugMessage(Key, DisplayTime, Color, FString::Printf(TEXT("%s %s"), *String, *Vector.ToString()));
}

void UMoonPrint::ScreenDebug(FString String, FRotator Rotator, FColor Color, float DisplayTime, int32 Key) const
{	
	GEngine->AddOnScreenDebugMessage(Key, DisplayTime, Color, FString::Printf(TEXT("%s %s"), *String, *Rotator.ToString()));
}

void UMoonPrint::ScreenDebug(FString String, bool Bool, FColor Color, float DisplayTime, int32 Key) const
{
	GEngine->AddOnScreenDebugMessage(Key, DisplayTime, Color, FString::Printf(TEXT("%s %s"), *String, (Bool ? TEXT("True") : TEXT("False"))));
}
#pragma endregion OnScreenDebugs

#pragma region Logs
void UMoonPrint::Log(FString String) const
{
	UE_LOG(LogTemp, Log, TEXT("%s"), *String);
}

void UMoonPrint::Log(int32 Integer) const
{
	UE_LOG(LogTemp, Log, TEXT("%d"), Integer);
}

void UMoonPrint::Log(float Float) const
{
	UE_LOG(LogTemp, Log, TEXT("%f"), Float);
}

void UMoonPrint::Log(FVector Vector) const
{
	UE_LOG(LogTemp, Log, TEXT("%s"), *Vector.ToString());
}

void UMoonPrint::Log(FRotator Rotator) const
{
	UE_LOG(LogTemp, Log, TEXT("%s"), *Rotator.ToString());	
}

void UMoonPrint::Log(bool Bool) const
{
	UE_LOG(LogTemp, Log, TEXT("%s"), (Bool ? TEXT("True") : TEXT("False")));
}

void UMoonPrint::Log(FString String, int32 Integer) const
{
	UE_LOG(LogTemp, Log, TEXT("%s %d"), *String, Integer);
}

void UMoonPrint::Log(FString String, float Float) const
{
	UE_LOG(LogTemp, Log, TEXT("%s %f"), *String, Float);
}

void UMoonPrint::Log(FString String, FVector Vector) const
{
	UE_LOG(LogTemp, Log, TEXT("%s %s"), *String, *Vector.ToString());
}

void UMoonPrint::Log(FString String, FRotator Rotator) const
{
	UE_LOG(LogTemp, Log, TEXT("%s %s"), *String, *Rotator.ToString());
}

void UMoonPrint::Log(FString String, bool Bool) const
{
	UE_LOG(LogTemp, Log, TEXT("%s %s"), *String, (Bool ? TEXT("True") : TEXT("False")));
}
#pragma endregion