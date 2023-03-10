// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackAlternatingRings.h"

#include "neonekon/Attacks/Actions/ActionShotgun.h"

AttackAlternatingRings::AttackAlternatingRings(TSubclassOf<class AProjectileBase> projClass, int numBullets, int duration, float angleOffset, float projSpeed)
    : Attack()
{
    float alternateAngleOffset = 180.0f / numBullets;

    for (int i = 0; i < duration; ++i)
    {
        float angleOffsetReal = angleOffset;
        if (i % 2 == 1)
        {
            angleOffsetReal += alternateAngleOffset;
        }

        ActionShotgun action = ActionShotgun::fromCircle(projClass, numBullets, angleOffsetReal);
        action.setProjSetupFunction([=](AProjectileBase* proj) { proj->speed = projSpeed; });
        this->actions.push_back(std::make_unique<ActionShotgun>(action));
    }
}