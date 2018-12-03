#include "chest.h"

Chest::Chest(std::string imgName) : Objects(true, true, imgName), opened{false}
{
}

bool Chest::isOpened()
{
    return this->opened;
}

void Chest::open()
{
    this->opened = true;
    this->setImgName("chest02");
}
