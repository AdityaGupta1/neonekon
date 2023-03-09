// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "neonekon/Attacks/Action.h"

#include "CoreMinimal.h"

/**
 *
 */
class NEONEKON_API ActionRest : public Action
{
public:
	void doAction(AActor& actor) override;
};
