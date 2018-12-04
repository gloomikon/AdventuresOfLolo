#include <fstream>
#include <string.h>
#include "game.h"
#include "widget.h"
#include <QDebug>

static const std::string LVL_PATH = "C://Users/gloomikon/Documents/AndenturesOfLolo/lvls/";

Game::Game(Widget *w) : lives{5}, level{1}, active{true}, firstDraw{true}, w{w}
{
    std::string s;
    s = std::to_string(this->level) + ".txt";
    readFromFile(s);
}

void Game::readFromFile(std::string fileName)
{
    std::ifstream   file;
    int             x = 0;
    int             y = 0;
    char            c;
    this->heartsToPick = 0;

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
                this->exit = this->map[i * x + j].objPtr;
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
                this->heartsToPick++;
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
                this->chest = static_cast<Chest*>(this->map[i * x + j].objPtr);
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

void Game::nextLevel()
{
    for (unsigned int i = 0; i < HEIGHT * WIDTH; i++)
    {
        if (this->map[i].objPtr)
            delete (this->map[i].objPtr);
        if (this->map[i].perPtr)
            delete (this->map[i].perPtr);
    }
    delete map;
    std::string s;
    s = std::to_string(this->level) + ".txt";
    readFromFile(s);
    this->firstDraw = true;
}
Game::cell *Game::getMap()
{
    return this->map;
}

Lolo *Game::getLolo()
{
    return this->lolo;
}

Chest *Game::getChest()
{
    return this->chest;
}

bool Game::isActive()
{
    return this->active;
}

Objects *Game::getEXit()
{
    return this->exit;
}

void Game::disactivate()
{
    this->active = false;
}

void Game::activate()
{
    this->active = true;
}

int Game::getHeartsToPick()
{
    return this->heartsToPick;
}

bool Game::getFirstDraw()
{
    return this->firstDraw;
}

void Game::setFirstDraw(bool f)
{
    this->firstDraw = f;
}

void Game::clear()
{
    for (unsigned int i = 0; i < HEIGHT * WIDTH; i++)
    {
        if (this->map[i].perPtr && this->map[i].perPtr != this->lolo)
        {
            delete (this->map[i].perPtr);
            this->map[i].perPtr = nullptr;
        }
    }
}

Widget *Game::getWidget()
{
    return this->w;
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
