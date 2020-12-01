// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BartenderCharacter.generated.h"

UCLASS()
class MOONSHOT_API ABartenderCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABartenderCharacter();

	//Transform of held items
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemManagement")
	class USceneComponent* HeldItemSocket;
	
	//Item Manager
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemManagment")
    class UItemManagerComponent* ItemManagerComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	// First person camera
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	class USkeletalMeshComponent* SkelMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	float Health = 100.f;
	
	UFUNCTION()
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController *EventInstigator, AActor *DamageCauser) override;

	UPROPERTY(BlueprintReadOnly, Category = "Gameplay")
	// Checks if player is currently stunned
	bool IsStunned = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (ClampMin = "0.0"))
	// Period of time before player can take damage again
	float IFrameLength = 0.5f;
	
	UFUNCTION()
	void BeginStun();

	UFUNCTION()
	void EndStun();

	UFUNCTION(BlueprintImplementableEvent, Category = "Gameplay")
	// Notify when Stun begins
	void OnStunBegin();

	UFUNCTION(BlueprintImplementableEvent, Category = "Gameplay")
	// Notify when Stun ends
    void OnStunEnd();

	UFUNCTION(BlueprintImplementableEvent, Category = "Gameplay")
	// Notify when Invincibility begins
    void OnInvincibilityBegin();

	UFUNCTION(BlueprintImplementableEvent, Category = "Gameplay")
	// Notify when Invincibility ends
    void OnInvincibilityEnd();

	UFUNCTION(BlueprintImplementableEvent, Category = "Gameplay")
	void OnKnockOut();

	UFUNCTION(BlueprintImplementableEvent, Category = "Gameplay")
	void OnDamageTaken();
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	UCameraComponent* GetCamera();

	UFUNCTION()
	USkeletalMeshComponent* GetSkelMesh();

	UFUNCTION()
	void MoveRight(float Value);

	UFUNCTION()
	void Duck();

	UFUNCTION()
	void Stand();
	
	UFUNCTION()
	void Use();

	UFUNCTION()
	void Reload();

	UFUNCTION()
	void KnockOut();

private:
	FVector HeldItemSocketLocation = FVector(40.f, 30.f, 30.f);
	FTimerHandle StunHandle;
	FTimerHandle InvincibilityHandle;

	bool IsInvincible;
	void BeginInvincibility();
	void EndInvincibility();

};
