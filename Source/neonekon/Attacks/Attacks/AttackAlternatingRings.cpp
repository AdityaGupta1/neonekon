// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackAlternatingRings.h"

#include "neonekon/Attacks/Actions/ActionShotgun.h"

AttackAlternatingRings::AttackAlternatingRings(TSubclassOf<class AProjectileBase> projClass, int numBullets, float angleOffset, int duration, float projSpeed)
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

        ActionShotgun action = ActionShotgun::fromCircle(projClass, numBullets, angleOffsetReal).setProjSpeed(projSpeed);
        this->actions.push_back(std::make_unique<ActionShotgun>(action));
    }
}