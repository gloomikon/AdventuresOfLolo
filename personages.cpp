#include "personages.h"
#include "game.h"
#include <QDebug>
#include <ctime>
#include <cstdlib>
#include "widget.h"

Personage::Personage(bool shootable, int x, int y, int direction, std::string imgName):
    Object(shootable, false, imgName, x, y), alive{true}, shoot{false}, steps{0,0}, direction{direction}
{
    QRect rect;
    rect.setCoords(this->coords.x * SIZE,
                   this->coords.y * SIZE,
                   (this->coords.x + 1) * SIZE,
                   (this->coords.y + 1) * SIZE);
    std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
    path += this->imgName;
    path += ".png";
    QPixmap pixmap(path.c_str());
    this->pImage.rect = rect;
    this->pImage.pixmap = pixmap;
}

void Personage::drawSelf(Widget *w)
{
    QPainter painter(w);
    if (this->alive)
        painter.drawPixmap(this->pImage.rect, this->pImage.pixmap);
    else
    {
        QPixmap pixmap("C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/rip.png");
        painter.drawPixmap(this->pImage.rect, pixmap);
    }
}

void Personage::doAction()
{
}

void Personage::setImgName(std::string imgName)
{
    this->imgName = imgName;
    std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
    path += this->imgName;
    path += ".png";
    QPixmap pixmap(path.c_str());
    this->pImage.pixmap = pixmap;
}

Personage::~Personage()
{
    if (this->timer)
    {
        this->timer->stop();
        delete this->timer;
    }
}

bool Personage::isAlive()
{
    return this->alive;
}

bool Personage::madeShoot()
{
    return this->shoot;
}

int Personage::canMoveLeft(Game *game, int n)
{
    if (this->steps.stepUpDown == 0)
    {
        int k = 0;
        if (this->steps.stepLeftRight == 0 && ((game->getMap()[(this->coords.y) * WIDTH + this->coords.x - 1].objPtr &&
             !(game->getMap()[(this->coords.y) * WIDTH + this->coords.x - 1].objPtr->isWalkable())) ||
                (game->getMap()[(this->coords.y) * WIDTH + this->coords.x - 1].perPtr &&
                 game->getMap()[(this->coords.y) * WIDTH + this->coords.x - 1].perPtr->alive &&
                 game->getMap()[(this->coords.y) * WIDTH + this->coords.x - 1].perPtr->getSteps().stepLeftRight == 0) ||
                (game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x - 1].perPtr &&
                 game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x - 1].perPtr->getSteps().stepLeftRight == 0 &&
                 game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x - 1].perPtr->getSteps().stepUpDown == 6) ||
                (game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x - 1].perPtr &&
                 game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x - 1].perPtr->getSteps().stepLeftRight == 0 &&
                 game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x - 1].perPtr->getSteps().stepUpDown == 12)))
            return 0;
        if (this->steps.stepLeftRight == 9)
            k = 0;
        else if (this->steps.stepLeftRight == 3)
            k = 1;
        if (this->steps.stepLeftRight != 0 &&
                ((game->getMap()[(this->coords.y) * WIDTH + this->coords.x - 1 + k].perPtr &&
             game->getMap()[(this->coords.y) * WIDTH + this->coords.x - 1 + k].perPtr->alive &&
             game->getMap()[(this->coords.y) * WIDTH + this->coords.x - 1 + k].perPtr != this) ||
                (game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x - 1 + k].perPtr &&
                 game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x - 1 + k].perPtr->getSteps().stepLeftRight == 9 &&
                 game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x - 1 + k].perPtr->getSteps().stepUpDown == 6) ||
                (game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x - 1 + k].perPtr &&
                 game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x - 1 + k].perPtr->getSteps().stepLeftRight == 9 &&
                 game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x - 1 + k].perPtr->getSteps().stepUpDown == 12)  ||
                (game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x - 2 + k].perPtr &&
                 game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x - 2 + k].perPtr->getSteps().stepLeftRight == 3 &&
                 game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x - 2 + k].perPtr->getSteps().stepUpDown == 6)||
                 (game->getMap()[(this->coords.y) * WIDTH + this->coords.x - 2 + k].perPtr &&
                  game->getMap()[(this->coords.y) * WIDTH + this->coords.x - 2 + k].perPtr->getSteps().stepLeftRight == 3 &&
                  game->getMap()[(this->coords.y) * WIDTH + this->coords.x - 2 + k].perPtr->isAlive()) ||
                (game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x - 2 + k].perPtr &&
                 game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x - 2 + k].perPtr->getSteps().stepLeftRight == 3 &&
                 game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x - 2 + k].perPtr->getSteps().stepUpDown == 12)))
            return 0;
            if (this->steps.stepLeftRight == 0 &&
                ((game->getMap()[(this->coords.y) * WIDTH + this->coords.x - 1].perPtr &&
                  !game->getMap()[(this->coords.y) * WIDTH + this->coords.x - 1].perPtr->isAlive() &&
                  game->getMap()[(this->coords.y) * WIDTH + this->coords.x - 1].perPtr->steps.stepLeftRight == 0)))
            {
                if (game->getMap()[(this->coords.y) * WIDTH + this->coords.x - 1].perPtr->canMoveLeft(game, n + 1))
                    return 2;
                return 0;
            }
            if (this->steps.stepLeftRight != 0 &&
                    (game->getMap()[(this->coords.y) * WIDTH + this->coords.x - 1 + k].perPtr &&
                  !game->getMap()[(this->coords.y) * WIDTH + this->coords.x - 1 + k].perPtr->isAlive() &&
                  game->getMap()[(this->coords.y) * WIDTH + this->coords.x - 1 + k].perPtr->steps.stepLeftRight == 9))
            {
                if (game->getMap()[(this->coords.y) * WIDTH + this->coords.x - 1 + k].perPtr->canMoveLeft(game, n + 1))
                    return 2;
                return 0;
            }

            if (this->steps.stepLeftRight != 0 &&
                    (game->getMap()[(this->coords.y) * WIDTH + this->coords.x - 2 + k].perPtr &&
                  !game->getMap()[(this->coords.y) * WIDTH + this->coords.x - 2 + k].perPtr->isAlive() &&
                  game->getMap()[(this->coords.y) * WIDTH + this->coords.x - 2 + k].perPtr->steps.stepLeftRight == 3))
            {
                if (game->getMap()[(this->coords.y) * WIDTH + this->coords.x - 2 + k].perPtr->canMoveLeft(game, n + 1))
                    return 3;
                return 0;
            }
    }
     else
    {
            int j = 0;
            int k = 0;
        if (this->steps.stepUpDown == 12)
                j = 0;
            else if (this->steps.stepUpDown == 6)
                j = 1;
        if (this->steps.stepLeftRight == 0 &&
                ((game->getMap()[(this->coords.y + j) * WIDTH + this->coords.x - 1].objPtr &&
                     !(game->getMap()[(this->coords.y + j) * WIDTH + this->coords.x - 1].objPtr->isWalkable())) ||
                (game->getMap()[(this->coords.y - 1 + j) * WIDTH + this->coords.x - 1].objPtr &&
                                     !(game->getMap()[(this->coords.y - 1 + j) * WIDTH + this->coords.x - 1].objPtr->isWalkable())) ||
                        (game->getMap()[(this->coords.y + j) * WIDTH + this->coords.x - 1].perPtr &&
                         game->getMap()[(this->coords.y + j) * WIDTH + this->coords.x - 1].perPtr->getSteps().stepLeftRight != 9 &&
                          game->getMap()[(this->coords.y + j) * WIDTH + this->coords.x - 1].perPtr->getSteps().stepUpDown != 6) ||
                (game->getMap()[(this->coords.y - 1 + j) * WIDTH + this->coords.x - 1].perPtr &&
                 game->getMap()[(this->coords.y - 1 + j) * WIDTH + this->coords.x - 1].perPtr->getSteps().stepLeftRight != 9 &&
                  game->getMap()[(this->coords.y - 1 + j) * WIDTH + this->coords.x - 1].perPtr->getSteps().stepUpDown != 12)))
            return 0;
        if (this->steps.stepLeftRight == 9)
            k = 0;
        else if (this->steps.stepLeftRight == 3)
            k = 1;
        if (this->steps.stepLeftRight != 0 &&
                        ((game->getMap()[(this->coords.y + j) * WIDTH + this->coords.x - 1 + k].perPtr &&
                          game->getMap()[(this->coords.y + j) * WIDTH + this->coords.x - 1 + k].perPtr != this &&
                          game->getMap()[(this->coords.y + j) * WIDTH + this->coords.x - 1 + k].perPtr->getSteps().stepUpDown != 6) ||
                (game->getMap()[(this->coords.y - 1 + j) * WIDTH + this->coords.x - 1 + k].perPtr &&
                 game->getMap()[(this->coords.y - 1 + j) * WIDTH + this->coords.x - 1 + k].perPtr != this &&
                  game->getMap()[(this->coords.y - 1 + j) * WIDTH + this->coords.x - 1 + k].perPtr->getSteps().stepUpDown != 12) ||
                         (game->getMap()[(this->coords.y + j) * WIDTH + this->coords.x - 2 + k].perPtr &&
                           game->getMap()[(this->coords.y + j) * WIDTH + this->coords.x - 2 + k].perPtr->getSteps().stepUpDown != 6 &&
                          game->getMap()[(this->coords.y + j) * WIDTH + this->coords.x - 2 + k].perPtr->getSteps().stepLeftRight == 3) ||
                         (game->getMap()[(this->coords.y - 1 + j) * WIDTH + this->coords.x - 2 + k].perPtr &&
                           game->getMap()[(this->coords.y - 1 + j) * WIDTH + this->coords.x - 2 + k].perPtr->getSteps().stepUpDown != 12 &&
                          game->getMap()[(this->coords.y - 1 + j) * WIDTH + this->coords.x - 2 + k].perPtr->getSteps().stepLeftRight == 3)))
            return 0;

    }
    return 1;
}

