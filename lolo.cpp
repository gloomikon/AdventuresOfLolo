#include "lolo.h"
#include "game.h"
#include "heart.h"
Lolo::Lolo(int x, int y, int direction, QRect rect, QPixmap pixmap, std::string imgName):
    Personages(true, x, y, direction, rect, pixmap, imgName), shoots{0}, heartPicked{0}
{}

void Lolo::makeWalkable()
{
    this->walkable = true;
}

void Lolo::checkPickUp(Game *game)
{
    if (game->getMap()[this->getCoords().y * WIDTH + this->getCoords().x].objPtr &&
            dynamic_cast<Heart*>(game->getMap()[this->getCoords().y * WIDTH + this->getCoords().x].objPtr))
    {
        this->heartPicked++;
        delete dynamic_cast<Heart*>(game->getMap()[this->getCoords().y * WIDTH + this->getCoords().x].objPtr);
        game->getMap()[this->getCoords().y * WIDTH + this->getCoords().x].objPtr = nullptr;
    }
    if (this->heartPicked == game->getHeartsToPick())
        game->getChest()->open();
}
