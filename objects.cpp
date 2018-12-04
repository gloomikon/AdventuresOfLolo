#include "objects.h"

Objects::Objects(bool shootable, bool walkable, std::string imgName):
    shootable{shootable}, walkable{walkable}, imgName{imgName}
{}

bool Objects::isShootable()
{
    return this->shootable;
}

bool Objects::isWalkable()
{
    return this->walkable;
}

void Objects::setImgName(std::string imgName)
{
    this->imgName = imgName;
}

void Objects::makeWalkable()
{
    this->walkable = true;
}

std::string Objects::getImgName()
{
    return this->imgName;
}
