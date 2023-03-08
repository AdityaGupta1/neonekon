// Fill out your copyright notice in the Description page of Project Settings.


#include "Attack.h"

Attack::Attack()
    : actions(), nextAction(0)
{}

void Attack::doNextAction(const AActor& actor) {
    actions[nextAction]->doAction(actor);
    nextAction++;
}

bool Attack::isDone() const {
    return nextAction >= actions.size();
}
