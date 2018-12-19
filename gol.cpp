#include "gol.h"


Gol::Gol(int x, int y, int direction, std::string imgName):
    Personage(true, x, y, direction, imgName)
{
    this->direction = 6;
}

void Gol::doAction()
{
    if (this->alive)
    {
        if (!this->madeShoot())
        {
            this->createShoot();
            this->setShootDirection(6);
        }
        this->shootDown();
    }
    else if (this->madeShoot())
        this->shootDown();
}
