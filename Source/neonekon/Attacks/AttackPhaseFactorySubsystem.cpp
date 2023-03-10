// Fill out your copyright notice in the Description page of Project Settings


#include "AttackPhaseFactorySubsystem.h"

#include "neonekon/Util/SmartPointerHelp.h"
#include "UObject/ConstructorHelpers.h"

#include "Attacks/AttackDebugPrintMessage.h"
#include "Attacks/AttackDebugPrintNumbers.h"
#include "Attacks/AttackRest.h"
#include "Attacks/AttackRepeatingShotgun.h"
#include "Attacks/AttackRotatingLasers.h"

#define ANT AttackAndTransitions

#define LOAD(path, varName) {\
    ConstructorHelpers::FObjectFinder<UBlueprint> projectile(TEXT(path));\
    if (projectile.Object) {\
        varName = (UClass*)projectile.Object->GeneratedClass;\
    }\
}

UAttackPhaseFactorySubsystem::UAttackPhaseFactorySubsystem()
    : UGameInstanceSubsystem(), phaseFunctionMap()
{
    phaseFunctionMap[FString(TEXT("debug"))] = &UAttackPhaseFactorySubsystem::createDebug;
    phaseFunctionMap[FString(TEXT("dog 1"))] = &UAttackPhaseFactorySubsystem::createDog1;

    LOAD("/Script/Engine.Blueprint'/Game/Projectiles/Bullet.Bullet'", bullet);

    LOAD("/Script/Engine.Blueprint'/Game/Projectiles/LineTelegraph.LineTelegraph'", laserTelegraph);
    LOAD("/Script/Engine.Blueprint'/Game/Projectiles/Laser.Laser'", laser);
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
        antAlterntingRings->attack = AttackRepeatingShotgun::alternatingRings(this->bullet, 12, 0.0, 4, 300);
        antAlterntingRings->transitions = {
            {"rest", 1}
        };

        uPtr<ANT> antRotatingLasers = mkU<ANT>();
        antRotatingLasers->attack = mkU<AttackRotatingLasers>(this->laserTelegraph, this->laser, 6, 60.0, 15.0, 2, 2, 7, 0);
        antRotatingLasers->transitions = {
            {"rest", 1}
        };

        uPtr<ANT> antWindmill = mkU<ANT>();
        antWindmill->attack = mkU<AttackRepeatingShotgun>(ActionShotgun::fromCone(this->bullet, 5, 20, 0).setStackRepeat(4),
            10, 0, [](int i) { return 10 * i; });
        antWindmill->transitions = {
            {"rest", 1}
        };

        uPtr<ANT> antRest = mkU<ANT>();
        antRest->attack = mkU<AttackRest>(2);
        antRest->transitions = {
            //{"alternating rings", 2},
            //{"rotating lasers", 1},
            {"windmill", 1}
        };

        phase1->addAnt("alternating rings", std::move(antAlterntingRings));
        phase1->addAnt("rotating lasers", std::move(antRotatingLasers));
        phase1->addAnt("windmill", std::move(antWindmill));
        phase1->addAnt("rest", std::move(antRest));

        phase1->setAnt("rest");
    }

    phases.push_back(std::move(phase1));
}
