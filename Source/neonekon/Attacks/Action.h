// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"

#include "CoreMinimal.h"

/**
 * 
 */
class NEONEKON_API Action
{
public:
	Action();
	virtual ~Action() = default;

	virtual void doAction(AActor& actor) = 0;
};
