// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackUnion.h"

AttackUnion::AttackUnion()
    : attack1(nullptr), attack2(nullptr), attack1Owned(nullptr), attack2Owned(nullptr)
{}

void AttackUnion::setAttacks(Attack* attack1Ptr, Attack* attack2Ptr)
{
    this->attack1 = attack1Ptr;
    this->attack2 = attack2Ptr;
}

void AttackUnion::setAttacks(std::unique_ptr<Attack> attack1Ptr, Attack* attack2Ptr)
{
    this->setAttacks(attack1Ptr.get(), attack2Ptr);
    this->attack1Owned = std::move(attack1Ptr);
}

void AttackUnion::setAttacks(Attack* attack1Ptr, std::unique_ptr<Attack> attack2Ptr)
{
    this->setAttacks(attack1Ptr, attack2Ptr.get());
    this->attack2Owned = std::move(attack2Ptr);
}

void AttackUnion::setAttacks(std::unique_ptr<Attack> attack1Ptr, std::unique_ptr<Attack> attack2Ptr)
{
    this->setAttacks(attack1Ptr.get(), attack2Ptr.get());
    this->attack1Owned = std::move(attack1Ptr);
    this->attack2Owned = std::move(attack2Ptr);
}

bool AttackUnion::doNextAction(AActor& actor)
{
    //return attack1->doNextAction(actor) && attack2->doNextAction(actor);
    attack1->doNextAction(actor);
    attack2->doNextAction(actor);
    return isDone();
}

bool AttackUnion::isDone() const
{
    return attack1->isDone() && attack2->isDone();
}

void AttackUnion::reset()
{
    attack1->reset();
    attack2->reset();
}
