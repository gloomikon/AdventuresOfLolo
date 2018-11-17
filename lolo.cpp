#include "lolo.h"

Lolo::Lolo(int x, int y, int direction):
    Personages(true, x, y, direction), shoots{0}
{}

void Lolo::makeWalkable()
{
    this->walkable = true;
}
