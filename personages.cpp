#include "personages.h"
#include "game.h"
#include <QDebug>
#include <ctime>
#include <cstdlib>
#include "widget.h"

Personage::Personage(bool shootable, int x, int y, int direction, std::string imgName):
    Object(shootable, false, imgName, x, y), alive{true}, shoot{false}, direction{direction}
{
    this->steps = new Steps;
    this->steps->stepLeftRight = 0;
    this->steps->stepUpDown = 0;
    QRect rect;
    rect.setCoords(this->coords->x * SIZE,
                   this->coords->y * SIZE,
                   (this->coords->x + 1) * SIZE,
                   (this->coords->y + 1) * SIZE);
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
    delete this->coords;
    delete this->steps;
}

bool Personage::isAlive()
{
    return this->alive;
}

bool Personage::madeShoot()
{
    return this->shoot;
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
        this->pShoot->coords.x = this->coords->x;
        this->pShoot->coords.y = this->coords->y;
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
        this->pShoot->coords.x = this->coords->x;
        this->pShoot->coords.y = this->coords->y;
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
        this->pShoot->coords.x = this->coords->x;
        this->pShoot->coords.y = this->coords->y;
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
        this->pShoot->coords.x = this->coords->x;
        this->pShoot->coords.y = this->coords->y;
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

Steps *Personage::getSteps()
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
}

Shoot *Personage::getShoot()
{
    return this->pShoot;
}

void Personage::setBoolShoot(bool shoot)
{
    this->shoot = shoot;
}

void Personage::kill()
{
    this->alive = false;
    this->timer = new QTimer();
    timer->singleShot(5000, [=]() { reincarnate(); });

}

void Personage::reincarnate()
{
    this->alive = true;
}

Personage *Personage::makePersonage(std::string choice, int x, int y)
{
    if (choice == "lolo")
        return new Lolo(x,y,6,"lolo");
    if (choice == "snakey")
        return new Snakey(x, y, 9, "snakey");
    if (choice == "gol")
        return new Gol(x,y,9,"gol");
    return nullptr;
}
