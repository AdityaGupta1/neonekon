// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionSpawnProjectiles.h"

ActionSpawnProjectiles::ActionSpawnProjectiles()
    : Action(), projSetupFunction(nullptr)
{}

ActionSpawnProjectiles* ActionSpawnProjectiles::setProjSetupFunction(std::function<void(AProjectileBase*)> newProjSetupFunction)
{
    this->projSetupFunction = newProjSetupFunction;
    return this;
}

void ActionSpawnProjectiles::spawnProjectile(AActor& originator, TSubclassOf<class AProjectileBase> projClass, FTransform transform)
{
    UWorld* world = originator.GetWorld();
    if (!world)
    {
        return;
    }

    FActorSpawnParameters spawnParams;
    spawnParams.Owner = &originator;
    spawnParams.Instigator = originator.GetInstigator();

    AProjectileBase* proj = world->SpawnActorDeferred<AProjectileBase>(projClass, transform);
    if (this->projSetupFunction != nullptr) 
    {
        this->projSetupFunction(proj);
    }
    proj->FinishSpawning(transform);
}