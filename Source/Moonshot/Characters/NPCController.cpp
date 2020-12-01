// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCController.h"
#include "NPCBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Navigation/CrowdFollowingComponent.h"

ANPCController::ANPCController(const FObjectInitializer &ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{
    
}

void ANPCController::ChangeAIState(ENPCState state)
{
    ENPCState currentState = (ENPCState) Blackboard->GetValueAsEnum("CurrentState");

    if(currentState == state)
        return;

    Blackboard->SetValueAsEnum("CurrentState", static_cast<uint8>(state));

    switch (state)
    {
        case ENPCState::Leaving:
            if(PawnRef->NPCType == ENPCType::NPC_Customer)
                Blackboard->SetValueAsVector("TargetSpot", StartingLocation);
            break;
        
        default:
            break;
    }
}

ENPCState ANPCController::GetState() const
{
    return static_cast<ENPCState>(Blackboard->GetValueAsEnum("CurrentState"));
}

void ANPCController::OnPossess(APawn *InPawn)
{
    Super::OnPossess(InPawn);

    PawnRef = (ANPCBase *) InPawn;

    if(IsValid(PawnRef))
    {
        StartingLocation = PawnRef->GetActorLocation();
        
        RunBehaviorTree(PawnRef->LogicTree);
        Blackboard->SetValueAsEnum("CurrentState", static_cast<uint8>(ENPCState::Idle));
    }
}
