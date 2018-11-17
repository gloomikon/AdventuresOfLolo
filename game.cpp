#include <fstream>
#include <string.h>
#include "game.h"
#include "objects.h"
#include "personages.h"
#include "lolo.h"
#include "heart.h"
#include "chest.h"

#include <QDebug>

static const std::string LVL_PATH = "C://Users/gloomikon/Documents/AndenturesOfLolo/lvls/";

bool Game::canMoveLeft(Personages *p)
{
    if (p->stepLeftRight == 3)
        return (true);
    if (this->map[p->y * this->width + p->x - 1].ptr)
    {
        if (!(this->map[p->y * this->width + p->x - 1].ptr->isWalkable()))
            return (false);
    }
    if (this->map[(p->y - 1) * this->width + p->x - 1].ptr)
    {
        if (p->stepUpDown == 12 &&
                !(this->map[(p->y - 1) * this->width + p->x - 1].ptr->isWalkable()))
            return (false);
    }
    if (this->map[(p->y + 1) * this->width + p->x - 1].ptr)
    {
        if (p->stepUpDown == 6 &&
                !(this->map[(p->y + 1) * this->width + p->x - 1].ptr->isWalkable()))
            return (false);
    }
    return (true);
}

bool Game::canMoveRight(Personages *p)
{
    if (p->stepLeftRight == 9)
        return (true);
    if (this->map[p->y * this->width + p->x + 1].ptr)
    {
        if (!(this->map[p->y * this->width + p->x + 1].ptr->isWalkable()))
            return (false);
    }
    if (this->map[(p->y - 1) * this->width + p->x + 1].ptr)
    {
        if (p->stepUpDown == 12 &&
                !(this->map[(p->y - 1) * this->width + p->x + 1].ptr->isWalkable()))
            return (false);
    }
    if (this->map[(p->y + 1) * this->width + p->x + 1].ptr)
    {
        if (p->stepUpDown == 6 &&
                !(this->map[(p->y + 1) * this->width + p->x + 1].ptr->isWalkable()))
            return (false);
    }
    return (true);
}

bool Game::canMoveUp(Personages *p)
{
    if (p->stepUpDown == 6)
        return (true);
    if (this->map[(p->y - 1) * this->width + p->x].ptr)
    {
                    qDebug() << (p->y - 1) * this->width + p->x;
        if (!(this->map[(p->y - 1) * this->width + p->x].ptr->isWalkable()))
            return (false);
    }
    if (this->map[(p->y - 1) * this->width + (p->x + 1)].ptr)
    {
        if (p->stepLeftRight == 3 &&
                !(this->map[(p->y - 1) * this->width + (p->x + 1)].ptr->isWalkable()))
            return (false);
    }
    if (this->map[(p->y - 1) * this->width + (p->x - 1)].ptr)
    {
        if (p->stepLeftRight == 9 &&
                !(this->map[(p->y - 1) * this->width + (p->x - 1)].ptr->isWalkable()))
            return (false);
    }
    return (true);
}

bool Game::canMoveDown(Personages *p)
{
    if (p->stepUpDown == 12)
        return (true);
    if (this->map[(p->y + 1) * this->width + p->x].ptr)
    {
        if (!(this->map[(p->y + 1) * this->width + p->x].ptr->isWalkable()))
            return (false);
    }
    if (this->map[(p->y + 1) * this->width + (p->x + 1)].ptr)
    {
        if (p->stepLeftRight == 3 &&
                !(this->map[(p->y + 1) * this->width + (p->x + 1)].ptr->isWalkable()))
            return (false);
    }
    if (this->map[(p->y + 1) * this->width + (p->x - 1)].ptr)
    {
        if (p->stepLeftRight == 9 &&
                !(this->map[(p->y + 1) * this->width + (p->x - 1)].ptr->isWalkable()))
            return (false);
    }
    return (true);
}

Game::Game(std::string fileName)
{
    std::ifstream   file;
    int    x = 0;
    int    y = 0;
    char            c;


    file.open(LVL_PATH + fileName);
    file >> x >> y;
    this->map = new Game::cell[static_cast<unsigned int>(x * y)];
    this->height = y;
    this->width = x;
    for (int i = 0; i < y; i++)
        for (int j = 0; j < x; j++)
        {
            file >> c;
            this->map[i * x + j].typeOfSurface = 'f';
            this->map[i * x + j].typeOfSthElse = c;
            switch (c)
            {
            case '.':
            {
               this->map[i * x + j].ptr = new Objects(false, false);
               this->map[i * x + j].typeOfSurface = 'w';
               break;
            }
            case 'E':
            {
               this->map[i * x + j].ptr = new Objects(false, true);
               this->map[i * x + j].typeOfSurface = 'w';
               this->map[i * x + j].typeOfSthElse = 'e';
               break;
            }
            case 'R':
            {
                this->map[i * x + j].ptr = new Objects(false, false);
                this->map[i * x + j].typeOfSthElse = 'r';
                this->map[i * x + j].imgName = "rock";
                break;
            }
            case 'T':
            {
                this->map[i * x + j].ptr = new Objects(true, false);
                this->map[i * x + j].typeOfSthElse = 't';
                this->map[i * x + j].imgName = "tree";
                break;
            }
            case 'S':
            {
                this->map[i * x + j].ptr = static_cast<Objects*>(new Personages(0, j, i, 9));
                this->map[i * x + j].typeOfSthElse = 'S';
                this->map[i * x + j].imgName = "snakey";
                break;
            }
            case 'H':
            {
                this->map[i * x + j].ptr = static_cast<Objects*>(new Heart(true, true, 2));
                this->map[i * x + j].typeOfSthElse = 'h';
                this->map[i * x + j].imgName = "heart";
                break;
            }
            case 'h':
            {
                this->map[i * x + j].ptr = static_cast<Objects*>(new Heart(true, true, 0));
                this->map[i * x + j].typeOfSthElse = 'h';
                this->map[i * x + j].imgName = "heart";
                break;
            }
            case 'L':
            {
                this->map[i * x + j].ptr = static_cast<Objects*>(new Lolo(j,i,6));
                this->lolo = static_cast<Lolo*>(this->map[i * x + j].ptr);
                this->lolo->makeWalkable();
                this->map[i * x + j].typeOfSthElse = 'L';
                this->map[i * x + j].imgName = "lolo";
                break;
            }
            case 'C':
            {
                this->map[i * x + j].ptr = static_cast<Objects*>(new Chest());
                this->map[i * x + j].typeOfSthElse = 'c';
                this->map[i * x + j].imgName = "chest01";
                break;
            }
            default:
            {
                this->map[i * x + j].ptr = nullptr;
                break;
            }
            }
        }
    file.close();
}


Game::~Game()
{
    for (unsigned int i = 0; i < this->height * this->width; i++)
        if (this->map[i].ptr)
            operator delete (this->map[i].ptr);
    delete map;
}