int Personage::canMoveRight(Game *game, int n)
{
    if (this->steps.stepUpDown == 0)
    {
        int k = 0;
        if (this->steps.stepLeftRight == 0 && ((game->getMap()[(this->coords.y) * WIDTH + this->coords.x + 1].objPtr &&
             !(game->getMap()[(this->coords.y) * WIDTH + this->coords.x + 1].objPtr->isWalkable())) ||
              (game->getMap()[(this->coords.y) * WIDTH + this->coords.x + 1].perPtr &&
               game->getMap()[(this->coords.y) * WIDTH + this->coords.x + 1].perPtr->alive &&
               game->getMap()[(this->coords.y) * WIDTH + this->coords.x + 1].perPtr->getSteps().stepLeftRight == 0) ||
          (game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x + 1].perPtr &&
           game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x + 1].perPtr->getSteps().stepLeftRight == 0 &&
           game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x + 1].perPtr->getSteps().stepUpDown == 6) ||
          (game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x + 1].perPtr &&
           game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x + 1].perPtr->getSteps().stepLeftRight == 0 &&
           game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x + 1].perPtr->getSteps().stepUpDown == 12)))
            return 0;
        if (this->steps.stepLeftRight == 3)
            k = 0;
        else if (this->steps.stepLeftRight == 9)
            k = 1;
        if (this->steps.stepLeftRight != 0 &&
                ((game->getMap()[(this->coords.y) * WIDTH + this->coords.x + 1 - k].perPtr &&
                  game->getMap()[(this->coords.y) * WIDTH + this->coords.x + 1 - k].perPtr->alive &&
                  game->getMap()[(this->coords.y) * WIDTH + this->coords.x + 1 - k].perPtr != this) ||
             (game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x + 1 - k].perPtr &&
              game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x + 1 - k].perPtr->getSteps().stepLeftRight == 3 &&
              game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x + 1 - k].perPtr->getSteps().stepUpDown == 6) ||
             (game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x + 1 - k].perPtr &&
              game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x + 1 - k].perPtr->getSteps().stepLeftRight == 3 &&
              game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x + 1 - k].perPtr->getSteps().stepUpDown == 12)  ||
             (game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x + 2 - k].perPtr &&
              game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x + 2 - k].perPtr->getSteps().stepLeftRight == 9 &&
              game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x + 2 - k].perPtr->getSteps().stepUpDown == 6)||
                 (game->getMap()[(this->coords.y) * WIDTH + this->coords.x + 2 - k].perPtr &&
                  game->getMap()[(this->coords.y) * WIDTH + this->coords.x + 2 - k].perPtr->getSteps().stepLeftRight == 9 &&
                  game->getMap()[(this->coords.y) * WIDTH + this->coords.x + 2 - k].perPtr->isAlive()) ||
             (game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x + 2 - k].perPtr &&
              game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x + 2 - k].perPtr->getSteps().stepLeftRight == 9 &&
              game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x + 2 - k].perPtr->getSteps().stepUpDown == 12)))
            return 0;
            if (this->steps.stepLeftRight == 0 &&
                ((game->getMap()[(this->coords.y) * WIDTH + this->coords.x + 1].perPtr &&
                 !game->getMap()[(this->coords.y) * WIDTH + this->coords.x + 1].perPtr->isAlive() &&
                  game->getMap()[(this->coords.y) * WIDTH + this->coords.x + 1].perPtr->steps.stepLeftRight == 0)))
            {
                if (game->getMap()[(this->coords.y) * WIDTH + this->coords.x + 1].perPtr->canMoveRight(game, n + 1))
                    return 2;
                return 0;
            }
            if (this->steps.stepLeftRight != 0 &&
                    (game->getMap()[(this->coords.y) * WIDTH + this->coords.x + 1 - k].perPtr &&
                    !game->getMap()[(this->coords.y) * WIDTH + this->coords.x + 1 - k].perPtr->isAlive() &&
                     game->getMap()[(this->coords.y) * WIDTH + this->coords.x + 1 - k].perPtr->steps.stepLeftRight == 3))
            {
                if (game->getMap()[(this->coords.y) * WIDTH + this->coords.x + 1 - k].perPtr->canMoveRight(game, n + 1))
                    return 2;
                return 0;
            }

            if (this->steps.stepLeftRight != 0 &&
                    (game->getMap()[(this->coords.y) * WIDTH + this->coords.x + 2 - k].perPtr &&
                    !game->getMap()[(this->coords.y) * WIDTH + this->coords.x + 2 - k].perPtr->isAlive() &&
                     game->getMap()[(this->coords.y) * WIDTH + this->coords.x + 2 - k].perPtr->steps.stepLeftRight == 9))
            {
                if (game->getMap()[(this->coords.y) * WIDTH + this->coords.x + 2 - k].perPtr->canMoveRight(game, n + 1))
                    return 3;
                return 0;
            }
    }
     else
    {
            int j = 0;
            int k = 0;
        if (this->steps.stepUpDown == 12)
                j = 0;
            else if (this->steps.stepUpDown == 6)
                j = 1;
        if (this->steps.stepLeftRight == 0 &&
                ((game->getMap()[(this->coords.y - 1 + j) * WIDTH + this->coords.x + 1].objPtr &&
                !(game->getMap()[(this->coords.y - 1 + j) * WIDTH + this->coords.x + 1].objPtr->isWalkable())) ||
             (game->getMap()[(this->coords.y + j) * WIDTH + this->coords.x + 1].objPtr &&
            !(game->getMap()[(this->coords.y + j) * WIDTH + this->coords.x + 1].objPtr->isWalkable())) ||
             (game->getMap()[(this->coords.y + j) * WIDTH + this->coords.x + 1].perPtr &&
              game->getMap()[(this->coords.y + j) * WIDTH + this->coords.x + 1].perPtr->getSteps().stepLeftRight != 3 &&
              game->getMap()[(this->coords.y + j) * WIDTH + this->coords.x + 1].perPtr->getSteps().stepUpDown != 6) ||
         (game->getMap()[(this->coords.y - 1 + j) * WIDTH + this->coords.x + 1].perPtr &&
          game->getMap()[(this->coords.y - 1 + j) * WIDTH + this->coords.x + 1].perPtr->getSteps().stepLeftRight != 3 &&
          game->getMap()[(this->coords.y - 1 + j) * WIDTH + this->coords.x + 1].perPtr->getSteps().stepUpDown != 12)))
            return 0;
        if (this->steps.stepLeftRight == 3)
            k = 0;
        else if (this->steps.stepLeftRight == 9)
            k = 1;
        if (this->steps.stepLeftRight != 0 &&
                ((game->getMap()[(this->coords.y + j) * WIDTH + this->coords.x + 1 - k].perPtr &&
                  game->getMap()[(this->coords.y + j) * WIDTH + this->coords.x + 1 - k].perPtr != this &&
                  game->getMap()[(this->coords.y + j) * WIDTH + this->coords.x + 1 - k].perPtr->getSteps().stepUpDown != 6) ||
             (game->getMap()[(this->coords.y - 1 + j) * WIDTH + this->coords.x + 1 - k].perPtr &&
              game->getMap()[(this->coords.y - 1 + j) * WIDTH + this->coords.x + 1 - k].perPtr != this &&
              game->getMap()[(this->coords.y - 1 + j) * WIDTH + this->coords.x + 1 - k].perPtr->getSteps().stepUpDown != 12) ||
                 (game->getMap()[(this->coords.y + j) * WIDTH + this->coords.x + 2 - k].perPtr &&
                  game->getMap()[(this->coords.y + j) * WIDTH + this->coords.x + 2 - k].perPtr->getSteps().stepUpDown != 6 &&
                  game->getMap()[(this->coords.y + j) * WIDTH + this->coords.x + 2 - k].perPtr->getSteps().stepLeftRight == 9) ||
             (game->getMap()[(this->coords.y - 1 + j) * WIDTH + this->coords.x + 2 - k].perPtr &&
              game->getMap()[(this->coords.y - 1 + j) * WIDTH + this->coords.x + 2 - k].perPtr->getSteps().stepUpDown != 12 &&
              game->getMap()[(this->coords.y - 1 + j) * WIDTH + this->coords.x + 2 - k].perPtr->getSteps().stepLeftRight == 9)))
            return 0;

    }
    return 1;
}

