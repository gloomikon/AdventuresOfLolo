#include <fstream>
#include <string.h>
#include "game.h"

#include <QDebug>

static const std::string LVL_PATH = "C://Users/gloomikon/Documents/AndenturesOfLolo/lvls/";

bool Game::wasHeartPicked()
{
    return this->heartPicked;
}

void Game::setHeartPickedStatus(bool picked)
{
    this->heartPicked = picked;
}

Game::Game(std::string fileName) : heartPicked{false}
{
    std::ifstream   file;
    int    x = 0;
    int    y = 0;
    char            c;


    file.open(LVL_PATH + fileName);
    file >> x >> y;
    this->map = new Game::cell[static_cast<unsigned int>(x * y)];
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
                this->map[i * x + j].ptr = static_cast<Objects*>(new Heart(true, true));
                this->map[i * x + j].typeOfSthElse = 'h';
                qDebug() << this->map[i * x + j].ptr << static_cast<Heart*>(this->map[i * x + j].ptr);
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
    for (unsigned int i = 0; i < HEIGHT * WIDTH; i++)
        if (this->map[i].ptr)
            operator delete (this->map[i].ptr);
    delete map;
}
