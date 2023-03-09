// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "neonekon/Attacks/Action.h"

#include "CoreMinimal.h"

/**
 *
 */
class NEONEKON_API ActionShotgun : public Action
{
private:
	const TSubclassOf<class AActor> projectileClass;
	const int numBullets;
	const float angleStart;
	const float bulletSpacing;

	ActionShotgun(TSubclassOf<class AActor> projectileClass, int numBullets, float angleStart, float bulletSpacing);

public:
	static ActionShotgun fromCone(TSubclassOf<class AActor> projectileClass, int numBullets, float totalSpread, float aimDirection);
	static ActionShotgun fromCircle(TSubclassOf<class AActor> projectileClass, int numBullets, float angleOffset);
	// TODO option to aim at player, maybe make angleStart a function pointer that can return a constant or aim at the player

	void doAction(AActor& actor) override;
};
