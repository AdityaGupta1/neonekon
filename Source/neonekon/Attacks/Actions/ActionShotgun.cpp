// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionShotgun.h"

#include "Engine/World.h"

ActionShotgun::ActionShotgun(TSubclassOf<class AActor> projectileClass, int numBullets, float angleStart, float bulletSpacing)
    : projectileClass(projectileClass), numBullets(numBullets), angleStart(angleStart), bulletSpacing(bulletSpacing)
{}

ActionShotgun ActionShotgun::fromCone(TSubclassOf<class AActor> projectileClass, int numBullets, float totalSpread, float aimDirection)
{
    float angleStart = aimDirection - (totalSpread / 2);
    float bulletSpacing = totalSpread / (numBullets - 1);
    return ActionShotgun(projectileClass, numBullets, angleStart, bulletSpacing);
}

ActionShotgun ActionShotgun::fromCircle(TSubclassOf<class AActor> projectileClass, int numBullets, float angleOffset)
{
    float angleStart = angleOffset;
    float bulletSpacing = 360.0f / numBullets;
    return ActionShotgun(projectileClass, numBullets, angleStart, bulletSpacing);
}

void ActionShotgun::doAction(AActor& actor)
{
    UWorld* world = actor.GetWorld();
    if (!world) 
    {
        return;
    }

    FActorSpawnParameters spawnParams;
    spawnParams.Owner = &actor;
    spawnParams.Instigator = actor.GetInstigator();

    float angle = angleStart;
    for (int i = 0; i < numBullets; ++i)
    {
        FRotator rotation(0, angle, 0);
        world->SpawnActor<AActor>(projectileClass, actor.GetActorLocation(), rotation, spawnParams);
        angle += bulletSpacing;
    }
}