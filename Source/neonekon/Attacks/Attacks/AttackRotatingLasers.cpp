// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackRotatingLasers.h"

#include "neonekon/Attacks/Actions/ActionShotgun.h"
#include "neonekon/Attacks/Actions/ActionRest.h"

AttackRotatingLasers::AttackRotatingLasers(TSubclassOf<class AProjectileBase> telegraphClass, TSubclassOf<class AProjectileBase> laserClass,
    int numLasers, float initialAngleOffset, float iterationAngleOffset, int durationTelegraph, int durationLasers, 
    int iterations, int restBetweenIterations)
    : Attack()
{
    for (int i = 0; i < iterations; ++i)
    {
        float angleOffset = initialAngleOffset + i * iterationAngleOffset;

        ActionShotgun actionTelegraph = ActionShotgun::fromCircle(telegraphClass, numLasers, angleOffset);
        actionTelegraph.setProjSetupFunction([=](AProjectileBase* proj) { proj->durationBeats = durationTelegraph; });
        this->actions.push_back(std::make_unique<ActionShotgun>(actionTelegraph));

        for (int j = 0; j < durationTelegraph - 1; ++j) 
        {
            this->actions.push_back(std::make_unique<ActionRest>());
        }

        ActionShotgun actionLasers = ActionShotgun::fromCircle(laserClass, numLasers, angleOffset);
        actionLasers.setProjSetupFunction([=](AProjectileBase* proj) { proj->durationBeats = durationLasers; });
        this->actions.push_back(std::make_unique<ActionShotgun>(actionLasers));

        for (int j = 0; j < durationLasers - 1; ++j)
        {
            this->actions.push_back(std::make_unique<ActionRest>());
        }
    }
}