int Personage::canMoveUp(Game *game, int n)
{
    if (this->steps.stepLeftRight == 0)
    {
        int k = 0;
        if (this->steps.stepUpDown == 0 && ((game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x].objPtr &&
             !(game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x].objPtr->isWalkable())) ||
              (game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x].perPtr &&
               game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x].perPtr->alive &&
               game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x].perPtr->getSteps().stepUpDown == 0) ||
          (game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x - 1].perPtr &&
           game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x - 1].perPtr->getSteps().stepUpDown == 0 &&
           game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x - 1].perPtr->getSteps().stepLeftRight == 3) ||
          (game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x + 1].perPtr &&
           game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x + 1].perPtr->getSteps().stepUpDown == 0 &&
           game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x + 1].perPtr->getSteps().stepLeftRight == 9)))
            return 0;
        if (this->steps.stepUpDown == 12)
            k = 0;
        else if (this->steps.stepUpDown == 6)
            k = 1;
        if (this->steps.stepUpDown != 0 &&
                ((game->getMap()[(this->coords.y - 1 + k) * WIDTH + this->coords.x].perPtr &&
                  game->getMap()[(this->coords.y - 1 + k) * WIDTH + this->coords.x].perPtr->alive &&
                  game->getMap()[(this->coords.y - 1 + k) * WIDTH + this->coords.x].perPtr != this) ||
             (game->getMap()[(this->coords.y - 1 + k) * WIDTH + this->coords.x - 1].perPtr &&
              game->getMap()[(this->coords.y - 1 + k) * WIDTH + this->coords.x - 1].perPtr->getSteps().stepLeftRight == 3 &&
              game->getMap()[(this->coords.y - 1 + k) * WIDTH + this->coords.x - 1].perPtr->getSteps().stepUpDown == 12) ||
             (game->getMap()[(this->coords.y - 1 + k) * WIDTH + this->coords.x + 1].perPtr &&
              game->getMap()[(this->coords.y - 1 + k) * WIDTH + this->coords.x + 1].perPtr->getSteps().stepLeftRight == 9 &&
              game->getMap()[(this->coords.y - 1 + k) * WIDTH + this->coords.x + 1].perPtr->getSteps().stepUpDown == 12)  ||
                 ((this->coords.y - 2 + k >= 0) &&
             ((game->getMap()[(this->coords.y - 2 + k) * WIDTH + this->coords.x - 1].perPtr &&
              game->getMap()[(this->coords.y - 2 + k) * WIDTH + this->coords.x - 1].perPtr->getSteps().stepLeftRight == 3 &&
              game->getMap()[(this->coords.y - 2 + k) * WIDTH + this->coords.x - 1].perPtr->getSteps().stepUpDown == 6)||
                 (game->getMap()[(this->coords.y - 2 + k) * WIDTH + this->coords.x].perPtr &&
                  game->getMap()[(this->coords.y - 2 + k) * WIDTH + this->coords.x].perPtr->getSteps().stepUpDown == 6 &&
                  game->getMap()[(this->coords.y - 2 + k) * WIDTH + this->coords.x].perPtr->isAlive()) ||
             (game->getMap()[(this->coords.y - 2 + k) * WIDTH + this->coords.x + 1].perPtr &&
              game->getMap()[(this->coords.y - 2 + k) * WIDTH + this->coords.x + 1].perPtr->getSteps().stepLeftRight == 9 &&
              game->getMap()[(this->coords.y - 2 + k) * WIDTH + this->coords.x + 1].perPtr->getSteps().stepUpDown == 6)))))
            return 0;
            if (this->steps.stepUpDown == 0 &&
                ((game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x].perPtr &&
                 !game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x].perPtr->isAlive() &&
                  game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x].perPtr->steps.stepUpDown == 0)))
            {
                if (game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x].perPtr->canMoveUp(game, n + 1))
                    return 2;
                return 0;
            }
            if (this->steps.stepUpDown != 0 &&
                    (game->getMap()[(this->coords.y - 1 + k) * WIDTH + this->coords.x].perPtr &&
                    !game->getMap()[(this->coords.y - 1 + k) * WIDTH + this->coords.x].perPtr->isAlive() &&
                     game->getMap()[(this->coords.y - 1 + k) * WIDTH + this->coords.x].perPtr->steps.stepUpDown == 12))
            {
                if (game->getMap()[(this->coords.y - 1 + k) * WIDTH + this->coords.x].perPtr->canMoveUp(game, n + 1))
                    return 2;
                return 0;
            }

            if (this->coords.y > 1 && this->steps.stepUpDown != 0 &&
                    (game->getMap()[(this->coords.y - 2 + k) * WIDTH + this->coords.x].perPtr &&
                    !game->getMap()[(this->coords.y - 2 + k) * WIDTH + this->coords.x].perPtr->isAlive() &&
                     game->getMap()[(this->coords.y - 2 + k) * WIDTH + this->coords.x].perPtr->steps.stepUpDown == 6))
            {
                if (game->getMap()[(this->coords.y - 2 + k) * WIDTH + this->coords.x].perPtr->canMoveUp(game, n + 1))
                    return 3;
                return 0;
            }
    }
     else
    {
            int j = 0;
            int k = 0;
        if (this->steps.stepLeftRight == 3)
                j = 0;
            else if (this->steps.stepLeftRight == 9)
                j = 1;
        if (this->steps.stepUpDown == 0 &&
                ((game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x - j].objPtr &&
                !(game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x - j].objPtr->isWalkable())) ||
             (game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x + 1 - j].objPtr &&
            !(game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x + 1 - j].objPtr->isWalkable())) ||
             (game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x - j].perPtr &&
              game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x - j].perPtr->getSteps().stepLeftRight != 9 &&
              game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x - j].perPtr->getSteps().stepUpDown != 12) ||
         (game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x + 1 - j].perPtr &&
          game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x + 1 - j].perPtr->getSteps().stepLeftRight != 3 &&
          game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x + 1 - j].perPtr->getSteps().stepUpDown != 12)))
            return 0;
        if (this->steps.stepUpDown == 12)
            k = 0;
        else if (this->steps.stepUpDown == 6)
            k = 1;
        if (this->steps.stepUpDown != 0 &&
                        ((game->getMap()[(this->coords.y - 1 + k) * WIDTH + this->coords.x - j].perPtr &&
                          game->getMap()[(this->coords.y - 1 + k) * WIDTH + this->coords.x - j].perPtr != this &&
                          game->getMap()[(this->coords.y - 1 + k) * WIDTH + this->coords.x - j].perPtr->getSteps().stepLeftRight != 9) ||
                (game->getMap()[(this->coords.y - 1 + k) * WIDTH + this->coords.x + 1 - j].perPtr &&
                 game->getMap()[(this->coords.y - 1 + k) * WIDTH + this->coords.x + 1 - j].perPtr != this &&
                  game->getMap()[(this->coords.y - 1 + k) * WIDTH + this->coords.x + 1 - j].perPtr->getSteps().stepLeftRight != 3) ||
                         ((this->coords.y > 1) &&
                         ((game->getMap()[(this->coords.y - 2 + k) * WIDTH + this->coords.x - j].perPtr &&
                           game->getMap()[(this->coords.y - 2 + k) * WIDTH + this->coords.x - j].perPtr->getSteps().stepLeftRight != 9 &&
                          game->getMap()[(this->coords.y  - 2 + k) * WIDTH + this->coords.x - j].perPtr->getSteps().stepUpDown == 6) ||
                         (game->getMap()[(this->coords.y - 2 + k) * WIDTH + this->coords.x + 1 - j].perPtr &&
                           game->getMap()[(this->coords.y - 2 + k) * WIDTH + this->coords.x + 1 - j].perPtr->getSteps().stepLeftRight != 3 &&
                          game->getMap()[(this->coords.y - 2 + k) * WIDTH + this->coords.x + 1 - j].perPtr->getSteps().stepUpDown == 6)))))
            return 0;

    }
    return 1;
}

