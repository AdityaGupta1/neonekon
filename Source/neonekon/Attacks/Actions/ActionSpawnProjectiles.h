// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "neonekon/Attacks/Action.h"
#include "neonekon/Attacks/Projectiles/ProjectileBase.h"

#include "CoreMinimal.h"

/**
 * 
 */
class NEONEKON_API ActionSpawnProjectiles : public Action
{
protected:
    std::function<void(AProjectileBase*)> projSetupFunction;

public:
    ActionSpawnProjectiles();

    ActionSpawnProjectiles* setProjSetupFunction(std::function<void(AProjectileBase*)>);

protected:
    void spawnProjectile(AActor& originator, TSubclassOf<class AProjectileBase>, FTransform);
};
