// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackAlternatingRings.h"

#include "neonekon/Attacks/Actions/ActionShotgun.h"

AttackAlternatingRings::AttackAlternatingRings(TSubclassOf<class AProjectileBase> projectileClass, int numBullets, int length, float angleOffset)
    : Attack()
{
    float alternateAngleOffset = 180.0f / numBullets;

    for (int i = 0; i < length; ++i)
    {
        float angleOffsetReal = angleOffset;
        if (i % 2 == 1)
        {
            angleOffsetReal += alternateAngleOffset;
        }

        ActionShotgun action = ActionShotgun::fromCircle(projectileClass, numBullets, angleOffsetReal);
        action.setProjSetupFunction([](AProjectileBase* proj) { proj->speed = 300; });
        this->actions.push_back(std::make_unique<ActionShotgun>(action));
    }
}

AttackAlternatingRings::AttackAlternatingRings(TSubclassOf<class AProjectileBase> projectileClass, int numBullets, int length)
    : AttackAlternatingRings(projectileClass, numBullets, length, 0)
{}