int Personage::canMoveDown(Game *game, int n)
{
    if (this->steps.stepLeftRight == 0)
    {
        int k = 0;
        if (this->steps.stepUpDown == 0 && ((game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x].objPtr &&
             !(game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x].objPtr->isWalkable())) ||
              (game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x].perPtr &&
               game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x].perPtr->alive &&
               game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x].perPtr->getSteps().stepUpDown == 0) ||
          (game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x - 1].perPtr &&
           game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x - 1].perPtr->getSteps().stepUpDown == 0 &&
           game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x - 1].perPtr->getSteps().stepLeftRight == 3) ||
          (game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x + 1].perPtr &&
           game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x + 1].perPtr->getSteps().stepUpDown == 0 &&
           game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x + 1].perPtr->getSteps().stepLeftRight == 9)))
            return 0;
        if (this->steps.stepUpDown == 6)
            k = 0;
        else if (this->steps.stepUpDown == 12)
            k = 1;
        if (this->steps.stepUpDown != 0 &&
                ((game->getMap()[(this->coords.y + 1 - k) * WIDTH + this->coords.x].perPtr &&
                  game->getMap()[(this->coords.y + 1 - k) * WIDTH + this->coords.x].perPtr->alive &&
                  game->getMap()[(this->coords.y + 1 - k) * WIDTH + this->coords.x].perPtr != this) ||
             (game->getMap()[(this->coords.y + 1 - k) * WIDTH + this->coords.x - 1].perPtr &&
              game->getMap()[(this->coords.y + 1 - k) * WIDTH + this->coords.x - 1].perPtr->getSteps().stepLeftRight == 3 &&
              game->getMap()[(this->coords.y + 1 - k) * WIDTH + this->coords.x - 1].perPtr->getSteps().stepUpDown == 6) ||
             (game->getMap()[(this->coords.y + 1 - k) * WIDTH + this->coords.x + 1].perPtr &&
              game->getMap()[(this->coords.y + 1 - k) * WIDTH + this->coords.x + 1].perPtr->getSteps().stepLeftRight == 9 &&
              game->getMap()[(this->coords.y + 1 - k) * WIDTH + this->coords.x + 1].perPtr->getSteps().stepUpDown == 6)  ||
             (game->getMap()[(this->coords.y + 2 - k) * WIDTH + this->coords.x - 1].perPtr &&
              game->getMap()[(this->coords.y + 2 - k) * WIDTH + this->coords.x - 1].perPtr->getSteps().stepLeftRight == 3 &&
              game->getMap()[(this->coords.y + 2 - k) * WIDTH + this->coords.x - 1].perPtr->getSteps().stepUpDown == 12)||
                 (game->getMap()[(this->coords.y + 2 - k) * WIDTH + this->coords.x].perPtr &&
                  game->getMap()[(this->coords.y + 2 - k) * WIDTH + this->coords.x].perPtr->getSteps().stepUpDown == 12 &&
                  game->getMap()[(this->coords.y + 2 - k) * WIDTH + this->coords.x].perPtr->isAlive()) ||
             (game->getMap()[(this->coords.y + 2 - k) * WIDTH + this->coords.x + 1].perPtr &&
              game->getMap()[(this->coords.y + 2 - k) * WIDTH + this->coords.x + 1].perPtr->getSteps().stepLeftRight == 9 &&
              game->getMap()[(this->coords.y + 2 - k) * WIDTH + this->coords.x + 1].perPtr->getSteps().stepUpDown == 12)))
            return 0;
            if (this->steps.stepUpDown == 0 &&
                ((game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x].perPtr &&
                 !game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x].perPtr->isAlive() &&
                  game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x].perPtr->steps.stepUpDown == 0)))
            {
                if (game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x].perPtr->canMoveDown(game, n + 1))
                    return 2;
                return 0;
            }
            if (this->steps.stepUpDown != 0 &&
                    (game->getMap()[(this->coords.y + 1 - k) * WIDTH + this->coords.x].perPtr &&
                    !game->getMap()[(this->coords.y + 1 - k) * WIDTH + this->coords.x].perPtr->isAlive() &&
                     game->getMap()[(this->coords.y + 1 - k) * WIDTH + this->coords.x].perPtr->steps.stepUpDown == 6))
            {
                if (game->getMap()[(this->coords.y + 1 - k) * WIDTH + this->coords.x].perPtr->canMoveDown(game, n + 1))
                    return 2;
                return 0;
            }

            if (this->steps.stepUpDown != 0 &&
                    (game->getMap()[(this->coords.y + 2 - k) * WIDTH + this->coords.x].perPtr &&
                    !game->getMap()[(this->coords.y + 2 - k) * WIDTH + this->coords.x].perPtr->isAlive() &&
                     game->getMap()[(this->coords.y + 2 - k) * WIDTH + this->coords.x].perPtr->steps.stepUpDown == 12))
            {
                if (game->getMap()[(this->coords.y + 2 - k) * WIDTH + this->coords.x].perPtr->canMoveDown(game, n + 1))
                    return 3;
                return 0;
            }
    }
     else
    {
            int j = 0;
            int k = 0;
        if (this->steps.stepLeftRight == 3)
                j = 0;
            else if (this->steps.stepLeftRight == 9)
                j = 1;
        if (this->steps.stepUpDown == 0 &&
                ((game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x - j].objPtr &&
                !(game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x - j].objPtr->isWalkable())) ||
             (game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x + 1 - j].objPtr &&
            !(game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x + 1 - j].objPtr->isWalkable())) ||
             (game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x - j].perPtr &&
              game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x - j].perPtr->getSteps().stepLeftRight != 9 &&
              game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x - j].perPtr->getSteps().stepUpDown != 6) ||
         (game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x + 1 - j].perPtr &&
          game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x + 1 - j].perPtr->getSteps().stepLeftRight != 3 &&
          game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x + 1 - j].perPtr->getSteps().stepUpDown != 6)))
            return 0;
        if (this->steps.stepUpDown == 6)
            k = 0;
        else if (this->steps.stepUpDown == 12)
            k = 1;
        if (this->steps.stepUpDown != 0 &&
                        ((game->getMap()[(this->coords.y + 1 - k) * WIDTH + this->coords.x - j].perPtr &&
                          game->getMap()[(this->coords.y + 1 - k) * WIDTH + this->coords.x - j].perPtr != this &&
                          game->getMap()[(this->coords.y + 1 - k) * WIDTH + this->coords.x - j].perPtr->getSteps().stepLeftRight != 9) ||
                (game->getMap()[(this->coords.y + 1 - k) * WIDTH + this->coords.x + 1 - j].perPtr &&
                 game->getMap()[(this->coords.y + 1 - k) * WIDTH + this->coords.x + 1 - j].perPtr != this &&
                  game->getMap()[(this->coords.y + 1 - k) * WIDTH + this->coords.x + 1 - j].perPtr->getSteps().stepLeftRight != 3) ||
                         (game->getMap()[(this->coords.y + 2 - k) * WIDTH + this->coords.x - j].perPtr &&
                           game->getMap()[(this->coords.y + 2 - k) * WIDTH + this->coords.x - j].perPtr->getSteps().stepLeftRight != 9 &&
                          game->getMap()[(this->coords.y + 2 - k) * WIDTH + this->coords.x - j].perPtr->getSteps().stepUpDown == 12) ||
                         (game->getMap()[(this->coords.y + 2 - k) * WIDTH + this->coords.x + 1 - j].perPtr &&
                           game->getMap()[(this->coords.y + 2 - k) * WIDTH + this->coords.x + 1 - j].perPtr->getSteps().stepLeftRight != 3 &&
                          game->getMap()[(this->coords.y + 2 - k) * WIDTH + this->coords.x + 1 - j].perPtr->getSteps().stepUpDown == 12)))
            return 0;

    }
    return 1;
}

