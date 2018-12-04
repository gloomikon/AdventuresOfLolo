#include "chest.h"

Chest::Chest(std::string imgName) : Objects(true, true, imgName), opened{false}, jewellery{true}
{
}

bool Chest::isOpened()
{
    return this->opened;
}

bool Chest::hasJewellery()
{
    return this->jewellery;
}

void Chest::open()
{
    this->opened = true;
    this->setImgName("chest02");
}

void Chest::finish()
{
    this->jewellery = false;
    this->setImgName("chest03");
}
