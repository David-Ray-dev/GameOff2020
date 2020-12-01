// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Moonshot/Items/Item.h"
#include "Gun_Item.generated.h"

/**
 * 
 */
UCLASS()
class MOONSHOT_API AGun_Item : public AItem
{
	GENERATED_BODY()
	
	protected:
	virtual void BeginPlay() override;

	public:
	virtual void Pickup(UItemManagerComponent* ItemManager) override;
	virtual void Place(UItemManagerComponent* ItemManager) override;
	virtual void Use(AActor* User) override;

	UFUNCTION(BlueprintCallable)
	void Reload();

	UFUNCTION(BlueprintImplementableEvent)
	void OnReload();

	UFUNCTION(BlueprintCallable)
	TArray<FHitResult> GetHit();

	private:
	

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float FireRange = 5000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float GunDamage = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	int32 MaxAmmo = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponStatus")
	int32 CurrentAmmo = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponStatus")
	bool bIsReloading;

	UPROPERTY(BlueprintReadOnly)
	TArray<FHitResult> Hit;

	UPROPERTY(BlueprintReadWrite, Category = "Settings")
	UCameraComponent* Camera;

	
};
