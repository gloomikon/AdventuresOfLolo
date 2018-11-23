#include "personages.h"
#include "game.h"
#include <QDebug>

Personages::Personages(bool shootable, int x, int y, int direction, QRect rect, QPixmap pixmap, std::string imgName):
    Objects(shootable, false, imgName), coords{x,y}, steps{0,0}, direction{direction},
    rect{rect}, pixmap{pixmap}
{}

bool Personages::canMoveLeft(Game *game)
{
    if (this->steps.stepLeftRight == 3)
        return (true);
    if (game->map[this->coords.y * WIDTH + this->coords.x - 1].ptr)
    {
        if (!(game->map[this->coords.y * WIDTH + this->coords.x - 1].ptr->isWalkable()))
            return (false);
    }
    if (game->map[(this->coords.y - 1) * WIDTH + this->coords.x - 1].ptr)
    {
        if (this->steps.stepUpDown == 12 &&
                !(game->map[(this->coords.y - 1) * WIDTH + this->coords.x - 1].ptr->isWalkable()))
            return (false);
    }
    if (game->map[(this->coords.y + 1) * WIDTH + this->coords.x - 1].ptr)
    {
        if (this->steps.stepUpDown == 6 &&
                !(game->map[(this->coords.y + 1) * WIDTH + this->coords.x - 1].ptr->isWalkable()))
            return (false);
    }
    return (true);
}

bool Personages::canMoveRight(Game *game)
{
    if (this->steps.stepLeftRight == 9)
        return (true);
    if (game->map[this->coords.y * WIDTH + this->coords.x + 1].ptr)
    {
        if (!(game->map[this->coords.y * WIDTH + this->coords.x + 1].ptr->isWalkable()))
            return (false);
    }
    if (game->map[(this->coords.y - 1) * WIDTH + this->coords.x + 1].ptr)
    {
        if (this->steps.stepUpDown == 12 &&
                !(game->map[(this->coords.y - 1) * WIDTH + this->coords.x + 1].ptr->isWalkable()))
            return (false);
    }
    if (game->map[(this->coords.y + 1) * WIDTH + this->coords.x + 1].ptr)
    {
        if (this->steps.stepUpDown == 6 &&
                !(game->map[(this->coords.y + 1) * WIDTH + this->coords.x + 1].ptr->isWalkable()))
            return (false);
    }
    return (true);
}

bool Personages::canMoveUp(Game *game)
{
    if (this->steps.stepUpDown == 6)
        return (true);
    if (game->map[(this->coords.y - 1) * WIDTH + this->coords.x].ptr)
    {
        if (!(game->map[(this->coords.y - 1) * WIDTH + this->coords.x].ptr->isWalkable()))
            return (false);
    }
    if (game->map[(this->coords.y - 1) * WIDTH + (this->coords.x + 1)].ptr)
    {
        if (this->steps.stepLeftRight == 3 &&
                !(game->map[(this->coords.y - 1) * WIDTH + (this->coords.x + 1)].ptr->isWalkable()))
            return (false);
    }
    if (game->map[(this->coords.y - 1) * WIDTH + (this->coords.x - 1)].ptr)
    {
        if (this->steps.stepLeftRight == 9 &&
                !(game->map[(this->coords.y - 1) * WIDTH + (this->coords.x - 1)].ptr->isWalkable()))
            return (false);
    }
    return (true);
}

