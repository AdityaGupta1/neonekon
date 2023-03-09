// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "neonekon/Attacks/Attack.h"

#include "CoreMinimal.h"

/**
 *
 */
class NEONEKON_API AttackAlternatingRings : public Attack
{
public:
	AttackAlternatingRings(TSubclassOf<class AActor> projectileClass, int numBullets, int length, float angleOffset);

	AttackAlternatingRings(TSubclassOf<class AActor> projectileClass, int numBullets, int length);
};
