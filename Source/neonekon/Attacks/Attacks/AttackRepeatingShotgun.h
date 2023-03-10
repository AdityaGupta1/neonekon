// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "neonekon/Attacks/Attack.h"
#include "neonekon/Attacks/Actions/ActionShotgun.h"

#include "CoreMinimal.h"

/**
 *
 */
class NEONEKON_API AttackRepeatingShotgun : public Attack
{
public:
	AttackRepeatingShotgun(ActionShotgun actionShotgun, int numShotguns, int restBetweenShotguns, 
		std::function<float(int)> angleOffsetFunction = nullptr);

	static std::unique_ptr<AttackRepeatingShotgun> alternatingRings(TSubclassOf<class AProjectileBase> projClass, int numBullets,
		float angleOffset, int duration, float projSpeed);
};
