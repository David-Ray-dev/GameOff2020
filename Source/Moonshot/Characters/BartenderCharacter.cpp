// Fill out your copyright notice in the Description page of Project Settings.


#include "BartenderCharacter.h"

#include "IDetailTreeNode.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/GameSession.h"
#include "Moonshot/MoonshotGameModeBase.h"
#include "Moonshot/Components/ItemManagerComponent.h"
#include "Moonshot/Items/Item.h"
#include "Moonshot/Items/Gun_Item.h"

FVector RightVector;

// Sets default values
ABartenderCharacter::ABartenderCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemManagerComponent = CreateDefaultSubobject<UItemManagerComponent>(TEXT("ItemManager"));
    
    if(GetMesh())
    {
    	GetMesh()->DestroyComponent();
    }
    
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
	Camera->FieldOfView = 90;
	Camera->PostProcessSettings.MotionBlurAmount = 0;
	Camera->bUsePawnControlRotation = true;

	//Tried to child skelly to camera, thought it would replace the default. It does not.
	SkelMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkelMesh->SetupAttachment(Camera);
	
	HeldItemSocket = CreateDefaultSubobject<USceneComponent>(TEXT("HeldItemSocket"));
	HeldItemSocket->SetRelativeLocation(HeldItemSocketLocation);
}

// Called when the game starts or when spawned
void ABartenderCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Store Right vector relative to the player spawn rotation
	RightVector = GetActorRightVector();
}


// Called every frame
void ABartenderCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABartenderCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Duck", IE_Pressed, this, &ABartenderCharacter::Duck);
	PlayerInputComponent->BindAction("Stand", IE_Pressed, this, &ABartenderCharacter::Stand);
	PlayerInputComponent->BindAction("Use", IE_Pressed, this, &ABartenderCharacter::Use);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &ABartenderCharacter::Reload);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABartenderCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookRight", this, &ABartenderCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ABartenderCharacter::AddControllerPitchInput);
}

UCameraComponent* ABartenderCharacter::GetCamera()
{
	return Camera;
}

USkeletalMeshComponent* ABartenderCharacter::GetSkelMesh()
{
	return SkelMesh;
}

void ABartenderCharacter::MoveRight(float Value)
{
	if (!IsStunned)
	{
		AddMovementInput(RightVector, Value);
	}
}

void ABartenderCharacter::Duck()
{
	Crouch();
}

void ABartenderCharacter::Stand()
{
	UnCrouch();
}

void ABartenderCharacter::Use()
{
	//Does something dynamically relative to held item
	if(ItemManagerComponent && !IsStunned)
	{
		if(ItemManagerComponent->GetHeldItem())
		{
			ItemManagerComponent->GetHeldItem()->Use(this);
		}
	}
}

void ABartenderCharacter::Reload()
{
	if(ItemManagerComponent->GetHeldItem() && Cast<AGun_Item>(ItemManagerComponent->GetHeldItem()))
	{
		Cast<AGun_Item>(ItemManagerComponent->GetHeldItem())->Reload();
	}
}

void ABartenderCharacter::KnockOut()
{
	AMoonshotGameModeBase* GameMode = Cast<AMoonshotGameModeBase>(GetWorld()->GetAuthGameMode());

	GameMode->OnCountdownEnd(false);
}

float ABartenderCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                                      AActor* DamageCauser)
{
	if (!IsInvincible)
	{
		FTimerManager * Manager = &GetWorldTimerManager();
		if (Manager)
		{
			BeginInvincibility();
			Manager->SetTimer(InvincibilityHandle, this, &ABartenderCharacter::EndInvincibility, IFrameLength, false);
			
			Health -= DamageAmount;

			if(Health <= 0)
			{
				KnockOut();
			}
			OnDamageTaken();
		}
	}
	return DamageAmount;
}

void ABartenderCharacter::BeginStun()
{
	IsStunned = true;
	OnStunBegin();
}

void ABartenderCharacter::EndStun()
{
	IsStunned = false;
	OnStunEnd();
}

void ABartenderCharacter::BeginInvincibility()
{
	IsInvincible = true;
	OnInvincibilityBegin();
}

void ABartenderCharacter::EndInvincibility()
{
	IsInvincible = false;
	OnInvincibilityEnd();
}


