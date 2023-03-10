// Fill out your copyright notice in the Description page of Project Settings


#include "AttackPhaseFactorySubsystem.h"

#include "neonekon/Util/SmartPointerHelp.h"
#include "UObject/ConstructorHelpers.h"

#include "Attacks/AttackDebugPrintMessage.h"
#include "Attacks/AttackDebugPrintNumbers.h"
#include "Attacks/AttackRest.h"
#include "Attacks/AttackAlternatingRings.h"

#define ANT AttackAndTransitions

// TSubclassOf<class AActor> getProjectile(std::string path)
// {
//     ConstructorHelpers::FObjectFinder<UBlueprint> projectile(UTF8_TO_TCHAR(path.c_str()));
//     return (UClass*) projectile.Object->GeneratedClass;
// }

UAttackPhaseFactorySubsystem::UAttackPhaseFactorySubsystem()
    : UGameInstanceSubsystem(), phaseFunctionMap()
{
    phaseFunctionMap[FString(TEXT("debug"))] = &UAttackPhaseFactorySubsystem::createDebug;
    phaseFunctionMap[FString(TEXT("dog 1"))] = &UAttackPhaseFactorySubsystem::createDog1;

    ConstructorHelpers::FObjectFinder<UBlueprint> projectile(TEXT("/Script/Engine.Blueprint'/Game/Projectiles/Bullet.Bullet'"));
    bullet = (UClass*)projectile.Object->GeneratedClass;
}

void UAttackPhaseFactorySubsystem::createPhases(const FString id, std::vector<uPtr<AttackPhase>>& phases)
{
    phases.clear();
    phaseFunctionMap[id](*this, phases);
}

void UAttackPhaseFactorySubsystem::createDebug(std::vector<uPtr<AttackPhase>>& phases)
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


void UAttackPhaseFactorySubsystem::createDog1(std::vector<uPtr<AttackPhase>>& phases)
{
    uPtr<AttackPhase> phase1 = mkU<AttackPhase>();
    {
        uPtr<ANT> antAlterntingRings = mkU<ANT>();
        antAlterntingRings->attack = mkU<AttackAlternatingRings>(this->bullet, 12, 4, 0.0, 300);
        antAlterntingRings->transitions = {
            {"rest", 1}
        };
        phase1->addAnt("alternating rings", std::move(antAlterntingRings));

        uPtr<ANT> antRest = mkU<ANT>();
        antRest->attack = mkU<AttackRest>(4);
        antRest->transitions = {
            {"alternating rings", 1}
        };
        phase1->addAnt("rest", std::move(antRest));

        phase1->setAnt("rest");
    }

    phases.push_back(std::move(phase1));
}
