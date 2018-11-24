#include "personages.h"
#include "game.h"
#include "widget.h"
#include <QDebug>

Personages::Personages(bool shootable, int x, int y, int direction, QRect pRect, QPixmap pPixmap, std::string imgName):
    Objects(shootable, false, imgName), alive{true}, shoot{false}, coords{x,y}, steps{0,0}, direction{direction},
    pImage{pRect, pPixmap}
{}

bool Personages::madeShoot()
{
    return this->shoot;
}

bool Personages::canMoveLeft(Game *game)
{
    if (this->steps.stepLeftRight == 3)
        return (true);
    if (game->getMap()[this->coords.y * WIDTH + this->coords.x - 1].ptr)
    {
        if (!(game->getMap()[this->coords.y * WIDTH + this->coords.x - 1].ptr->isWalkable()))
            return (false);
    }
    if (game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x - 1].ptr)
    {
        if (this->steps.stepUpDown == 12 &&
                !(game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x - 1].ptr->isWalkable()))
            return (false);
    }
    if (game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x - 1].ptr)
    {
        if (this->steps.stepUpDown == 6 &&
                !(game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x - 1].ptr->isWalkable()))
            return (false);
    }
    return (true);
}

bool Personages::canMoveRight(Game *game)
{
    if (this->steps.stepLeftRight == 9)
        return (true);
    if (game->getMap()[this->coords.y * WIDTH + this->coords.x + 1].ptr)
    {
        if (!(game->getMap()[this->coords.y * WIDTH + this->coords.x + 1].ptr->isWalkable()))
            return (false);
    }
    if (game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x + 1].ptr)
    {
        if (this->steps.stepUpDown == 12 &&
                !(game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x + 1].ptr->isWalkable()))
            return (false);
    }
    if (game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x + 1].ptr)
    {
        if (this->steps.stepUpDown == 6 &&
                !(game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x + 1].ptr->isWalkable()))
            return (false);
    }
    return (true);
}

bool Personages::canMoveUp(Game *game)
{
    if (this->steps.stepUpDown == 6)
        return (true);
    if (game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x].ptr)
    {
        if (!(game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x].ptr->isWalkable()))
            return (false);
    }
    if (game->getMap()[(this->coords.y - 1) * WIDTH + (this->coords.x + 1)].ptr)
    {
        if (this->steps.stepLeftRight == 3 &&
                !(game->getMap()[(this->coords.y - 1) * WIDTH + (this->coords.x + 1)].ptr->isWalkable()))
            return (false);
    }
    if (game->getMap()[(this->coords.y - 1) * WIDTH + (this->coords.x - 1)].ptr)
    {
        if (this->steps.stepLeftRight == 9 &&
                !(game->getMap()[(this->coords.y - 1) * WIDTH + (this->coords.x - 1)].ptr->isWalkable()))
            return (false);
    }
    return (true);
}

bool Personages::canMoveDown(Game *game)
{
    if (this->steps.stepUpDown == 12)
        return (true);
    if (game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x].ptr)
    {
        if (!(game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x].ptr->isWalkable()))
            return (false);
    }
    if (game->getMap()[(this->coords.y + 1) * WIDTH + (this->coords.x + 1)].ptr)
    {
        if (this->steps.stepLeftRight == 3 &&
                !(game->getMap()[(this->coords.y + 1) * WIDTH + (this->coords.x + 1)].ptr->isWalkable()))
            return (false);
    }
    if (game->getMap()[(this->coords.y + 1) * WIDTH + (this->coords.x - 1)].ptr)
    {
        if (this->steps.stepLeftRight == 9 &&
                !(game->getMap()[(this->coords.y + 1) * WIDTH + (this->coords.x - 1)].ptr->isWalkable()))
            return (false);
    }
    return (true);
}

