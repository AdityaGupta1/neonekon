// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackPhaseManager.h"

#include "AttackPhaseFactory.h"

UAttackPhaseManager::UAttackPhaseManager()
    : UObject(), phases(), currentPhase(0), isPhaseTransitionQueued(false)
{}


void UAttackPhaseManager::loadPhases(const FString phasesId)
{
    this->currentPhase = 0;
    AttackPhaseFactory::createPhases(phasesId, this->phases);
}

bool UAttackPhaseManager::onBeat(const AActor* actor)
{
    bool attackDone = phases[currentPhase]->onBeat(*actor);
    return attackDone && this->isPhaseTransitionQueued;
}

void UAttackPhaseManager::queuePhaseTransition()
{
    this->isPhaseTransitionQueued = true;
}