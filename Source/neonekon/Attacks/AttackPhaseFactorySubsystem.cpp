// Fill out your copyright notice in the Description page of Project Settings


#include "AttackPhaseFactorySubsystem.h"

#include "neonekon/Util/SmartPointerHelp.h"
#include "UObject/ConstructorHelpers.h"

#include "Attacks/Operators/AttackUnion.h"

#include "Attacks/AttackDebugPrintMessage.h"
#include "Attacks/AttackDebugPrintNumbers.h"
#include "Attacks/AttackRest.h"
#include "Attacks/AttackRepeatingShotgun.h"
#include "Attacks/AttackRotatingLasers.h"

#define ANT AttackAndTransitions

#define LOAD(path, varName) {\
    ConstructorHelpers::FObjectFinder<UClass> projectile(TEXT(path));\
    if (projectile.Object) {\
        varName = projectile.Object;\
    }\
}

UAttackPhaseFactorySubsystem::UAttackPhaseFactorySubsystem()
    : UGameInstanceSubsystem(), phaseFunctionMap()
{
    phaseFunctionMap[FString(TEXT("debug"))] = &UAttackPhaseFactorySubsystem::createDebug;
    phaseFunctionMap[FString(TEXT("dog 1"))] = &UAttackPhaseFactorySubsystem::createDog1;

    LOAD("/Script/Engine.Blueprint'/Game/Projectiles/Bullet.Bullet_C'", bullet);

    LOAD("/Script/Engine.Blueprint'/Game/Projectiles/LineTelegraph.LineTelegraph_C'", laserTelegraph);
    LOAD("/Script/Engine.Blueprint'/Game/Projectiles/Laser.Laser_C'", laser);
}

void UAttackPhaseFactorySubsystem::createPhases(const FString id, std::vector<sPtr<AttackPhase>>& phases)
{
    phases.clear();
    phaseFunctionMap[id](*this, phases);
}

void UAttackPhaseFactorySubsystem::createDebug(std::vector<sPtr<AttackPhase>>& phases)
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


void UAttackPhaseFactorySubsystem::createDog1(std::vector<sPtr<AttackPhase>>& phases)
{
    sPtr<AttackPhase> phase1 = mkS<AttackPhase>();
    {
        uPtr<ANT> antAlterntingRings = mkU<ANT>();
        antAlterntingRings->attack = AttackRepeatingShotgun::alternatingRings(this->bullet, 8, 0.0, 4, 250);
        antAlterntingRings->transitions = {
            {"rest 1"}
        };

        uPtr<ANT> antWindmill = mkU<ANT>();
        antWindmill->attack = mkU<AttackRepeatingShotgun>(ActionShotgun::fromCone(this->bullet, 4, 20, 0)
            .setProjSpeed(150.0).setStackRepeat(3), 10, 0, [](int i) { return -8 * i; });
        antWindmill->transitions = {
            {"rest 1"}
        };

        uPtr<ANT> antRotatingLasers = mkU<ANT>();
        uPtr<AttackRotatingLasers> attackRotatingLasers =
            mkU<AttackRotatingLasers>(this->laserTelegraph, this->laser, 4, 0, 15.0, 2, 2, 7, 0);
        antRotatingLasers->attack = std::move(attackRotatingLasers);
        antRotatingLasers->transitions = {
            {"rest 2"}
        };

        uPtr<ANT> antRest1 = mkU<ANT>();
        antRest1->attack = mkU<AttackRest>(2);
        antRest1->transitions = {
            {"alternating rings", 3},
            {"windmill", 2},
            {"rotating lasers", 2},
        };

        uPtr<ANT> antRest2 = mkU<ANT>();
        antRest2->attack = mkU<AttackRest>(4);
        antRest2->transitions = {
            {"alternating rings", 3},
            {"windmill", 2}
        };

        phase1->addAnt("alternating rings", std::move(antAlterntingRings));
        phase1->addAnt("windmill", std::move(antWindmill));
        phase1->addAnt("rotating lasers", std::move(antRotatingLasers));
        phase1->addAnt("rest 1", std::move(antRest1));
        phase1->addAnt("rest 2", std::move(antRest2));

        phase1->setAnt("rest 1");
    }

    sPtr<AttackPhase> phase2 = mkS<AttackPhase>();
    {
        uPtr<ANT> antAlterntingRings = mkU<ANT>();
        antAlterntingRings->attack = AttackRepeatingShotgun::alternatingRings(this->bullet, 12, 0.0, 4, 300);
        antAlterntingRings->transitions = {
            {"rest 1"}
        };

        uPtr<ANT> antWindmill = mkU<ANT>();
        antWindmill->attack = mkU<AttackRepeatingShotgun>(ActionShotgun::fromCone(this->bullet, 5, 20, 0)
            .setProjSpeed(200.0).setStackRepeat(4), 10, 0, [](int i) { return 10 * i; });
        antWindmill->transitions = {
            {"rest 1"}
        };

        uPtr<ANT> antRotatingLasers = mkU<ANT>();
        uPtr<AttackUnion> attackRotatingLasersUnion = mkU<AttackUnion>();
        attackRotatingLasersUnion->setAttacks(
            mkU<AttackRotatingLasers>(this->laserTelegraph, this->laser, 6, 60.0, 15.0, 2, 2, 7, 0),
            mkU<AttackRepeatingShotgun>(ActionShotgun::fromCone(this->bullet, 2, 6.0, 24.0).setProjSpeed(160.0).setStackRepeat(5),
                7 * (2 + 2), 0, [](int i) { return -17 * i; })
        );
        antRotatingLasers->attack = std::move(attackRotatingLasersUnion);
        antRotatingLasers->transitions = {
            {"rest 2"}
        };

        uPtr<ANT> antRest1 = mkU<ANT>();
        antRest1->attack = mkU<AttackRest>(2);
        antRest1->transitions = {
            {"alternating rings", 3},
            {"windmill", 2},
            {"rotating lasers", 2},
        };

        uPtr<ANT> antRest2 = mkU<ANT>();
        antRest2->attack = mkU<AttackRest>(4);
        antRest2->transitions = {
            {"alternating rings", 3},
            {"windmill", 2}
        };

        phase2->addAnt("alternating rings", std::move(antAlterntingRings));
        phase2->addAnt("windmill", std::move(antWindmill));
        phase2->addAnt("rotating lasers", std::move(antRotatingLasers));
        phase2->addAnt("rest 1", std::move(antRest1));
        phase2->addAnt("rest 2", std::move(antRest2));

        phase2->setAnt("rest 1");
    }

    phases.push_back(phase1);
    phases.push_back(phase1);
    phases.push_back(phase2);
}
