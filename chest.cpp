#include "chest.h"

Chest::Chest(std::string imgName) : Objects(true, true, imgName), opened{false}
{
}

bool Chest::isOpened()
{
    return this->opened;
}
