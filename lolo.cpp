#include "lolo.h"
#include "game.h"
#include "heart.h"
#include "widget.h"

Lolo::Lolo(int x, int y, int direction, std::string imgName):
    Personage(true, x, y, direction, imgName), shoots{0}, heartPicked{0}
{}

int Lolo::getShoots()
{
    return this->shoots;
}

void Lolo::setShoots(int shoots)
{
    this->shoots = shoots;
}

int Lolo::getHeartsPicked()
{
    return this->heartPicked;
}

void Lolo::setHeartsPicked(int hearts)
{
    this->heartPicked = hearts;
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
