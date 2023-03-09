// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "neonekon/Attacks/Attack.h"

#include "CoreMinimal.h"

/**
 *
 */
class NEONEKON_API AttackDebugPrintMessage : public Attack
{
public:
	AttackDebugPrintMessage(const std::string message);
};
