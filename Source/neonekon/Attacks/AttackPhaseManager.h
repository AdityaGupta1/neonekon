// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AttackPhase.h"

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AttackPhaseManager.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class NEONEKON_API UAttackPhaseManager : public UObject
{
	GENERATED_BODY()

private:
	std::vector<std::shared_ptr<AttackPhase>> phases;
	int currentPhase;

	bool isPhaseTransitionQueued;

public:
	UAttackPhaseManager();

	UFUNCTION(BlueprintCallable)
	void loadPhases(const FString phasesId, AActor* actor);

	UFUNCTION(BlueprintCallable)
	bool onBeat(AActor* actor); // return true if should transition to next phase (transition queued and attack done)

	UFUNCTION(BlueprintCallable)
	void queuePhaseTransition();

	UFUNCTION(BlueprintCallable)
	void doPhaseTransition();
};