void Personage::moveLeft(Game *game, QTimer *timer)
{
    int *x1 = new int;
    int *y1 = new int;
    int *x2 = new int;
    int *y2 = new int;
    static int steps = 0;
    static bool mooving = false;
    this->pImage.rect.getCoords(x1, y1, x2, y2);
    if (this->canMoveLeft(game))
    {
        Personage *p = nullptr;
        if (this->canMoveLeft(game) > 1)
        {
            mooving = true;
            if (this->canMoveLeft(game) == 2)
                p = game->getMap()[this->coords.y * WIDTH + this->coords.x - 1].perPtr;
            else
                p = game->getMap()[this->coords.y * WIDTH + this->coords.x - 2].perPtr;
        }
        this->pImage.rect.moveLeft(*x1 - SIZE/32);

        if (mooving && p)
        {
            p->pImage.rect.getCoords(x1, y1, x2, y2);
            p->pImage.rect.moveLeft(*x1 - SIZE/32);
        }
        steps+=SIZE / 32;
        if (steps >= SIZE/32*2 && steps < SIZE/32*4)
        {
            this->imgName = "lololeft1";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pImage.pixmap = QPixmap(path.c_str());
        }
        else if (steps >= SIZE/32*4 && steps < SIZE/32*6)
        {
            this->imgName = "lololeft2";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pImage.pixmap = QPixmap(path.c_str());
        }
        else if (steps >= SIZE/32*6 && steps < SIZE/32*8)
        {
            this->imgName = "lololeft1";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pImage.pixmap = QPixmap(path.c_str());
        }
        else if (steps >= SIZE/32*8 && steps < SIZE/32*10)
        {
            this->imgName = "lololeft3";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pImage.pixmap = QPixmap(path.c_str());
        }
        else if (steps >= SIZE/32*10 && steps < SIZE/32*12)
        {
            this->imgName = "lololeft4";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pImage.pixmap = QPixmap(path.c_str());
        }
        else if (steps >= SIZE/32*12 && steps < SIZE/32*14)
        {
            this->imgName = "lololeft3";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pImage.pixmap = QPixmap(path.c_str());
        }
        else if (steps >= SIZE/32*14 && steps < SIZE/32*16)
        {
            this->imgName = "lololeft";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pImage.pixmap = QPixmap(path.c_str());
        }
        else if (steps == SIZE/2)
        {
            if (this->steps.stepLeftRight)
            {
                if (this->steps.stepLeftRight == 9)
                {
                    if (mooving && p)
                    {
                        if (this->canMoveLeft(game) == 2)
                        {
                            p->coords.x--;
                            game->getMap()[p->coords.y * WIDTH + p->coords.x].perPtr = p;
                            game->getMap()[p->coords.y * WIDTH + p->coords.x + 1].perPtr = nullptr;
                        }
                    }
                    this->coords.x--;
                    if (game->getMap()[this->coords.y * WIDTH + this->coords.x + 1].perPtr == this)
                    game->getMap()[this->coords.y * WIDTH + this->coords.x + 1].perPtr = nullptr;
                    if (this->steps.stepUpDown == 12 && game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x + 1].perPtr == this)
                        game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x + 1].perPtr = nullptr;
                    if (this->steps.stepUpDown == 6 && game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x + 1].perPtr == this)
                        game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x + 1].perPtr = nullptr;
                    if (!game->getMap()[this->coords.y * WIDTH + this->coords.x].perPtr)
                    game->getMap()[this->coords.y * WIDTH + this->coords.x].perPtr = this;
                }
                {
                    if (mooving && p)
                        p->steps.stepLeftRight = 0;
                        this->steps.stepLeftRight = 0;
                }
            }
        else
            {
                if (mooving && p)
                    p->steps.stepLeftRight = 9;
                this->steps.stepLeftRight = 9;
            }
        steps = 0;
        timer->stop();
        mooving = false;
        p = nullptr;
        }
    }
    else
        timer->stop();
    delete x1;
    delete x2;
    delete y1;
    delete y2;
}

