// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackPhaseManager.h"

#include "Kismet/GameplayStatics.h"

#include "AttackPhaseFactorySubsystem.h"

UAttackPhaseManager::UAttackPhaseManager()
    : UObject(), phases(), currentPhase(0), isPhaseTransitionQueued(false)
{}


void UAttackPhaseManager::loadPhases(const FString phasesId, AActor* actor)
{
    this->currentPhase = 0;
    actor->GetGameInstance()->GetSubsystem<UAttackPhaseFactorySubsystem>()->createPhases(phasesId, this->phases);
}

bool UAttackPhaseManager::onBeat(AActor* actor)
{
    bool attackDone = phases[currentPhase]->onBeat(*actor);
    return attackDone && this->isPhaseTransitionQueued;
}

void UAttackPhaseManager::queuePhaseTransition()
{
    this->isPhaseTransitionQueued = true;
}