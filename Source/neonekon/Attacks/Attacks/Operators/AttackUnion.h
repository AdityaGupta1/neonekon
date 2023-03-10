// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "neonekon/Attacks/Attack.h"

#include "CoreMinimal.h"

/**
 * 
 */
class NEONEKON_API AttackUnion : public Attack
{
private:
	Attack* attack1;
	Attack* attack2;

	std::unique_ptr<Attack> attack1Owned;
	std::unique_ptr<Attack> attack2Owned;

public:
	AttackUnion();

	void setAttacks(Attack* attack1Ptr, Attack* attack2Ptr);
	void setAttacks(std::unique_ptr<Attack> attack1Ptr, Attack* attack2Ptr);
	void setAttacks(Attack* attack1Ptr, std::unique_ptr<Attack> attack2Ptr);
	void setAttacks(std::unique_ptr<Attack> attack1Ptr, std::unique_ptr<Attack> attack2Ptr);

	bool doNextAction(AActor& actor) override;
	bool isDone() const override;
	void reset() override;
};
