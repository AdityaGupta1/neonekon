// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"

/**
 * 
 */
class NEONEKON_API Action
{
public:
	Action();
	virtual ~Action() = default;

	virtual void doAction(const AActor& actor) = 0;
};
