// Fill out your copyright notice in the Description page of Project Settings.


#include "BlueprintMathUtil.h"

bool UBlueprintMathUtil::isEven(int x)
{
    return x % 2 == 0;
}

float UBlueprintMathUtil::smoothstep(float min, float max, float x)
{
    x = std::clamp((x - min) / (max - min), 0.0f, 1.0f);
    return x * x * (3 - 2 * x);
}

float UBlueprintMathUtil::offsetSmoothstep(float x)
{
    return (smoothstep(-0.2, 0.2, x) + smoothstep(0.8, 1.2, x) - 0.5 + x / 5.0) / 1.2;
}