void Personages::moveLeft(Game *game, QTimer *timer)
{
    int *x1 = new int;
    int *y1 = new int;
    int *x2 = new int;
    int *y2 = new int;
    static int steps = 0;
    this->pImage.rect.getCoords(x1, y1, x2, y2);
    if (this->canMoveLeft(game))
    {
        this->pImage.rect.moveLeft(*x1 - 4);
        steps+=4;
        if (steps >= 8 && steps < 16)
        {
            this->imgName = "lololeft1";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pImage.pixmap = QPixmap(path.c_str());
        }
        else if (steps >= 16 && steps < 24)
        {
            this->imgName = "lololeft2";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pImage.pixmap = QPixmap(path.c_str());
        }
        else if (steps >= 24 && steps < 32)
        {
            this->imgName = "lololeft1";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pImage.pixmap = QPixmap(path.c_str());
        }
        else if (steps >= 32 && steps < 40)
        {
            this->imgName = "lololeft3";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pImage.pixmap = QPixmap(path.c_str());
        }
        else if (steps >= 40 && steps < 48)
        {
            this->imgName = "lololeft4";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pImage.pixmap = QPixmap(path.c_str());
        }
        else if (steps >= 48 && steps < 56)
        {
            this->imgName = "lololeft3";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pImage.pixmap = QPixmap(path.c_str());
        }
        else if (steps >= 56 && steps < 64)
        {
            this->imgName = "lololeft";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pImage.pixmap = QPixmap(path.c_str());
        }
        else if (steps == 64)
        {
            if (this->steps.stepLeftRight)
            {
                if (this->steps.stepLeftRight == 9)
                    this->coords.x--;
                game->getMap()[this->coords.y * WIDTH + this->coords.x + 1].isSome1Here = false;
                if (this->steps.stepUpDown == 12)
                    game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x + 1].isSome1Here = false;
                if (this->steps.stepUpDown == 6)
                    game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x + 1].isSome1Here = false;
                game->getMap()[this->coords.y * WIDTH + this->coords.x].isSome1Here = true;
                if (this->steps.stepUpDown == 12)
                    game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x].isSome1Here = true;
                if (this->steps.stepUpDown == 6)
                    game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x].isSome1Here = true;
                this->steps.stepLeftRight = 0;
            }
            else
                this->steps.stepLeftRight = 9;
            steps = 0;
            timer->stop();
        }
    }
    else
        timer->stop();
    delete x1;
    delete x2;
    delete y1;
    delete y2;
}

void Personages::moveRight(Game *game, QTimer *timer)
{
    int *x1 = new int;
    int *y1 = new int;
    int *x2 = new int;
    int *y2 = new int;
    static int steps = 0;
    this->pImage.rect.getCoords(x1, y1, x2, y2);
    if (this->canMoveRight(game))
    {
        this->pImage.rect.moveLeft(*x1 + 4);
        steps+=4;
        if (steps >= 8 && steps < 16)
        {
            this->imgName = "loloright1";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pImage.pixmap = QPixmap(path.c_str());
        }
        else if (steps >= 16 && steps < 24)
        {
            this->imgName = "loloright2";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pImage.pixmap = QPixmap(path.c_str());
        }
        else if (steps >= 24 && steps < 32)
        {
            this->imgName = "loloright1";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pImage.pixmap = QPixmap(path.c_str());
        }
        else if (steps >= 32 && steps < 40)
        {
            this->imgName = "loloright3";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pImage.pixmap = QPixmap(path.c_str());
        }
        else if (steps >= 40 && steps < 48)
        {
            this->imgName = "loloright4";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pImage.pixmap = QPixmap(path.c_str());
        }
        else if (steps >= 48 && steps < 56)
        {
            this->imgName = "loloright3";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pImage.pixmap = QPixmap(path.c_str());
        }
        else if (steps >= 56 && steps < 64)
        {
            this->imgName = "loloright";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pImage.pixmap = QPixmap(path.c_str());
        }
        else if (steps == 64)
        {
            if (this->steps.stepLeftRight)
            {
                if (this->steps.stepLeftRight == 3)
                    this->coords.x++;
                game->getMap()[this->coords.y * WIDTH + this->coords.x - 1].isSome1Here = false;
                if (this->steps.stepUpDown == 12)
                    game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x - 1].isSome1Here = false;
                if (this->steps.stepUpDown == 6)
                    game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x - 1].isSome1Here = false;
                game->getMap()[this->coords.y * WIDTH + this->coords.x].isSome1Here = true;
                if (this->steps.stepUpDown == 12)
                    game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x].isSome1Here = true;
                if (this->steps.stepUpDown == 6)
                    game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x].isSome1Here = true;
                this->steps.stepLeftRight = 0;
            }
            else
                this->steps.stepLeftRight = 3;
            steps = 0;
            timer->stop();
        }
    }
    else
        timer->stop();
    delete x1;
    delete x2;
    delete y1;
    delete y2;
}

