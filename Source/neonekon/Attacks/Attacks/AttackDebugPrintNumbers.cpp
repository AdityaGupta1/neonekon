// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackDebugPrintNumbers.h"

#include "neonekon/Attacks/Actions/ActionDebugPrint.h"
#include <string>

AttackDebugPrintNumbers::AttackDebugPrintNumbers(int length)
    : Attack()
{
    for (int i = 0; i < length; ++i) 
    {
        this->actions.push_back(std::make_unique<ActionDebugPrint>(std::to_string(i + 1)));
    }
}
