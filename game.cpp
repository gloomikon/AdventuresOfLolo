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
            this->map[i * x + j].typeOfSthElse = c;
            switch (c)
            {
            case '.':
            {
               this->map[i * x + j].ptr = new Objects(false, false, "wall");
               this->map[i * x + j].typeOfSthElse = 'w';
               break;
            }
            case 'E':
            {
               this->map[i * x + j].ptr = new Objects(false, true, "exit");
               this->map[i * x + j].typeOfSthElse = 'e';
               break;
            }
            case 'R':
            {
                this->map[i * x + j].ptr = new Objects(false, false, "rock");
                this->map[i * x + j].typeOfSthElse = 'r';
                break;
            }
            case 'T':
            {
                this->map[i * x + j].ptr = new Objects(true, false, "tree");
                this->map[i * x + j].typeOfSthElse = 't';
                break;
            }
            case 'S':
            {
                QRect rect;
                rect.setCoords(j * 128,
                               i * 128,
                               (j + 1) * 128,
                               (i + 1) * 128);
                QPixmap pixmap("C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/snakey");
                this->map[i * x + j].ptr = static_cast<Objects*>(new Personages(0, j, i, 9, rect, pixmap, "snakey"));
                this->map[i * x + j].typeOfSthElse = 'b';
                break;
            }
            case 'H':
            {
                this->map[i * x + j].ptr = new Objects(true, true, "heart");
                this->map[i * x + j].typeOfSthElse = 'h';
                qDebug() << this->map[i * x + j].ptr << static_cast<Heart*>(this->map[i * x + j].ptr);
                break;
            }
            case 'L':
            {
                QRect rect;
                rect.setCoords(j * 128,
                               i * 128,
                               (j + 1) * 128,
                               (i + 1) * 128);
                QPixmap pixmap("C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/lolo");
                this->map[i * x + j].ptr = static_cast<Objects*>(new Lolo(j,i,6,rect,pixmap, "lolo"));
                this->lolo = static_cast<Lolo*>(this->map[i * x + j].ptr);
                this->lolo->makeWalkable();
                this->map[i * x + j].typeOfSthElse = 'l';
                break;
            }
            case 'C':
            {
                this->map[i * x + j].ptr = new Objects(true, true, "chest01");
                this->map[i * x + j].typeOfSthElse = 'c';
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