void Personages::moveUp(Game *game, QTimer *timer)
{
    int *x1 = new int;
    int *y1 = new int;
    int *x2 = new int;
    int *y2 = new int;
    static int steps = 0;
    this->pImage.rect.getCoords(x1, y1, x2, y2);
    if (this->canMoveUp(game))
    {
        this->pImage.rect.moveTop(*y1 - 4);
        steps+=4;
        if (steps >= 8 && steps < 16)
        {
            this->imgName = "loloup1";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pImage.pixmap = QPixmap(path.c_str());
        }
        else if (steps >= 16 && steps < 24)
        {
            this->imgName = "loloup2";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pImage.pixmap = QPixmap(path.c_str());
        }
        else if (steps >= 24 && steps < 32)
        {
            this->imgName = "loloup1";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pImage.pixmap = QPixmap(path.c_str());
        }
        else if (steps >= 32 && steps < 40)
        {
            this->imgName = "loloup3";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pImage.pixmap = QPixmap(path.c_str());
        }
        else if (steps >= 40 && steps < 48)
        {
            this->imgName = "loloup4";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pImage.pixmap = QPixmap(path.c_str());
        }
        else if (steps >= 48 && steps < 56)
        {
            this->imgName = "loloup3";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pImage.pixmap = QPixmap(path.c_str());
        }
        else if (steps >= 56 && steps < 64)
        {
            this->imgName = "loloup";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pImage.pixmap = QPixmap(path.c_str());
        }
        else if (steps == 64)
        {
            if (this->steps.stepUpDown)
            {
                if (this->steps.stepUpDown == 12)
                {
                    this->coords.y--;
                    game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x].isSome1Here = false;
                if (this->steps.stepLeftRight == 3)
                    game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x + 1].isSome1Here = false;
                if (this->steps.stepLeftRight == 9)
                    game->getMap()[(this->coords.y + 1) * WIDTH + this->coords.x - 1].isSome1Here = false;
                game->getMap()[this->coords.y * WIDTH + this->coords.x].isSome1Here = true;
                if (this->steps.stepLeftRight == 3)
                    game->getMap()[this->coords.y * WIDTH + this->coords.x + 1].isSome1Here = true;
                if (this->steps.stepLeftRight == 9)
                    game->getMap()[this->coords.y * WIDTH + this->coords.x - 1].isSome1Here = true;
                }
                this->steps.stepUpDown = 0;
            }
            else
            {
                this->steps.stepUpDown = 12;
            }
            steps = 0;
            timer->stop();
        }
    }
    else
        timer->stop();
    delete x1;
    delete x2;
    delete y1;
    delete y2;
}

