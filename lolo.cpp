#include "lolo.h"

Lolo::Lolo(int x, int y, int direction, QRect rect, QPixmap pixmap, std::string imgName):
    Personages(true, x, y, direction, rect, pixmap, imgName), shoots{0}
{}

void Lolo::makeWalkable()
{
    this->walkable = true;
}
