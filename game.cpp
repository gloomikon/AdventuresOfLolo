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
    int             x = 0;
    int             y = 0;
    char            c;


    file.open(LVL_PATH + fileName);
    file >> x >> y;
    this->map = new Game::cell[static_cast<unsigned int>(x * y)];
    for (int i = 0; i < y; i++)
        for (int j = 0; j < x; j++)
        {
            file >> c;
            this->map[i * x + j].typeOfSurface = 'f';
            this->map[i * x + j].objPtr = nullptr;
            this->map[i * x + j].perPtr = nullptr;
            switch (c)
            {
            case '.':
            {
               this->map[i * x + j].objPtr = new Objects(false, false, "wall");
               break;
            }
            case 'E':
            {
               this->map[i * x + j].objPtr = new Objects(false, false, "exit");
               break;
            }
            case 'R':
            {
                this->map[i * x + j].objPtr = new Objects(false, false, "rock");
                break;
            }
            case 'T':
            {
                this->map[i * x + j].objPtr = new Objects(true, false, "tree");
                break;
            }
            case 'S':
            {
                QRect rect;
                rect.setCoords(j * SIZE,
                               i * SIZE,
                               (j + 1) * SIZE,
                               (i + 1) * SIZE);
                QPixmap pixmap("C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/snakey");
                this->map[i * x + j].perPtr = new Personages(0, j, i, 9, rect, pixmap, "snakey");
                break;
            }
            case 'H':
            {
                this->map[i * x + j].objPtr = new Heart("heart");
                break;
            }
            case 'L':
            {
                QRect rect;
                rect.setCoords(j * SIZE,
                               i * SIZE,
                               (j + 1) * SIZE,
                               (i + 1) * SIZE);
                QPixmap pixmap("C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/lolo");
                this->map[i * x + j].perPtr = new Lolo(j,i,6,rect,pixmap, "lolo");
                this->lolo = static_cast<Lolo*>(this->map[i * x + j].perPtr);
                this->lolo->makeWalkable();
                break;
            }
            case 'C':
            {
                this->map[i * x + j].objPtr = new Chest("chest01");
                break;
            }
            default:
            {
                break;
            }
            }
        }
    file.close();
}

Game::cell *Game::getMap()
{
    return this->map;
}

Lolo *Game::getLolo()
{
    return this->lolo;
}


Game::~Game()
{
    for (unsigned int i = 0; i < HEIGHT * WIDTH; i++)
    {
        if (this->map[i].objPtr)
            delete (this->map[i].objPtr);
        if (this->map[i].perPtr)
            delete (this->map[i].perPtr);
    }
    delete map;
}
