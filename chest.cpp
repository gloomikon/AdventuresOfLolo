#include "chest.h"
#include "state.h"

Chest::Chest(std::string imgName, int x, int y) : Object(true, true, imgName, x, y), opened{false}, jewellery{true}
{
    this->current = new ClosedState;
}

bool Chest::isOpened()
{
    return this->opened;
}

bool Chest::hasJewellery()
{
    return this->jewellery;
}

void Chest::perfomSth()
{
    current->chestAction(this);
}

void Chest::setCurrentState(State *s)
{
    this->current = s;
}