void Personage::moveRight(Game *game, QTimer *timer)
{
    int *x1 = new int;
    int *y1 = new int;
    int *x2 = new int;
    int *y2 = new int;
    static int steps = 0;
    static bool mooving = false;
    this->pImage.rect.getCoords(x1, y1, x2, y2);
    if (this->canMoveRight(game))
    {
        Personage *p = nullptr;
        if (this->canMoveRight(game) > 1)
        {
            mooving = true;
            if (this->canMoveRight(game) == 2)
                p = game->getMap()[this->coords.y * WIDTH + this->coords.x + 1].perPtr;
            else
                p = game->getMap()[this->coords.y * WIDTH + this->coords.x + 2].perPtr;
        }
        this->pImage.rect.moveLeft(*x1 + SIZE/32);

        if (mooving && p)
        {
            p->pImage.rect.getCoords(x1, y1, x2, y2);
            p->pImage.rect.moveLeft(*x1 + SIZE/32);
        }
        steps+=SIZE / 32;
        if (steps >= SIZE/32*2 && steps < SIZE/32*4)
        {
            this->imgName = "loloright1";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pImage.pixmap = QPixmap(path.c_str());
        }
        else if (steps >= SIZE/32*4 && steps < SIZE/32*6)
        {
            this->imgName = "loloright2";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pImage.pixmap = QPixmap(path.c_str());
        }
        else if (steps >= SIZE/32*6 && steps < SIZE/32*8)
        {
            this->imgName = "loloright1";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pImage.pixmap = QPixmap(path.c_str());
        }
        else if (steps >= SIZE/32*8 && steps < SIZE/32*10)
        {
            this->imgName = "loloright3";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pImage.pixmap = QPixmap(path.c_str());
        }
        else if (steps >= SIZE/32*10 && steps < SIZE/32*12)
        {
            this->imgName = "loloright4";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pImage.pixmap = QPixmap(path.c_str());
        }
        else if (steps >= SIZE/32*12 && steps < SIZE/32*14)
        {
            this->imgName = "loloright3";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pImage.pixmap = QPixmap(path.c_str());
        }
        else if (steps >= SIZE/32*14 && steps < SIZE/32*16)
        {
            this->imgName = "loloright";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pImage.pixmap = QPixmap(path.c_str());
        }
        else if (steps == SIZE/2)
        {
            if (this->steps.stepLeftRight)
            {
                if (this->steps.stepLeftRight == 3)
                {
                    if (mooving && p)
                    {
                        if (this->canMoveRight(game) == 2)
                        {
                            p->coords.x++;
                            game->getMap()[p->coords.y * WIDTH + p->coords.x].perPtr = p;
                            game->getMap()[p->coords.y * WIDTH + p->coords.x - 1].perPtr = nullptr;
                        }
                    }
                    this->coords.x++;
                    if (game->getMap()[this->coords.y * WIDTH + this->coords.x - 1].perPtr == this)
                    game->getMap()[this->coords.y * WIDTH + this->coords.x - 1].perPtr = nullptr;
                    if (this->steps.stepUpDown == 12 && game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x - 1].perPtr == this)
                        game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x - 1].perPtr = nullptr;
                    if (this->steps.stepUpDown == 6 && game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x - 1].perPtr == this)
                        game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x - 1].perPtr = nullptr;
                    if (!game->getMap()[this->coords.y * WIDTH + this->coords.x].perPtr)
                    game->getMap()[this->coords.y * WIDTH + this->coords.x].perPtr = this;
                }
                {
                    if (mooving && p)
                        p->steps.stepLeftRight = 0;
                        this->steps.stepLeftRight = 0;
                }
            }
        else
            {
                if (mooving && p)
                    p->steps.stepLeftRight = 3;
                this->steps.stepLeftRight = 3;
            }
        steps = 0;
        timer->stop();
        mooving = false;
        }
    }
    else
        timer->stop();
    delete x1;
    delete x2;
    delete y1;
    delete y2;
}

