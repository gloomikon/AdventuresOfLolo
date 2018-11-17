#include "chest.h"

Chest::Chest() : Objects(true, true), opened{false}
{
}

bool Chest::isOpened()
{
    return this->opened;
}
