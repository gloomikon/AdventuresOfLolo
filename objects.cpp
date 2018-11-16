#include "objects.h"

Objects::Objects(bool shootable, bool walkable):
    shootable{shootable}, walkable{walkable}
{}

bool Objects::isShootable()
{
    return this->shootable;
}

bool Objects::isWalkable()
{
    return this->walkable;
}