void Personage::moveUp(Game *game, QTimer *timer)
{
    int *x1 = new int;
    int *y1 = new int;
    int *x2 = new int;
    int *y2 = new int;
    static int steps = 0;
    static bool mooving = false;
    this->pImage.rect.getCoords(x1, y1, x2, y2);
    if (this->canMoveUp(game))
    {
        Personage *p = nullptr;
        if (this->canMoveUp(game) > 1)
        {
            mooving = true;
            if (this->canMoveUp(game) == 2)
                p = game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x].perPtr;
            else
                p = game->getMap()[(this->coords.y - 2) * WIDTH + this->coords.x].perPtr;
        }
        this->pImage.rect.moveTop(*y1 - SIZE/32);

        if (mooving && p)
        {
            p->pImage.rect.getCoords(x1, y1, x2, y2);
            p->pImage.rect.moveTop(*y1 - SIZE/32);
        }
        steps+=SIZE / 32;
        if (steps >= SIZE/32*2 && steps < SIZE/32*4)
        {
            this->imgName = "loloup1";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pImage.pixmap = QPixmap(path.c_str());
        }
        else if (steps >= SIZE/32*4 && steps < SIZE/32*6)
        {
            this->imgName = "loloup2";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pImage.pixmap = QPixmap(path.c_str());
        }
        else if (steps >= SIZE/32*6 && steps < SIZE/32*8)
        {
            this->imgName = "loloup1";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pImage.pixmap = QPixmap(path.c_str());
        }
        else if (steps >= SIZE/32*8 && steps < SIZE/32*10)
        {
            this->imgName = "loloup3";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pImage.pixmap = QPixmap(path.c_str());
        }
        else if (steps >= SIZE/32*10 && steps < SIZE/32*12)
        {
            this->imgName = "loloup4";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pImage.pixmap = QPixmap(path.c_str());
        }
        else if (steps >= SIZE/32*12 && steps < SIZE/32*14)
        {
            this->imgName = "loloup3";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pImage.pixmap = QPixmap(path.c_str());
        }
        else if (steps >= SIZE/32*14 && steps < SIZE/32*16)
        {
            this->imgName = "loloup";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pImage.pixmap = QPixmap(path.c_str());
        }
        else if (steps == SIZE/2)
        {
            if (this->steps.stepUpDown)
            {
                if (this->steps.stepUpDown == 12)
                {
                    if (mooving && p)
                    {
                        if (this->canMoveUp(game) == 2)
                        {
                            p->coords.y--;
                            game->getMap()[p->coords.y * WIDTH + p->coords.x].perPtr = p;
                            game->getMap()[(p->coords.y + 1) * WIDTH + p->coords.x].perPtr = nullptr;
                        }
                    }
                    this->coords.y--;
                    if (game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x].perPtr == this)
                    game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x].perPtr = nullptr;
                    if (this->steps.stepLeftRight == 9 && game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x - 1].perPtr == this)
                        game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x - 1].perPtr = nullptr;
                    if (this->steps.stepLeftRight == 3 && game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x + 1].perPtr == this)
                        game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x + 1].perPtr = nullptr;
                    if (!game->getMap()[this->coords.y * WIDTH + this->coords.x].perPtr)
                    game->getMap()[this->coords.y * WIDTH + this->coords.x].perPtr = this;
                }
                {
                    {
                        if (mooving && p)
                            p->steps.stepUpDown = 0;
                            this->steps.stepUpDown = 0;
                    }
                }
            }
        else
            {
                if (mooving && p)
                    p->steps.stepUpDown = 12;
                this->steps.stepUpDown = 12;
            }
        steps = 0;
        timer->stop();
        mooving = false;
        }
    }
    else
        timer->stop();
    delete x1;
    delete x2;
    delete y1;
    delete y2;
}

void Personage::moveDown(Game *game, QTimer *timer)
{
    int *x1 = new int;
    int *y1 = new int;
    int *x2 = new int;
    int *y2 = new int;
    static int steps = 0;
    static bool mooving = false;
    this->pImage.rect.getCoords(x1, y1, x2, y2);
    if (this->canMoveDown(game))
    {
        Personage *p = nullptr;
        if (this->canMoveDown(game) > 1)
        {
            mooving = true;
            if (this->canMoveDown(game) == 2)
                p = game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x].perPtr;
            else
                p = game->getMap()[(this->coords.y + 2) * WIDTH + this->coords.x].perPtr;
        }
        this->pImage.rect.moveTop(*y1 + SIZE/32);

        if (mooving && p)
        {
            p->pImage.rect.getCoords(x1, y1, x2, y2);
            p->pImage.rect.moveTop(*y1 + SIZE/32);
        }
        steps+=SIZE / 32;
        if (steps >= SIZE/32*2 && steps < SIZE/32*4)
        {
            this->imgName = "lolodown1";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pImage.pixmap = QPixmap(path.c_str());
        }
        else if (steps >= SIZE/32*4 && steps < SIZE/32*6)
        {
            this->imgName = "lolodown2";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pImage.pixmap = QPixmap(path.c_str());
        }
        else if (steps >= SIZE/32*6 && steps < SIZE/32*8)
        {
            this->imgName = "lolodown1";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pImage.pixmap = QPixmap(path.c_str());
        }
        else if (steps >= SIZE/32*8 && steps < SIZE/32*10)
        {
            this->imgName = "lolodown3";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pImage.pixmap = QPixmap(path.c_str());
        }
        else if (steps >= SIZE/32*10 && steps < SIZE/32*12)
        {
            this->imgName = "lolodown4";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pImage.pixmap = QPixmap(path.c_str());
        }
        else if (steps >= SIZE/32*12 && steps < SIZE/32*14)
        {
            this->imgName = "lolodown3";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pImage.pixmap = QPixmap(path.c_str());
        }
        else if (steps >= SIZE/32*14 && steps < SIZE/32*16)
        {
            this->imgName = "lolo";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pImage.pixmap = QPixmap(path.c_str());
        }
        else if (steps == SIZE/2)
        {
            if (this->steps.stepUpDown)
            {
                if (this->steps.stepUpDown == 6)
                {
                    if (mooving && p)
                    {
                        if (this->canMoveDown(game) == 2)
                        {
                            p->coords.y++;
                            game->getMap()[p->coords.y * WIDTH + p->coords.x].perPtr = p;
                            game->getMap()[(p->coords.y - 1) * WIDTH + p->coords.x].perPtr = nullptr;
                        }
                    }
                    this->coords.y++;
                    if (game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x].perPtr == this)
                    game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x].perPtr = nullptr;
                    if (this->steps.stepLeftRight == 9 && game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x - 1].perPtr == this)
                        game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x - 1].perPtr = nullptr;
                    if (this->steps.stepLeftRight == 3 && game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x + 1].perPtr == this)
                        game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x + 1].perPtr = nullptr;
                    if (!game->getMap()[this->coords.y * WIDTH + this->coords.x].perPtr)
                    game->getMap()[this->coords.y * WIDTH + this->coords.x].perPtr = this;
                }
                {
                    if (mooving && p)
                        p->steps.stepUpDown = 0;
                        this->steps.stepUpDown = 0;
                }
            }
        else
            {
                if (mooving && p)
                    p->steps.stepUpDown = 6;
                this->steps.stepUpDown = 6;
            }
        steps = 0;
        timer->stop();
        mooving = false;
        }
    }
    else
        timer->stop();
    delete x1;
    delete x2;
    delete y1;
    delete y2;
}

