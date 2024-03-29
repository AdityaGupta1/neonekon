// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackPhase.h"

#include "Math/UnrealMathUtility.h"

#include <stdexcept>

AttackPhase::AttackPhase()
    : stateMachine(), currentAnt(nullptr)
{}

void AttackPhase::addAnt(const std::string id, std::unique_ptr<AttackAndTransitions> ant)
{
	int totalWeight = 0;
	for (const auto& transition : ant->transitions)
	{
		totalWeight += transition.weight;
	}
	ant->totalWeight = totalWeight;
	stateMachine[id] = std::move(ant);
}

void AttackPhase::setAnt(const std::string id) 
{
	currentAnt = stateMachine[id].get();
	currentAnt->attack->reset();
}

bool AttackPhase::onBeat(AActor& actor)
{
	bool attackDone = currentAnt->attack->doNextAction(actor);
	if (!attackDone)
	{
		return false;
	}

	int randomInt = FMath::RandRange(0, currentAnt->totalWeight - 1);
	for (const auto& transition : currentAnt->transitions)
	{
		if (randomInt < transition.weight)
		{
			setAnt(transition.id);
			return true;
		}

		randomInt -= transition.weight;
	}

	throw std::out_of_range("weight out of range");
	return false;
}
