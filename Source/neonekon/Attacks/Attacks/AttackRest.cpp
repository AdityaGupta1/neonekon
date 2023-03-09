// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackRest.h"

#include "neonekon/Attacks/Actions/ActionRest.h"

AttackRest::AttackRest(int length)
    : Attack()
{
    for (int i = 0; i < length; ++i)
    {
        this->actions.push_back(std::make_unique<ActionRest>());
    }
}
