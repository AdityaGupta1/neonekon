// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include <string>
#include <unordered_map>

#include "Attack.h"

struct Transition {
	std::string id;
	int weight;
};

struct AttackAndTransitions {
	std::unique_ptr<Attack> attack;
	std::vector<Transition> transitions;
	int totalWeight;
};

/**
 * 
 */
class NEONEKON_API AttackPhase
{
private:
	std::unordered_map<std::string, std::unique_ptr<AttackAndTransitions>> stateMachine;
	AttackAndTransitions* currentAnt;

public:
	AttackPhase();
	AttackPhase(const AttackPhase&) = delete;
	AttackPhase& operator=(const AttackPhase&) = delete;
	~AttackPhase() = default;

	void addAttackAndTransitions(const std::string id, std::unique_ptr<AttackAndTransitions>& ant);
	void setAttack(const std::string id);
	
	bool onBeat(const AActor& actor);
};
