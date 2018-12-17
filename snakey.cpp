#include "snakey.h"

Snakey::Snakey(int x, int y, int direction, std::string imgName):
    Personage(true, x, y, direction, imgName), shoots{0}, heartPicked{0}
{
    this->direction = 3;
}

void Snakey::doAction()
{
    if (this->direction == 3)
    {
        this->direction = 9;
        this->setImgName("snakeyright");
    }
    else
    {
        this->direction = 3;
        this->setImgName("snakey");
    }
}
