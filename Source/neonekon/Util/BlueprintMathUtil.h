// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BlueprintMathUtil.generated.h"

/**
 * 
 */
UCLASS()
class NEONEKON_API UBlueprintMathUtil : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintPure, Category = "Math|Integer")
	static bool isEven(int x);
	
	UFUNCTION(BlueprintPure, Category = "Math|Float")
	static float smoothstep(float min = 0, float max = 1, float x = 0);

	UFUNCTION(BlueprintPure, Category = "Math|Float")
	static float offsetSmoothstep(float x);
};
