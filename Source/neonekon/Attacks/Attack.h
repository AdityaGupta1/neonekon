// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Action.h"

#include "GameFramework/Actor.h"

/**
 * 
 */
class NEONEKON_API Attack
{
protected:
	std::vector<std::unique_ptr<Action>> actions;
	int nextAction;

public:
	Attack();
	Attack(const Attack&) = delete;
	Attack& operator=(const Attack&) = delete;
	virtual ~Attack() = default;

	bool doNextAction(const AActor& actor);
	bool isDone() const;
};