void Personages::moveDown(Game *game, QTimer *timer)
{
    int *x1 = new int;
    int *y1 = new int;
    int *x2 = new int;
    int *y2 = new int;
    static int steps = 0;
    this->pImage.rect.getCoords(x1, y1, x2, y2);
    if (this->canMoveDown(game))
    {
        this->pImage.rect.moveTop(*y1 + 4);
        steps+=4;
        if (steps >= 8 && steps < 16)
        {
            this->imgName = "lolodown1";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pImage.pixmap = QPixmap(path.c_str());
        }
        else if (steps >= 16 && steps < 24)
        {
            this->imgName = "lolodown2";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pImage.pixmap = QPixmap(path.c_str());
        }
        else if (steps >= 24 && steps < 32)
        {
            this->imgName = "lolodown1";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pImage.pixmap = QPixmap(path.c_str());
        }
        else if (steps >= 32 && steps < 40)
        {
            this->imgName = "lolodown3";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pImage.pixmap = QPixmap(path.c_str());
        }
        else if (steps >= 40 && steps < 48)
        {
            this->imgName = "lolodown4";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pImage.pixmap = QPixmap(path.c_str());
        }
        else if (steps >= 48 && steps < 56)
        {
            this->imgName = "lolodown3";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pImage.pixmap = QPixmap(path.c_str());
        }
        else if (steps >= 56 && steps < 64)
        {
            this->imgName = "lolo";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pImage.pixmap = QPixmap(path.c_str());
        }
        else if (steps == 64)
        {
            if (this->steps.stepUpDown)
            {
                if (this->steps.stepUpDown == 6)
                {
                    this->coords.y++;
                    game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x].isSome1Here = false;
                if (this->steps.stepLeftRight == 3)
                    game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x + 1].isSome1Here = false;
                if (this->steps.stepLeftRight == 9)
                    game->getMap()[(this->coords.y - 1) * WIDTH + this->coords.x - 1].isSome1Here = false;
                game->getMap()[this->coords.y * WIDTH + this->coords.x].isSome1Here = true;
                if (this->steps.stepLeftRight == 3)
                    game->getMap()[this->coords.y * WIDTH + this->coords.x + 1].isSome1Here = true;
                if (this->steps.stepLeftRight == 9)
                    game->getMap()[this->coords.y * WIDTH + this->coords.x - 1].isSome1Here = true;
                }
                this->steps.stepUpDown = 0;
            }
            else
            {
                this->steps.stepUpDown = 6;
            }
            steps = 0;
            timer->stop();
        }
    }
    else
        timer->stop();
    delete x1;
    delete x2;
    delete y1;
    delete y2;
}

int Personages::shooted(Game *game, int x, int y)
{
    if (game->getMap()[y * WIDTH + x].ptr &&
            game->getMap()[y * WIDTH + x].ptr != this)
    {
        if (dynamic_cast<Personages*>(game->getMap()[y * WIDTH + x].ptr))
            return 2;
        if (!game->getMap()[y * WIDTH + x].ptr->isShootable())
        {
            //qDebug() << "SHIT SHIT SHIT" << x << y;
            return 1;
        }
    }
    return 0;
}

void Personages::shootUp(Game *game)
{
    static int x;
    static int y;

    int *x1 = new int;
    int *y1 = new int;
    int *x2 = new int;
    int *y2 = new int;

    static int steps = 0;

    if (!this->shoot)
    {
        x = this->coords.x;
        y = this->coords.y;
        this->sImage.rect.setCoords(x  * 128,
                                    y * 128,
                                   (x + 1) * 128,
                                   (y + 1) * 128);
        this->sImage.pixmap = QPixmap("C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/bulletup.png");
        this->shoot = true;
    }
    {
        this->sImage.rect.getCoords(x1, y1, x2, y2);
        if (shooted(game, x, y))
        {
            this->timer->stop();
            this->shoot = false;
        }
        else
        {
            this->sImage.rect.moveTop(*y1 - 16);
            steps+=16;
            if (steps == 128)
            {
                y--;
                steps = 0;
            }
        }

    }
    delete x1;
    delete x2;
    delete y1;
    delete y2;
}

