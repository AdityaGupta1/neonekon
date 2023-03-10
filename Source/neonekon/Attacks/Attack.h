// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Action.h"

#include "GameFramework/Actor.h"

#include "CoreMinimal.h"

/**
 * 
 */
class NEONEKON_API Attack
{
protected:
	std::vector<std::unique_ptr<Action>> actions;
	int nextAction;

	Attack();

public:
	Attack(const Attack&) = delete;
	Attack& operator=(const Attack&) = delete;
	virtual ~Attack() = default;

	virtual bool doNextAction(AActor& actor); // return true if attack is done
	virtual bool isDone() const;
	virtual void reset();
};
