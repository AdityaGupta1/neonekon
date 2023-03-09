// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackDebugPrintMessage.h"

#include "neonekon/Attacks/Actions/ActionDebugPrint.h"
#include <string>

AttackDebugPrintMessage::AttackDebugPrintMessage(const std::string message)
    : Attack()
{
    this->actions.push_back(std::make_unique<ActionDebugPrint>(message));
}
