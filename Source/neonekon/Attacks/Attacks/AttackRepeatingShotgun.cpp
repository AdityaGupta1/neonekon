// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackRepeatingShotgun.h"

#include "neonekon/Attacks/Actions/ActionRest.h"

AttackRepeatingShotgun::AttackRepeatingShotgun(ActionShotgun actionShotgun, int numShotguns, int restBetweenShotguns,
    std::function<float(int)> angleOffsetFunction)
    : Attack()
{
    for (int i = 0; i < numShotguns; ++i)
    {
        ActionShotgun newAction(actionShotgun);
        newAction.addAngleOffset(angleOffsetFunction(i));
        this->actions.push_back(std::make_unique<ActionShotgun>(newAction));

        if (i != numShotguns - 1) 
        {
            for (int j = 0; j < restBetweenShotguns; ++j)
            {
                this->actions.push_back(std::make_unique<ActionRest>());
            }
        }
    }
}

std::unique_ptr<AttackRepeatingShotgun> AttackRepeatingShotgun::alternatingRings(TSubclassOf<class AProjectileBase> projClass, 
    int numBullets, float angleOffset, int duration, float projSpeed)
{
    ActionShotgun actionShotgun = ActionShotgun::fromCircle(projClass, numBullets, angleOffset);
    actionShotgun.setProjSetupFunction([=](AProjectileBase* proj) { proj->speed = projSpeed; });

    float alternateAngleOffset = 180.0f / numBullets;
    auto angleOffsetFunction = [=](int i)
    {
        return (i % 2 == 1) ? angleOffset + alternateAngleOffset : angleOffset;
    };

    return std::make_unique<AttackRepeatingShotgun>(actionShotgun, duration, 0, angleOffsetFunction);
}
