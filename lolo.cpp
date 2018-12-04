#include "lolo.h"
#include "game.h"
#include "heart.h"
#include "widget.h"

Lolo::Lolo(int x, int y, int direction, QRect rect, QPixmap pixmap, std::string imgName):
    Personages(true, x, y, direction, rect, pixmap, imgName), shoots{0}, heartPicked{0}
{}

void Lolo::checkPickUp(Game *game)
{
    if (game->getMap()[this->getCoords().y * WIDTH + this->getCoords().x].objPtr &&
            dynamic_cast<Heart*>(game->getMap()[this->getCoords().y * WIDTH + this->getCoords().x].objPtr))
    {
        this->heartPicked++;
        if (this->heartPicked == game->getHeartsToPick())
            game->getChest()->open();
        delete dynamic_cast<Heart*>(game->getMap()[this->getCoords().y * WIDTH + this->getCoords().x].objPtr);
        game->getMap()[this->getCoords().y * WIDTH + this->getCoords().x].objPtr = nullptr;
    }
    if (game->getMap()[this->getCoords().y * WIDTH + this->getCoords().x].objPtr &&
        game->getMap()[this->getCoords().y * WIDTH + this->getCoords().x].objPtr == game->getChest() &&
            game->getChest()->isOpened() && game->getChest()->hasJewellery())
    {
        game->getChest()->finish();
        game->clear();
        game->getEXit()->setImgName("exitopen");
        game->getEXit()->makeWalkable();
        game->setFirstDraw(true);
    }
    if (game->getMap()[this->getCoords().y * WIDTH + this->getCoords().x].objPtr &&
        game->getMap()[this->getCoords().y * WIDTH + this->getCoords().x].objPtr == game->getEXit())
    {
        game->disactivate();
        game->nextLevel();
        game->getWidget()->connectTimers();
        game->activate();
    }
}
