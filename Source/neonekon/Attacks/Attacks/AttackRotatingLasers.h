// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "neonekon/Attacks/Attack.h"
#include "neonekon/Attacks/Projectiles/ProjectileBase.h"

#include "CoreMinimal.h"

/**
 *
 */
class NEONEKON_API AttackRotatingLasers : public Attack
{
public:
	AttackRotatingLasers(TSubclassOf<class AProjectileBase> telegraphClass, TSubclassOf<class AProjectileBase> laserClass, 
		int numLasers, float initialAngleOffset, float iterationAngleOffset, int durationTelegraph, int durationLasers, 
		int iterations, int restBetweenIterations = 0);
};
