// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionDebugPrint.h"

ActionDebugPrint::ActionDebugPrint(std::string message)
    : message(message)
{}

void ActionDebugPrint::doAction(const AActor& actor)
{
    std::cout << message << std::endl;
}