int Personage::shooted(Game *game, int x, int y)
{
    if ((game->getMap()[y * WIDTH + x].objPtr || game->getMap()[y * WIDTH + x].perPtr) &&
            game->getMap()[y * WIDTH + x].perPtr != this)
    {
        if (game->getMap()[y * WIDTH + x].perPtr)
            return 2;
        if (!game->getMap()[y * WIDTH + x].objPtr->isShootable())
        {
            return 1;
        }
    }
    return 0;
}

void Personage::shootUp()
{
    int *x1 = new int;
    int *y1 = new int;
    int *x2 = new int;
    int *y2 = new int;

    static int steps = 0;

    if (!this->shoot)
    {
        this->pShoot->coords.x = this->coords.x;
        this->pShoot->coords.y = this->coords.y;
        this->pShoot->image.rect.setCoords(this->pShoot->coords.x  * SIZE,
                                           this->pShoot->coords.y * SIZE,
                                           (this->pShoot->coords.x + 1) * SIZE,
                                           (this->pShoot->coords.y + 1) * SIZE);
        this->pShoot->image.pixmap = QPixmap("C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/bulletup.png");
        this->shoot = true;
    }
    {
        this->pShoot->image.rect.getCoords(x1, y1, x2, y2);
        {
            this->pShoot->image.rect.moveTop(*y1 - 16);
            steps+=16;
            if (steps == SIZE)
            {
                this->pShoot->coords.y--;
                steps = 0;
            }
        }

    }
    delete x1;
    delete x2;
    delete y1;
    delete y2;
}

void Personage::shootDown()
{
    int *x1 = new int;
    int *y1 = new int;
    int *x2 = new int;
    int *y2 = new int;

    static int steps = 0;

    if (!this->shoot)
    {
        this->pShoot->coords.x = this->coords.x;
        this->pShoot->coords.y = this->coords.y;
        this->pShoot->image.rect.setCoords(this->pShoot->coords.x  * SIZE,
                                           this->pShoot->coords.y * SIZE,
                                           (this->pShoot->coords.x + 1) * SIZE,
                                           (this->pShoot->coords.y + 1) * SIZE);
        this->pShoot->image.pixmap = QPixmap("C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/bulletdown.png");
        this->shoot = true;
    }
    this->pShoot->image.rect.getCoords(x1, y1, x2, y2);
    {
        this->pShoot->image.rect.moveTop(*y1 + SIZE/8);
        steps+=SIZE/8;
        if (steps == SIZE)
        {
            this->pShoot->coords.y++;
            steps = 0;
        }
    }
    delete x1;
    delete x2;
    delete y1;
    delete y2;
}

void Personage::shootRight()
{
    int *x1 = new int;
    int *y1 = new int;
    int *x2 = new int;
    int *y2 = new int;

    static int steps = 0;

    if (!this->shoot)
    {
        this->pShoot->coords.x = this->coords.x;
        this->pShoot->coords.y = this->coords.y;
        this->pShoot->image.rect.setCoords(this->pShoot->coords.x  * SIZE,
                                           this->pShoot->coords.y * SIZE,
                                           (this->pShoot->coords.x + 1) * SIZE,
                                           (this->pShoot->coords.y + 1) * SIZE);
        this->pShoot->image.pixmap = QPixmap("C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/bulletright.png");
        this->shoot = true;
    }
    {
        this->pShoot->image.rect.getCoords(x1, y1, x2, y2);
        {
            this->pShoot->image.rect.moveLeft(*x1 + 16);
            steps+=16;
            if (steps == SIZE)
            {
                this->pShoot->coords.x++;
                steps = 0;
            }
        }

    }
    delete x1;
    delete x2;
    delete y1;
    delete y2;
}

void Personage::shootLeft()
{
    int *x1 = new int;
    int *y1 = new int;
    int *x2 = new int;
    int *y2 = new int;

    static int steps = 0;

    if (!this->shoot)
    {
        this->pShoot->coords.x = this->coords.x;
        this->pShoot->coords.y = this->coords.y;
        this->pShoot->image.rect.setCoords(this->pShoot->coords.x  * SIZE,
                                           this->pShoot->coords.y * SIZE,
                                           (this->pShoot->coords.x + 1) * SIZE,
                                           (this->pShoot->coords.y + 1) * SIZE);
        this->pShoot->image.pixmap = QPixmap("C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/bulletleft.png");
        this->shoot = true;
    }
    {
        this->pShoot->image.rect.getCoords(x1, y1, x2, y2);
        {
            this->pShoot->image.rect.moveLeft(*x1 - 16);
            steps+=16;
            if (steps == SIZE)
            {
                this->pShoot->coords.x--;
                steps = 0;
            }
        }

    }
    delete x1;
    delete x2;
    delete y1;
    delete y2;
}

Steps Personage::getSteps()
{
    return this->steps;
}

int Personage::getDirection()
{
    return this->direction;
}

void Personage::setDirection(int direction)
{
    this->direction = direction;
}

void Personage::setShootDirection(int shootDirection)
{
    this->pShoot->direction = shootDirection;
}


QRect Personage::getRect()
{
    return this->pImage.rect;
}

QPixmap Personage::getPixmap()
{
    std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
    path += this->imgName;
    path += ".png";
    QPixmap pixmap(path.c_str());
    this->pImage.pixmap = pixmap;
    return this->pImage.pixmap;
}

QTimer *Personage::getTimer()
{
    return this->timer;
}

void Personage::setTimer(QTimer *timer)
{
    this->timer = timer;
}

Image Personage::getSImage()
{
    return this->pShoot->image;
}

void Personage::createShoot()
{
    this->pShoot = new (Shoot);
    //this->shoot = true;
}

Shoot *Personage::getShoot()
{
    return this->pShoot;
}

void Personage::setBoolShoot(bool shoot)
{
    this->shoot = shoot;
}

void Personage::kill(Game*)
{
    this->alive = false;
    this->timer = new QTimer();
    timer->singleShot(5000, [=]() { reincarnate(); });

}

void Personage::reincarnate()
{
    this->alive = true;
}
