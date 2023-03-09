// Fill out your copyright notice in the Description page of Project Settings.


#include "Attack.h"

Attack::Attack()
    : actions(), nextAction(0)
{}

bool Attack::doNextAction(const AActor& actor) 
{
    actions[nextAction]->doAction(actor);
    nextAction++;
    return isDone();
}

bool Attack::isDone() const 
{
    return nextAction >= actions.size();
}

void Attack::reset()
{
    nextAction = 0;
}