// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Moonshot/LevelActors/BarSpot.h"
#include "Moonshot/Tools/Enums.h"

#include "NPCBase.generated.h"

class ANPCManager;

UCLASS()
class MOONSHOT_API ANPCBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPCBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (ClampMin = "0.0"))
	float HealthValue = 100.0;
	
	UFUNCTION()
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController *EventInstigator, AActor *DamageCauser) override;

	UFUNCTION(BlueprintNativeEvent)
	void OnKilled();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category="Behavior")
	void EnterBar();

	UFUNCTION(BlueprintCallable, Category="Behavior")
	void LeaveBar();

	UPROPERTY(BlueprintReadWrite, Category="Customer Settings")
	float Patience;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI Settings")
	class UBehaviorTree *LogicTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI Settings", meta=(MakeEditWidget, ExposeOnSpawn = "true"))
	TArray<ABarSpot*> BarSpots;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="AI Settings", meta=(ExposeOnSpawn = "true"))
	ANPCManager* NPCManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Settings", meta=(ExposeOnSpawn = "true"))
	ENPCType NPCType;

	UFUNCTION(BlueprintCallable, Category = "Bar Spot")
	void GetUnoccupiedSpot();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI Settings")
	ABarSpot* AssignedSpot;

	UFUNCTION(BlueprintCallable, Category = "AI Settings")
	void ResetValues();
};
