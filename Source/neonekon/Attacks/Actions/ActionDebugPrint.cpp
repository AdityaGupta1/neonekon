// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionDebugPrint.h"

ActionDebugPrint::ActionDebugPrint(std::string message)
    : message(message)
{}

void ActionDebugPrint::doAction(const AActor& actor)
{
    GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, FString(message.c_str()));
}