// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackPhaseManager.h"

#include <iostream>

UAttackPhaseManager::UAttackPhaseManager()
    : UObject(), phases(), isPhaseTransitionQueued(false), currentPhase(0)
{}


void UAttackPhaseManager::loadPhases(const FString phasesId)
{
    this->phases.clear();
    this->currentPhase = 0;

    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString(TEXT("loading phases: ")) + phasesId);
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