// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCBase.h"
#include "NPCController.h"
#include "Moonshot/Spawner/NPCManager.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ANPCBase::ANPCBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Added by Nick, setting all NPCs to generate block on visibility traces
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
}

// Called when the game starts or when spawned
void ANPCBase::BeginPlay()
{
	Super::BeginPlay();	
	
}

float ANPCBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	HealthValue = FGenericPlatformMath::Max((0.0f), HealthValue - DamageAmount);

	if (HealthValue <= 0.0f)
	{
		ResetValues();
		OnKilled();
	}
	
	return DamageAmount;	
}

void ANPCBase::OnKilled_Implementation()
{
	ResetValues();

	Destroy();
	

}

void ANPCBase::EnterBar()
{
	ANPCController *ctrl = Cast<ANPCController>(Controller);

	if(IsValid(ctrl))
	{
		ctrl->ChangeAIState(ENPCState::Arriving);
	}
}

void ANPCBase::LeaveBar()
{
	ANPCController *ctrl = Cast<ANPCController>(Controller);

	if(IsValid(ctrl))
	{
		ctrl->ChangeAIState(ENPCState::Leaving);
	}
}

void ANPCBase::GetUnoccupiedSpot()
{	
	
	if(BarSpots.Num() > 0 && AssignedSpot == nullptr)
	{
		TArray<ABarSpot*> UnoccupiedSpots;
		
		for (ABarSpot* Spot : BarSpots)
		{
			if(Spot->bOccupied == false && Spot->Occupier == nullptr)
			{
				UnoccupiedSpots.AddUnique(Spot);
			}
		}

		if (UnoccupiedSpots.Num() == 1)
		{
			AssignedSpot = UnoccupiedSpots[0];
			AssignedSpot->bOccupied = true;
			AssignedSpot->Occupier = this;
			
		}

		if(UnoccupiedSpots.Num() > 1)
		{
			AssignedSpot = UnoccupiedSpots[FMath::RandRange(0,UnoccupiedSpots.Num() - 1)];
			AssignedSpot->bOccupied = true;
			AssignedSpot->Occupier = this;
			
		}
	}
	
}

void ANPCBase::ResetValues()
{
	if(NPCManager)
	{
		NPCManager->RemoveNPC(this);

	}	


	if(NPCType == ENPCType::NPC_Customer)
	{
		if(AssignedSpot)
		{
			AssignedSpot->bOccupied = false;
			AssignedSpot->Occupier = nullptr;
			AssignedSpot = nullptr;
		
		}
	}

}


// Called every frame
void ANPCBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPCBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

