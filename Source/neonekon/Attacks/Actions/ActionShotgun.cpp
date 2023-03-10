// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionShotgun.h"

#include "Engine/World.h"

ActionShotgun::ActionShotgun(TSubclassOf<class AProjectileBase> projectileClass, int numBullets, float angleStart, float bulletSpacing)
    : projectileClass(projectileClass), numBullets(numBullets), angleStart(angleStart), bulletSpacing(bulletSpacing), 
    stacks(1), stackAngleOffset(0)
{}

ActionShotgun ActionShotgun::fromCone(TSubclassOf<class AProjectileBase> projectileClass, int numBullets, float totalSpread, float aimDirection)
{
    float angleStart = aimDirection - (totalSpread / 2);
    float bulletSpacing = totalSpread / (numBullets - 1);
    return ActionShotgun(projectileClass, numBullets, angleStart, bulletSpacing);
}

ActionShotgun ActionShotgun::fromSingleBullet(TSubclassOf<class AProjectileBase> projectileClass, float aimDirection)
{
    return ActionShotgun(projectileClass, 1, aimDirection, 0.0);
}

ActionShotgun ActionShotgun::fromCircle(TSubclassOf<class AProjectileBase> projectileClass, int numBullets, float angleOffset)
{
    float angleStart = angleOffset;
    float bulletSpacing = 360.0f / numBullets;
    return ActionShotgun(projectileClass, numBullets, angleStart, bulletSpacing);
}

ActionShotgun& ActionShotgun::setProjSpeed(float projSpeed)
{
    this->setProjSetupFunction([=](AProjectileBase* proj) { proj->speed = projSpeed; });
    return *this;
}

ActionShotgun& ActionShotgun::setStackRepeat(int numStacks, float angleOffset)
{
    this->stacks = numStacks;
    this->stackAngleOffset = angleOffset;
    return *this;
}

ActionShotgun& ActionShotgun::setStackRepeat(int numStacks)
{
    return setStackRepeat(numStacks, 360.0 / numStacks);
}

ActionShotgun& ActionShotgun::addAngleOffset(float addedAngleOffset)
{
    this->angleStart += addedAngleOffset;
    return *this;
}

void ActionShotgun::doAction(AActor& actor)
{
    const FVector location = actor.GetActorLocation();
    const FVector scale(1.0f);

    for (int stack = 0; stack < stacks; ++stack)
    {
        float angle = angleStart + stack * stackAngleOffset;
        for (int i = 0; i < numBullets; ++i)
        {
            const FRotator rotation(0, angle, 0);
            spawnProjectile(actor, projectileClass, FTransform(rotation, location, scale));
            angle += bulletSpacing;
        }
    }
}