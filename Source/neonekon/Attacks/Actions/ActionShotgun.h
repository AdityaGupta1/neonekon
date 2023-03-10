// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "neonekon/Attacks/Actions/ActionSpawnProjectiles.h"
#include "neonekon/Attacks/Projectiles/ProjectileBase.h"

#include "CoreMinimal.h"

/**
 *
 */
class NEONEKON_API ActionShotgun : public ActionSpawnProjectiles
{
private:
	const TSubclassOf<class AProjectileBase> projectileClass;
	const int numBullets;
	float angleStart;
	const float bulletSpacing;

	int stacks;
	float stackAngleOffset;

	ActionShotgun(TSubclassOf<class AProjectileBase> projectileClass, int numBullets, float angleStart, float bulletSpacing);

public:
	static ActionShotgun fromCone(TSubclassOf<class AProjectileBase> projectileClass, int numBullets, float totalSpread, float aimDirection);
	static ActionShotgun fromCircle(TSubclassOf<class AProjectileBase> projectileClass, int numBullets, float angleOffset);
	// TODO option to aim at player, maybe make angleStart a function pointer that can return a constant or aim at the player

	ActionShotgun& setProjSpeed(float projSpeed);

	ActionShotgun& setStackRepeat(int numStacks, float angleOffset);
	ActionShotgun& setStackRepeat(int numStacks);

	ActionShotgun& addAngleOffset(float addedAngleOffset);

	void doAction(AActor& actor) override;
};
