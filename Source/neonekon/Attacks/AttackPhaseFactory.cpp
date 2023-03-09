// Fill out your copyright notice in the Description page of Project Settings


#include "AttackPhaseFactory.h"

#include "neonekon/Util/SmartPointerHelp.h"

#include "Attacks/AttackDebugPrintMessage.h"
#include "Attacks/AttackDebugPrintNumbers.h"

#define ANT AttackAndTransitions

void AttackPhaseFactory::createPhases(const FString id, std::vector<uPtr<AttackPhase>>& phases)
{
    phases.clear();
    phaseFunctionMap[id](phases);
}

std::map<FString, std::function<void(std::vector<uPtr<AttackPhase>>&)>> AttackPhaseFactory::phaseFunctionMap = {
    {FString(TEXT("debug")), &createDebug}
};

void AttackPhaseFactory::createDebug(std::vector<uPtr<AttackPhase>>& phases)
{
    uPtr<AttackPhase> phase1 = mkU<AttackPhase>();
    {
        uPtr<ANT> antPrint1 = mkU<ANT>();
        antPrint1->attack = mkU<AttackDebugPrintMessage>("joe");
        antPrint1->transitions = {
            {"print2", 1}
        };
        phase1->addAnt("print1", std::move(antPrint1));

        uPtr<ANT> antPrint2 = mkU<ANT>();
        antPrint2->attack = mkU<AttackDebugPrintMessage>("biden");
        antPrint2->transitions = {
            {"print1", 1}
        };
        phase1->addAnt("print2", std::move(antPrint2));

        phase1->setAnt("print1");
    }

    phases.push_back(std::move(phase1));
}