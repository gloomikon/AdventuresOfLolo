#include "lolo.h"
#include "game.h"
#include "heart.h"
#include "widget.h"

Lolo::Lolo(int x, int y, int direction, std::string imgName):
    Personage(true, x, y, direction, imgName), shoots{0}, heartPicked{0}
{}

void Lolo::checkPickUp(Game *game)
{
    if (game->getMap()[this->getCoords().y * WIDTH + this->getCoords().x].objPtr &&
            dynamic_cast<Heart*>(game->getMap()[this->getCoords().y * WIDTH + this->getCoords().x].objPtr))
    {
        this->shoots += 2;
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

int Lolo::getShoots()
{
    return this->shoots;
}

void Lolo::setShoots(int shoots)
{
    this->shoots = shoots;
}

void Lolo::suicide(Game *game)
{
    game->disactivate();
    game->setLives(game->getLives() - 1);
    if (game->getLives() == 0)
    {
        game->setLvl(1);
        game->setLives(5);
    }
    game->restartLevel();
    game->getWidget()->connectTimers();
    game->activate();
}
