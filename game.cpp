#include <fstream>
#include <string.h>
#include "game.h"
#include "widget.h"
#include <QDebug>

static const std::string LVL_PATH = "C://Users/gloomikon/Documents/AndenturesOfLolo/lvls/";

Game::Game(Widget *w) : lives{5}, level{1}, active{true}, firstDraw{true}, w{w}
{
    //this->map = new Map;
    this->map = std::unique_ptr<cell[]>(new cell[HEIGHT * WIDTH]);
    std::string s;
    s = std::to_string(this->level) + ".txt";
    readFromFile(s);
}

enum class CellType : char {
    Floor = 'f',
};

void Game::readFromFile(std::string fileName)
{
    std::ifstream   file;
    int             x = 0;
    int             y = 0;
    char            c;
    this->heartsToPick = 0;

    file.open(LVL_PATH + fileName);
    file >> x >> y;
    for (int i = 0; i < y; i++)
        for (int j = 0; j < x; j++)
        {
            file >> c;
            this->map[i * x + j].typeOfSurface = static_cast<char>(CellType::Floor);
            this->map[i * x + j].objPtr = nullptr;
            this->map[i * x + j].perPtr = nullptr;
            switch (c)
            {
            case '.':
            {
               this->map[i * x + j].objPtr = new Object(false, false, "wall", j, i);
               break;
            }
            case 'E':
            {
               this->map[i * x + j].objPtr = new Object(false, false, "exit", j , i);
                this->exit = this->map[i * x + j].objPtr;
               break;
            }
            case 'R':
            {
                this->map[i * x + j].objPtr = new Object(false, false, "rock", j ,i);
                break;
            }
            case 'T':
            {
                this->map[i * x + j].objPtr = new Object(true, false, "tree", j, i);
                break;
            }
            case 'S':
            {
                this->map[i * x + j].perPtr = new Snakey(j, i, 9, "snakey");
                break;
            }
            case 'G':
            {
                this->map[i * x + j].perPtr = new Gol(j, i, 9, "gol");
                break;
            }
            case 'H':
            {
                this->map[i * x + j].objPtr = new Heart("heart", j, i);
                this->heartsToPick++;
                break;
            }
            case 'L':
            {
                this->map[i * x + j].perPtr = new Lolo(j,i,6, "lolo");
                this->lolo = static_cast<Lolo*>(this->map[i * x + j].perPtr);
                this->lolo->makeWalkable();
                break;
            }
            case 'C':
            {
                this->map[i * x + j].objPtr = new Chest("chest01", j, i);
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

void Game::restartLevel()
{
    for (unsigned int i = 0; i < HEIGHT * WIDTH; i++)
    {
        if (this->map[i].objPtr)
            delete (this->map[i].objPtr);
        if (this->map[i].perPtr)
            delete (this->map[i].perPtr);
    }
    std::string s;
    s = std::to_string(this->level) + ".txt";
    readFromFile(s);
    this->firstDraw = true;
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
    if (this->level < 3)
        this->level++;
    std::string s;
    s = std::to_string(this->level) + ".txt";
    readFromFile(s);
    this->firstDraw = true;
    this->activate();
}
std::shared_ptr<cell[]> Game::getMap()
{
    return this->map;
}

/*Map* Game::getClassMap()
{
    return  this->map;
}*/

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

Object *Game::getEXit()
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

void Game::setLvl(int lvl)
{
    this->level = lvl;
}

int Game::getLives()
{
    return this->lives;
}

void Game::setLives(int lives)
{
    this->lives = lives;
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
}
