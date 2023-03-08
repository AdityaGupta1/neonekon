// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Action.h"

/**
 * 
 */
class NEONEKON_API ActionDebugPrint: public Action
{
private:
	const std::string message;

public:
	ActionDebugPrint(std::string message);

	void doAction(const AActor& actor) override;
};
