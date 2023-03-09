// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AttackPhase.h"

#include <map>

#include "CoreMinimal.h"

/**
 * 
 */
class NEONEKON_API AttackPhaseFactory
{
public:
    static void createPhases(const FString id, std::vector<std::unique_ptr<AttackPhase>>& phases);

private:
    static std::map<FString, std::function<void(std::vector<std::unique_ptr<AttackPhase>>&)>> phaseFunctionMap;

    static void createDebug(std::vector<std::unique_ptr<AttackPhase>>& phases);
};
