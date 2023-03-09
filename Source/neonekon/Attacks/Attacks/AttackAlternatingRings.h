// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "neonekon/Attacks/Attack.h"
#include "neonekon/Attacks/Projectiles/ProjectileBase.h"

#include "CoreMinimal.h"

/**
 *
 */
class NEONEKON_API AttackAlternatingRings : public Attack
{
public:
	AttackAlternatingRings(TSubclassOf<class AProjectileBase> projectileClass, int numBullets, int length, float angleOffset);

	AttackAlternatingRings(TSubclassOf<class AProjectileBase> projectileClass, int numBullets, int length);
};