void Personages::shootDown(Game *game)
{
    static int x;
    static int y;

    int *x1 = new int;
    int *y1 = new int;
    int *x2 = new int;
    int *y2 = new int;

    static int steps = 0;

    if (!this->shoot)
    {
        x = this->coords.x;
        y = this->coords.y;
        this->sImage.rect.setCoords(x  * 128,
                                    y * 128,
                                   (x + 1) * 128,
                                   (y + 1) * 128);
        this->sImage.pixmap = QPixmap("C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/bulletdown.png");
        this->shoot = true;
    }
    {
        this->sImage.rect.getCoords(x1, y1, x2, y2);
        if (shooted(game, x, y))
        {
            this->timer->stop();
            this->shoot = false;
        }
        else
        {
            this->sImage.rect.moveTop(*y1 + 16);
            steps+=16;
            if (steps == 128)
            {
                y++;
                steps = 0;
            }
        }

    }
    delete x1;
    delete x2;
    delete y1;
    delete y2;
}

void Personages::shootRight(Game *game)
{
    static int x;
    static int y;

    int *x1 = new int;
    int *y1 = new int;
    int *x2 = new int;
    int *y2 = new int;

    static int steps = 0;

    if (!this->shoot)
    {
        x = this->coords.x;
        y = this->coords.y;
        this->sImage.rect.setCoords(x  * 128,
                                    y * 128,
                                   (x + 1) * 128,
                                   (y + 1) * 128);
        this->sImage.pixmap = QPixmap("C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/bulletright.png");
        this->shoot = true;
    }
    {
        this->sImage.rect.getCoords(x1, y1, x2, y2);
        if (shooted(game, x, y))
        {
            this->timer->stop();
            this->shoot = false;
        }
        else
        {
            this->sImage.rect.moveLeft(*x1 + 16);
            steps+=16;
            if (steps == 128)
            {
                x++;
                steps = 0;
            }
        }

    }
    delete x1;
    delete x2;
    delete y1;
    delete y2;
}

void Personages::shootLeft(Game *game)
{
    static int x;
    static int y;

    int *x1 = new int;
    int *y1 = new int;
    int *x2 = new int;
    int *y2 = new int;

    static int steps = 0;

    if (!this->shoot)
    {
        x = this->coords.x;
        y = this->coords.y;
        this->sImage.rect.setCoords(x  * 128,
                                    y * 128,
                                   (x + 1) * 128,
                                   (y + 1) * 128);
        this->sImage.pixmap = QPixmap("C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/bulletleft.png");
        this->shoot = true;
    }
    {
        this->sImage.rect.getCoords(x1, y1, x2, y2);
        if (shooted(game, x, y))
        {
            this->timer->stop();
            this->shoot = false;
        }
        else
        {
            this->sImage.rect.moveLeft(*x1 - 16);
            steps+=16;
            if (steps == 128)
            {
                x--;
                steps = 0;
            }
        }

    }
    delete x1;
    delete x2;
    delete y1;
    delete y2;
}

Personages::Coords Personages::getCoords()
{
    return this->coords;
}

void Personages::setCoords(int x, int y)
{
    this->coords.x = x;
    this->coords.y = y;
}

Personages::Steps Personages::getSteps()
{
    return this->steps;
}

int Personages::getDirection()
{
    return this->direction;
}

void Personages::setDirection(int direction)
{
    this->direction = direction;
}

int Personages::getShootDirection()
{
    return  this->shootDirection;
}

void Personages::setShootDirection(int shootDirection)
{
    this->shootDirection = shootDirection;
}

QRect Personages::getRect()
{
    return this->pImage.rect;
}

QPixmap Personages::getPixmap()
{
    std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
    path += this->getImgName();
    path += ".png";
    QPixmap pixmap(path.c_str());
    this->pImage.pixmap = pixmap;
    return this->pImage.pixmap;
}

QTimer *Personages::getTimer()
{
    return this->timer;
}

void Personages::setTimer(QTimer *timer)
{
    this->timer = timer;
}

Personages::Image Personages::getSImage()
{
    return this->sImage;
}