bool Personages::canMoveDown(Game *game)
{
    if (this->steps.stepUpDown == 12)
        return (true);
    if (game->map[(this->coords.y + 1) * WIDTH + this->coords.x].ptr)
    {
        if (!(game->map[(this->coords.y + 1) * WIDTH + this->coords.x].ptr->isWalkable()))
            return (false);
    }
    if (game->map[(this->coords.y + 1) * WIDTH + (this->coords.x + 1)].ptr)
    {
        if (this->steps.stepLeftRight == 3 &&
                !(game->map[(this->coords.y + 1) * WIDTH + (this->coords.x + 1)].ptr->isWalkable()))
            return (false);
    }
    if (game->map[(this->coords.y + 1) * WIDTH + (this->coords.x - 1)].ptr)
    {
        if (this->steps.stepLeftRight == 9 &&
                !(game->map[(this->coords.y + 1) * WIDTH + (this->coords.x - 1)].ptr->isWalkable()))
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
    this->rect.getCoords(x1, y1, x2, y2);
    if (this->canMoveLeft(game))
    {
        this->rect.moveLeft(*x1 - 4);
        steps+=4;
        if (steps >= 8 && steps < 16)
        {
            this->imgName = "lololeft1";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pixmap = QPixmap(path.c_str());
        }
        else if (steps >= 16 && steps < 24)
        {
            this->imgName = "lololeft2";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pixmap = QPixmap(path.c_str());
        }
        else if (steps >= 24 && steps < 32)
        {
            this->imgName = "lololeft1";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pixmap = QPixmap(path.c_str());
        }
        else if (steps >= 32 && steps < 40)
        {
            this->imgName = "lololeft3";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pixmap = QPixmap(path.c_str());
        }
        else if (steps >= 40 && steps < 48)
        {
            this->imgName = "lololeft4";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pixmap = QPixmap(path.c_str());
        }
        else if (steps >= 48 && steps < 56)
        {
            this->imgName = "lololeft3";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pixmap = QPixmap(path.c_str());
        }
        else if (steps >= 56 && steps < 64)
        {
            this->imgName = "lololeft";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pixmap = QPixmap(path.c_str());
        }
        else if (steps == 64)
        {
            if (this->steps.stepLeftRight)
            {
                if (this->steps.stepLeftRight == 9)
                    this->coords.x--;
                game->map[this->coords.y * WIDTH + this->coords.x + 1].isSome1Here = false;
                if (this->steps.stepUpDown == 12)
                    game->map[(this->coords.y - 1) * WIDTH + this->coords.x + 1].isSome1Here = false;
                if (this->steps.stepUpDown == 6)
                    game->map[(this->coords.y + 1) * WIDTH + this->coords.x + 1].isSome1Here = false;
                game->map[this->coords.y * WIDTH + this->coords.x].isSome1Here = true;
                if (this->steps.stepUpDown == 12)
                    game->map[(this->coords.y - 1) * WIDTH + this->coords.x].isSome1Here = true;
                if (this->steps.stepUpDown == 6)
                    game->map[(this->coords.y + 1) * WIDTH + this->coords.x].isSome1Here = true;
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
    this->rect.getCoords(x1, y1, x2, y2);
    if (this->canMoveRight(game))
    {
        this->rect.moveLeft(*x1 + 4);
        steps+=4;
        if (steps >= 8 && steps < 16)
        {
            this->imgName = "loloright1";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pixmap = QPixmap(path.c_str());
        }
        else if (steps >= 16 && steps < 24)
        {
            this->imgName = "loloright2";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pixmap = QPixmap(path.c_str());
        }
        else if (steps >= 24 && steps < 32)
        {
            this->imgName = "loloright1";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pixmap = QPixmap(path.c_str());
        }
        else if (steps >= 32 && steps < 40)
        {
            this->imgName = "loloright3";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pixmap = QPixmap(path.c_str());
        }
        else if (steps >= 40 && steps < 48)
        {
            this->imgName = "loloright4";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pixmap = QPixmap(path.c_str());
        }
        else if (steps >= 48 && steps < 56)
        {
            this->imgName = "loloright3";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pixmap = QPixmap(path.c_str());
        }
        else if (steps >= 56 && steps < 64)
        {
            this->imgName = "loloright";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pixmap = QPixmap(path.c_str());
        }
        else if (steps == 64)
        {
            if (this->steps.stepLeftRight)
            {
                if (this->steps.stepLeftRight == 3)
                    this->coords.x++;
                game->map[this->coords.y * WIDTH + this->coords.x - 1].isSome1Here = false;
                if (this->steps.stepUpDown == 12)
                    game->map[(this->coords.y - 1) * WIDTH + this->coords.x - 1].isSome1Here = false;
                if (this->steps.stepUpDown == 6)
                    game->map[(this->coords.y + 1) * WIDTH + this->coords.x - 1].isSome1Here = false;
                game->map[this->coords.y * WIDTH + this->coords.x].isSome1Here = true;
                if (this->steps.stepUpDown == 12)
                    game->map[(this->coords.y - 1) * WIDTH + this->coords.x].isSome1Here = true;
                if (this->steps.stepUpDown == 6)
                    game->map[(this->coords.y + 1) * WIDTH + this->coords.x].isSome1Here = true;
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
    this->rect.getCoords(x1, y1, x2, y2);
    if (this->canMoveUp(game))
    {
        this->rect.moveTop(*y1 - 4);
        steps+=4;
        if (steps >= 8 && steps < 16)
        {
            this->imgName = "loloup1";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pixmap = QPixmap(path.c_str());
        }
        else if (steps >= 16 && steps < 24)
        {
            this->imgName = "loloup2";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pixmap = QPixmap(path.c_str());
        }
        else if (steps >= 24 && steps < 32)
        {
            this->imgName = "loloup1";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pixmap = QPixmap(path.c_str());
        }
        else if (steps >= 32 && steps < 40)
        {
            this->imgName = "loloup3";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pixmap = QPixmap(path.c_str());
        }
        else if (steps >= 40 && steps < 48)
        {
            this->imgName = "loloup4";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pixmap = QPixmap(path.c_str());
        }
        else if (steps >= 48 && steps < 56)
        {
            this->imgName = "loloup3";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pixmap = QPixmap(path.c_str());
        }
        else if (steps >= 56 && steps < 64)
        {
            this->imgName = "loloup";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pixmap = QPixmap(path.c_str());
        }
        else if (steps == 64)
        {
            if (this->steps.stepUpDown)
            {
                if (this->steps.stepUpDown == 12)
                {
                    this->coords.y--;
                    game->map[(this->coords.y + 1) * WIDTH + this->coords.x].isSome1Here = false;
                if (this->steps.stepLeftRight == 3)
                    game->map[(this->coords.y + 1) * WIDTH + this->coords.x + 1].isSome1Here = false;
                if (this->steps.stepLeftRight == 9)
                    game->map[(this->coords.y + 1) * WIDTH + this->coords.x - 1].isSome1Here = false;
                game->map[this->coords.y * WIDTH + this->coords.x].isSome1Here = true;
                if (this->steps.stepLeftRight == 3)
                    game->map[this->coords.y * WIDTH + this->coords.x + 1].isSome1Here = true;
                if (this->steps.stepLeftRight == 9)
                    game->map[this->coords.y * WIDTH + this->coords.x - 1].isSome1Here = true;
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
    this->rect.getCoords(x1, y1, x2, y2);
    if (this->canMoveDown(game))
    {
        this->rect.moveTop(*y1 + 4);
        steps+=4;
        if (steps >= 8 && steps < 16)
        {
            this->imgName = "lolodown1";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pixmap = QPixmap(path.c_str());
        }
        else if (steps >= 16 && steps < 24)
        {
            this->imgName = "lolodown2";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pixmap = QPixmap(path.c_str());
        }
        else if (steps >= 24 && steps < 32)
        {
            this->imgName = "lolodown1";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pixmap = QPixmap(path.c_str());
        }
        else if (steps >= 32 && steps < 40)
        {
            this->imgName = "lolodown3";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pixmap = QPixmap(path.c_str());
        }
        else if (steps >= 40 && steps < 48)
        {
            this->imgName = "lolodown4";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pixmap = QPixmap(path.c_str());
        }
        else if (steps >= 48 && steps < 56)
        {
            this->imgName = "lolodown3";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pixmap = QPixmap(path.c_str());
        }
        else if (steps >= 56 && steps < 64)
        {
            this->imgName = "lolo";
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->imgName;
            path += ".png";
            this->pixmap = QPixmap(path.c_str());
        }
        else if (steps == 64)
        {
            if (this->steps.stepUpDown)
            {
                if (this->steps.stepUpDown == 6)
                {
                    this->coords.y++;
                    game->map[(this->coords.y - 1) * WIDTH + this->coords.x].isSome1Here = false;
                if (this->steps.stepLeftRight == 3)
                    game->map[(this->coords.y - 1) * WIDTH + this->coords.x + 1].isSome1Here = false;
                if (this->steps.stepLeftRight == 9)
                    game->map[(this->coords.y - 1) * WIDTH + this->coords.x - 1].isSome1Here = false;
                game->map[this->coords.y * WIDTH + this->coords.x].isSome1Here = true;
                if (this->steps.stepLeftRight == 3)
                    game->map[this->coords.y * WIDTH + this->coords.x + 1].isSome1Here = true;
                if (this->steps.stepLeftRight == 9)
                    game->map[this->coords.y * WIDTH + this->coords.x - 1].isSome1Here = true;
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

QRect Personages::getRect()
{
    return this->rect;
}

QPixmap Personages::getPixmap()
{
    std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
    path += this->getImgName();
    path += ".png";
    QPixmap pixmap(path.c_str());
    this->pixmap = pixmap;
    return this->pixmap;
}
