// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AttackPhase.h"
#include "neonekon/Attacks/Projectiles/ProjectileBase.h"

#include <map>

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AttackPhaseFactorySubsystem.generated.h"

/**
 * 
 */
UCLASS()
class NEONEKON_API UAttackPhaseFactorySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
    UAttackPhaseFactorySubsystem();

    void createPhases(const FString id, std::vector<std::shared_ptr<AttackPhase>>& phases);

private:
    std::map<FString, std::function<void(UAttackPhaseFactorySubsystem&, std::vector<std::shared_ptr<AttackPhase>>&)>> phaseFunctionMap;

    TSubclassOf<class AProjectileBase> bullet;

    TSubclassOf<class AProjectileBase> laserTelegraph;
    TSubclassOf<class AProjectileBase> laser;

    void createDebug(std::vector<std::shared_ptr<AttackPhase>>& phases);

    void createDog1(std::vector<std::shared_ptr<AttackPhase>>& phases);
};
