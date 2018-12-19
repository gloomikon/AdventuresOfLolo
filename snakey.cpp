#include "snakey.h"

Snakey::Snakey(int x, int y, int direction, std::string imgName):
    Personage(true, x, y, direction, imgName)
{
    this->direction = 3;
}

void Snakey::doAction()
{
    static int count = 0;
    if (count < 50)
        count++;
    else
    {
        count = 0;
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
}
