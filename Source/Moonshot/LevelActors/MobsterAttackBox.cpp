// Fill out your copyright notice in the Description page of Project Settings.


#include "MobsterAttackBox.h"
#include "Components/BoxComponent.h"
#include "Components/BillboardComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AMobsterAttackBox::AMobsterAttackBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Icon = CreateDefaultSubobject<UBillboardComponent>(TEXT("Icon"));
	SetRootComponent(Icon);
	
	BoundingBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoundingBox"));
	BoundingBox->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMobsterAttackBox::BeginPlay()
{
	Super::BeginPlay();
	
}

FVector AMobsterAttackBox::GetRandomBoxLocation() const
{
	FTransform boxTransform = BoundingBox->GetComponentTransform();
	FVector relativeSpot = UKismetMathLibrary::RandomPointInBoundingBox(FVector::ZeroVector, BoundingBox->GetScaledBoxExtent());
	return boxTransform.TransformPosition(relativeSpot);
}

// Called every frame
void AMobsterAttackBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

