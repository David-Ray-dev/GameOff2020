// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum EBeverageType
{
	Bev_Whiskey		UMETA(DisplayName = "Whiskey"),
	Bev_Vodka		UMETA(DisplayName = "Vodka"),
	Bev_Beer		UMETA(DisplayName = "Beer"),
	Bev_Gin			UMETA(DisplayName = "Gin"),
	Bev_Wine		UMETA(DisplayName = "Wine"),
	Bev_Glirkadorp		UMETA(DisplayName = "Glirkadorp")
};

UENUM(BlueprintType)
enum EGlassType
{
	Glass_Whiskey	UMETA(DisplayName = "Whiskey Glass"),
	Glass_Shot		UMETA(DisplayName = "Shot Glass"),
	Glass_Beer		UMETA(DisplayName = "Beer Glass"),
	Glass_Wine		UMETA(DisplayName = "Wine Glass")
};

UENUM(BlueprintType)
enum class ENPCType : uint8
{
	NPC_Customer	UMETA(DisplayName = "Customer"),
	NPC_Mobster		UMETA(DisplayName = "Mobster")
};

UENUM(BlueprintType)
enum EAttackType
{
	Atk_Melee		UMETA(DisplayName = "Melee Attack"),
	Atk_Ranged		UMETA(DisplayName = "Ranged Attack")
};

UENUM(BlueprintType)
enum class ENPCActivationState : uint8
{
	NPC_Activated UMETA(DisplayName = "Activated"),
	NPC_Deactivated UMETA(DisplayName = "Deactivated")
	
};

UENUM(BlueprintType)
enum class ENPCState : uint8
{
	Arriving,
    Ordering,
    Leaving,
    Idle,
    Attacking
};