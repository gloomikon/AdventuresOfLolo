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
        if (this->map[i].perPtr && this->map[i].perPtr != this->lolo)
            delete (this->map[i].perPtr);
    }
}

Game &Game::Instance(Widget *w)
{
    static Game instance(w);
    return instance;
}

int Game::canMoveLeft(Personage *p, int n)
{
    if (p->getSteps()->stepUpDown== 0)
    {
        int k = 0;
        if (p->getSteps()->stepLeftRight== 0 && ((this->map[(p->getCoords()->y) * WIDTH + p->getCoords()->x - 1].objPtr &&
             !(this->map[(p->getCoords()->y) * WIDTH + p->getCoords()->x - 1].objPtr->isWalkable())) ||
                (this->map[(p->getCoords()->y) * WIDTH + p->getCoords()->x - 1].perPtr &&
                 this->map[(p->getCoords()->y) * WIDTH + p->getCoords()->x - 1].perPtr->isAlive() &&
                 this->map[(p->getCoords()->y) * WIDTH + p->getCoords()->x - 1].perPtr->getSteps()->stepLeftRight== 0) ||
                (this->map[(p->getCoords()->y - 1) * WIDTH + p->getCoords()->x - 1].perPtr &&
                 this->map[(p->getCoords()->y - 1) * WIDTH + p->getCoords()->x - 1].perPtr->getSteps()->stepLeftRight== 0 &&
                 this->map[(p->getCoords()->y - 1) * WIDTH + p->getCoords()->x - 1].perPtr->getSteps()->stepUpDown== 6) ||
                (this->map[(p->getCoords()->y + 1) * WIDTH + p->getCoords()->x - 1].perPtr &&
                 this->map[(p->getCoords()->y + 1) * WIDTH + p->getCoords()->x - 1].perPtr->getSteps()->stepLeftRight== 0 &&
                 this->map[(p->getCoords()->y + 1) * WIDTH + p->getCoords()->x - 1].perPtr->getSteps()->stepUpDown== 12)))
            return 0;
        if (p->getSteps()->stepLeftRight== 9)
            k = 0;
        else if (p->getSteps()->stepLeftRight== 3)
            k = 1;
        if (p->getSteps()->stepLeftRight!= 0 &&
                ((this->map[(p->getCoords()->y) * WIDTH + p->getCoords()->x - 1 + k].perPtr &&
             this->map[(p->getCoords()->y) * WIDTH + p->getCoords()->x - 1 + k].perPtr->isAlive() &&
             this->map[(p->getCoords()->y) * WIDTH + p->getCoords()->x - 1 + k].perPtr != p) ||
                (this->map[(p->getCoords()->y - 1) * WIDTH + p->getCoords()->x - 1 + k].perPtr &&
                 this->map[(p->getCoords()->y - 1) * WIDTH + p->getCoords()->x - 1 + k].perPtr->getSteps()->stepLeftRight== 9 &&
                 this->map[(p->getCoords()->y - 1) * WIDTH + p->getCoords()->x - 1 + k].perPtr->getSteps()->stepUpDown== 6) ||
                (this->map[(p->getCoords()->y + 1) * WIDTH + p->getCoords()->x - 1 + k].perPtr &&
                 this->map[(p->getCoords()->y + 1) * WIDTH + p->getCoords()->x - 1 + k].perPtr->getSteps()->stepLeftRight== 9 &&
                 this->map[(p->getCoords()->y + 1) * WIDTH + p->getCoords()->x - 1 + k].perPtr->getSteps()->stepUpDown== 12)  ||
                (this->map[(p->getCoords()->y - 1) * WIDTH + p->getCoords()->x - 2 + k].perPtr &&
                 this->map[(p->getCoords()->y - 1) * WIDTH + p->getCoords()->x - 2 + k].perPtr->getSteps()->stepLeftRight== 3 &&
                 this->map[(p->getCoords()->y - 1) * WIDTH + p->getCoords()->x - 2 + k].perPtr->getSteps()->stepUpDown== 6)||
                 (this->map[(p->getCoords()->y) * WIDTH + p->getCoords()->x - 2 + k].perPtr &&
                  this->map[(p->getCoords()->y) * WIDTH + p->getCoords()->x - 2 + k].perPtr->getSteps()->stepLeftRight== 3 &&
                  this->map[(p->getCoords()->y) * WIDTH + p->getCoords()->x - 2 + k].perPtr->isAlive()) ||
                (this->map[(p->getCoords()->y + 1) * WIDTH + p->getCoords()->x - 2 + k].perPtr &&
                 this->map[(p->getCoords()->y + 1) * WIDTH + p->getCoords()->x - 2 + k].perPtr->getSteps()->stepLeftRight== 3 &&
                 this->map[(p->getCoords()->y + 1) * WIDTH + p->getCoords()->x - 2 + k].perPtr->getSteps()->stepUpDown== 12)))
            return 0;
            if (p->getSteps()->stepLeftRight== 0 &&
                ((this->map[(p->getCoords()->y) * WIDTH + p->getCoords()->x - 1].perPtr &&
                  !this->map[(p->getCoords()->y) * WIDTH + p->getCoords()->x - 1].perPtr->isAlive() &&
                  this->map[(p->getCoords()->y) * WIDTH + p->getCoords()->x - 1].perPtr->getSteps()->stepLeftRight== 0)))
            {
                if (this->canMoveLeft(this->map[(p->getCoords()->y) * WIDTH + p->getCoords()->x - 1].perPtr, n+1))
                    return 2;
                return 0;
            }
            if (p->getSteps()->stepLeftRight!= 0 &&
                    (this->map[(p->getCoords()->y) * WIDTH + p->getCoords()->x - 1 + k].perPtr &&
                  !this->map[(p->getCoords()->y) * WIDTH + p->getCoords()->x - 1 + k].perPtr->isAlive() &&
                  this->map[(p->getCoords()->y) * WIDTH + p->getCoords()->x - 1 + k].perPtr->getSteps()->stepLeftRight== 9))
            {
                if (this->canMoveLeft(this->map[(p->getCoords()->y) * WIDTH + p->getCoords()->x - 1 + k].perPtr, n+1))
                    return 2;
                return 0;
            }

            if (p->getSteps()->stepLeftRight!= 0 &&
                    (this->map[(p->getCoords()->y) * WIDTH + p->getCoords()->x - 2 + k].perPtr &&
                  !this->map[(p->getCoords()->y) * WIDTH + p->getCoords()->x - 2 + k].perPtr->isAlive() &&
                  this->map[(p->getCoords()->y) * WIDTH + p->getCoords()->x - 2 + k].perPtr->getSteps()->stepLeftRight== 3))
            {
                if (this->canMoveLeft(this->map[(p->getCoords()->y) * WIDTH + p->getCoords()->x - 2 + k].perPtr, n+1))
                    return 3;
                return 0;
            }
    }
     else
    {
            int j = 0;
            int k = 0;
        if (p->getSteps()->stepUpDown== 12)
                j = 0;
            else if (p->getSteps()->stepUpDown== 6)
                j = 1;
        if (p->getSteps()->stepLeftRight== 0 &&
                ((this->map[(p->getCoords()->y + j) * WIDTH + p->getCoords()->x - 1].objPtr &&
                     !(this->map[(p->getCoords()->y + j) * WIDTH + p->getCoords()->x - 1].objPtr->isWalkable())) ||
                (this->map[(p->getCoords()->y - 1 + j) * WIDTH + p->getCoords()->x - 1].objPtr &&
                                     !(this->map[(p->getCoords()->y - 1 + j) * WIDTH + p->getCoords()->x - 1].objPtr->isWalkable())) ||
                        (this->map[(p->getCoords()->y + j) * WIDTH + p->getCoords()->x - 1].perPtr &&
                         this->map[(p->getCoords()->y + j) * WIDTH + p->getCoords()->x - 1].perPtr->getSteps()->stepLeftRight!= 9 &&
                          this->map[(p->getCoords()->y + j) * WIDTH + p->getCoords()->x - 1].perPtr->getSteps()->stepUpDown!= 6) ||
                (this->map[(p->getCoords()->y - 1 + j) * WIDTH + p->getCoords()->x - 1].perPtr &&
                 this->map[(p->getCoords()->y - 1 + j) * WIDTH + p->getCoords()->x - 1].perPtr->getSteps()->stepLeftRight!= 9 &&
                  this->map[(p->getCoords()->y - 1 + j) * WIDTH + p->getCoords()->x - 1].perPtr->getSteps()->stepUpDown!= 12)))
            return 0;
        if (p->getSteps()->stepLeftRight== 9)
            k = 0;
        else if (p->getSteps()->stepLeftRight== 3)
            k = 1;
        if (p->getSteps()->stepLeftRight!= 0 &&
                        ((this->map[(p->getCoords()->y + j) * WIDTH + p->getCoords()->x - 1 + k].perPtr &&
                          this->map[(p->getCoords()->y + j) * WIDTH + p->getCoords()->x - 1 + k].perPtr != p &&
                          this->map[(p->getCoords()->y + j) * WIDTH + p->getCoords()->x - 1 + k].perPtr->getSteps()->stepUpDown!= 6) ||
                (this->map[(p->getCoords()->y - 1 + j) * WIDTH + p->getCoords()->x - 1 + k].perPtr &&
                 this->map[(p->getCoords()->y - 1 + j) * WIDTH + p->getCoords()->x - 1 + k].perPtr != p &&
                  this->map[(p->getCoords()->y - 1 + j) * WIDTH + p->getCoords()->x - 1 + k].perPtr->getSteps()->stepUpDown!= 12) ||
                         (this->map[(p->getCoords()->y + j) * WIDTH + p->getCoords()->x - 2 + k].perPtr &&
                           this->map[(p->getCoords()->y + j) * WIDTH + p->getCoords()->x - 2 + k].perPtr->getSteps()->stepUpDown!= 6 &&
                          this->map[(p->getCoords()->y + j) * WIDTH + p->getCoords()->x - 2 + k].perPtr->getSteps()->stepLeftRight== 3) ||
                         (this->map[(p->getCoords()->y - 1 + j) * WIDTH + p->getCoords()->x - 2 + k].perPtr &&
                           this->map[(p->getCoords()->y - 1 + j) * WIDTH + p->getCoords()->x - 2 + k].perPtr->getSteps()->stepUpDown!= 12 &&
                          this->map[(p->getCoords()->y - 1 + j) * WIDTH + p->getCoords()->x - 2 + k].perPtr->getSteps()->stepLeftRight== 3)))
            return 0;

    }
    return 1;
}

int Game::canMoveRight(Personage *p, int n)
{
    if (p->getSteps()->stepUpDown== 0)
    {
        int k = 0;
        if (p->getSteps()->stepLeftRight== 0 && ((this->map[(p->getCoords()->y) * WIDTH + p->getCoords()->x + 1].objPtr &&
             !(this->map[(p->getCoords()->y) * WIDTH + p->getCoords()->x + 1].objPtr->isWalkable())) ||
              (this->map[(p->getCoords()->y) * WIDTH + p->getCoords()->x + 1].perPtr &&
               this->map[(p->getCoords()->y) * WIDTH + p->getCoords()->x + 1].perPtr->isAlive() &&
               this->map[(p->getCoords()->y) * WIDTH + p->getCoords()->x + 1].perPtr->getSteps()->stepLeftRight== 0) ||
          (this->map[(p->getCoords()->y - 1) * WIDTH + p->getCoords()->x + 1].perPtr &&
           this->map[(p->getCoords()->y - 1) * WIDTH + p->getCoords()->x + 1].perPtr->getSteps()->stepLeftRight== 0 &&
           this->map[(p->getCoords()->y - 1) * WIDTH + p->getCoords()->x + 1].perPtr->getSteps()->stepUpDown== 6) ||
          (this->map[(p->getCoords()->y + 1) * WIDTH + p->getCoords()->x + 1].perPtr &&
           this->map[(p->getCoords()->y + 1) * WIDTH + p->getCoords()->x + 1].perPtr->getSteps()->stepLeftRight== 0 &&
           this->map[(p->getCoords()->y + 1) * WIDTH + p->getCoords()->x + 1].perPtr->getSteps()->stepUpDown== 12)))
            return 0;
        if (p->getSteps()->stepLeftRight== 3)
            k = 0;
        else if (p->getSteps()->stepLeftRight== 9)
            k = 1;
        if (p->getSteps()->stepLeftRight!= 0 &&
                ((this->map[(p->getCoords()->y) * WIDTH + p->getCoords()->x + 1 - k].perPtr &&
                  this->map[(p->getCoords()->y) * WIDTH + p->getCoords()->x + 1 - k].perPtr->isAlive() &&
                  this->map[(p->getCoords()->y) * WIDTH + p->getCoords()->x + 1 - k].perPtr != p) ||
             (this->map[(p->getCoords()->y - 1) * WIDTH + p->getCoords()->x + 1 - k].perPtr &&
              this->map[(p->getCoords()->y - 1) * WIDTH + p->getCoords()->x + 1 - k].perPtr->getSteps()->stepLeftRight== 3 &&
              this->map[(p->getCoords()->y - 1) * WIDTH + p->getCoords()->x + 1 - k].perPtr->getSteps()->stepUpDown== 6) ||
             (this->map[(p->getCoords()->y + 1) * WIDTH + p->getCoords()->x + 1 - k].perPtr &&
              this->map[(p->getCoords()->y + 1) * WIDTH + p->getCoords()->x + 1 - k].perPtr->getSteps()->stepLeftRight== 3 &&
              this->map[(p->getCoords()->y + 1) * WIDTH + p->getCoords()->x + 1 - k].perPtr->getSteps()->stepUpDown== 12)  ||
             (this->map[(p->getCoords()->y - 1) * WIDTH + p->getCoords()->x + 2 - k].perPtr &&
              this->map[(p->getCoords()->y - 1) * WIDTH + p->getCoords()->x + 2 - k].perPtr->getSteps()->stepLeftRight== 9 &&
              this->map[(p->getCoords()->y - 1) * WIDTH + p->getCoords()->x + 2 - k].perPtr->getSteps()->stepUpDown== 6)||
                 (this->map[(p->getCoords()->y) * WIDTH + p->getCoords()->x + 2 - k].perPtr &&
                  this->map[(p->getCoords()->y) * WIDTH + p->getCoords()->x + 2 - k].perPtr->getSteps()->stepLeftRight== 9 &&
                  this->map[(p->getCoords()->y) * WIDTH + p->getCoords()->x + 2 - k].perPtr->isAlive()) ||
             (this->map[(p->getCoords()->y + 1) * WIDTH + p->getCoords()->x + 2 - k].perPtr &&
              this->map[(p->getCoords()->y + 1) * WIDTH + p->getCoords()->x + 2 - k].perPtr->getSteps()->stepLeftRight== 9 &&
              this->map[(p->getCoords()->y + 1) * WIDTH + p->getCoords()->x + 2 - k].perPtr->getSteps()->stepUpDown== 12)))
            return 0;
            if (p->getSteps()->stepLeftRight== 0 &&
                ((this->map[(p->getCoords()->y) * WIDTH + p->getCoords()->x + 1].perPtr &&
                 !this->map[(p->getCoords()->y) * WIDTH + p->getCoords()->x + 1].perPtr->isAlive() &&
                  this->map[(p->getCoords()->y) * WIDTH + p->getCoords()->x + 1].perPtr->getSteps()->stepLeftRight== 0)))
            {
                if (this->canMoveRight(this->map[(p->getCoords()->y) * WIDTH + p->getCoords()->x + 1].perPtr, n+1))
                    return 2;
                return 0;
            }
            if (p->getSteps()->stepLeftRight!= 0 &&
                    (this->map[(p->getCoords()->y) * WIDTH + p->getCoords()->x + 1 - k].perPtr &&
                    !this->map[(p->getCoords()->y) * WIDTH + p->getCoords()->x + 1 - k].perPtr->isAlive() &&
                     this->map[(p->getCoords()->y) * WIDTH + p->getCoords()->x + 1 - k].perPtr->getSteps()->stepLeftRight== 3))
            {
                if (this->canMoveRight(this->map[(p->getCoords()->y) * WIDTH + p->getCoords()->x + 1 - k].perPtr, n+1))
                    return 2;
                return 0;
            }

            if (p->getSteps()->stepLeftRight!= 0 &&
                    (this->map[(p->getCoords()->y) * WIDTH + p->getCoords()->x + 2 - k].perPtr &&
                    !this->map[(p->getCoords()->y) * WIDTH + p->getCoords()->x + 2 - k].perPtr->isAlive() &&
                     this->map[(p->getCoords()->y) * WIDTH + p->getCoords()->x + 2 - k].perPtr->getSteps()->stepLeftRight== 9))
            {
                if (this->canMoveRight(this->map[(p->getCoords()->y) * WIDTH + p->getCoords()->x + 2 - k].perPtr, n+1))
                    return 3;
                return 0;
            }
    }
     else
    {
            int j = 0;
            int k = 0;
        if (p->getSteps()->stepUpDown== 12)
                j = 0;
            else if (p->getSteps()->stepUpDown== 6)
                j = 1;
        if (p->getSteps()->stepLeftRight== 0 &&
                ((this->map[(p->getCoords()->y - 1 + j) * WIDTH + p->getCoords()->x + 1].objPtr &&
                !(this->map[(p->getCoords()->y - 1 + j) * WIDTH + p->getCoords()->x + 1].objPtr->isWalkable())) ||
             (this->map[(p->getCoords()->y + j) * WIDTH + p->getCoords()->x + 1].objPtr &&
            !(this->map[(p->getCoords()->y + j) * WIDTH + p->getCoords()->x + 1].objPtr->isWalkable())) ||
             (this->map[(p->getCoords()->y + j) * WIDTH + p->getCoords()->x + 1].perPtr &&
              this->map[(p->getCoords()->y + j) * WIDTH + p->getCoords()->x + 1].perPtr->getSteps()->stepLeftRight!= 3 &&
              this->map[(p->getCoords()->y + j) * WIDTH + p->getCoords()->x + 1].perPtr->getSteps()->stepUpDown!= 6) ||
         (this->map[(p->getCoords()->y - 1 + j) * WIDTH + p->getCoords()->x + 1].perPtr &&
          this->map[(p->getCoords()->y - 1 + j) * WIDTH + p->getCoords()->x + 1].perPtr->getSteps()->stepLeftRight!= 3 &&
          this->map[(p->getCoords()->y - 1 + j) * WIDTH + p->getCoords()->x + 1].perPtr->getSteps()->stepUpDown!= 12)))
            return 0;
        if (p->getSteps()->stepLeftRight== 3)
            k = 0;
        else if (p->getSteps()->stepLeftRight== 9)
            k = 1;
        if (p->getSteps()->stepLeftRight!= 0 &&
                ((this->map[(p->getCoords()->y + j) * WIDTH + p->getCoords()->x + 1 - k].perPtr &&
                  this->map[(p->getCoords()->y + j) * WIDTH + p->getCoords()->x + 1 - k].perPtr != p &&
                  this->map[(p->getCoords()->y + j) * WIDTH + p->getCoords()->x + 1 - k].perPtr->getSteps()->stepUpDown!= 6) ||
             (this->map[(p->getCoords()->y - 1 + j) * WIDTH + p->getCoords()->x + 1 - k].perPtr &&
              this->map[(p->getCoords()->y - 1 + j) * WIDTH + p->getCoords()->x + 1 - k].perPtr != p &&
              this->map[(p->getCoords()->y - 1 + j) * WIDTH + p->getCoords()->x + 1 - k].perPtr->getSteps()->stepUpDown!= 12) ||
                 (this->map[(p->getCoords()->y + j) * WIDTH + p->getCoords()->x + 2 - k].perPtr &&
                  this->map[(p->getCoords()->y + j) * WIDTH + p->getCoords()->x + 2 - k].perPtr->getSteps()->stepUpDown!= 6 &&
                  this->map[(p->getCoords()->y + j) * WIDTH + p->getCoords()->x + 2 - k].perPtr->getSteps()->stepLeftRight== 9) ||
             (this->map[(p->getCoords()->y - 1 + j) * WIDTH + p->getCoords()->x + 2 - k].perPtr &&
              this->map[(p->getCoords()->y - 1 + j) * WIDTH + p->getCoords()->x + 2 - k].perPtr->getSteps()->stepUpDown!= 12 &&
              this->map[(p->getCoords()->y - 1 + j) * WIDTH + p->getCoords()->x + 2 - k].perPtr->getSteps()->stepLeftRight== 9)))
            return 0;

    }
    return 1;
}

int Game::canMoveUp(Personage *p, int n)
{
    if (p->getSteps()->stepLeftRight== 0)
    {
        int k = 0;
        if (p->getSteps()->stepUpDown== 0 && ((this->map[(p->getCoords()->y - 1) * WIDTH + p->getCoords()->x].objPtr &&
             !(this->map[(p->getCoords()->y - 1) * WIDTH + p->getCoords()->x].objPtr->isWalkable())) ||
              (this->map[(p->getCoords()->y - 1) * WIDTH + p->getCoords()->x].perPtr &&
               this->map[(p->getCoords()->y - 1) * WIDTH + p->getCoords()->x].perPtr->isAlive() &&
               this->map[(p->getCoords()->y - 1) * WIDTH + p->getCoords()->x].perPtr->getSteps()->stepUpDown== 0) ||
          (this->map[(p->getCoords()->y - 1) * WIDTH + p->getCoords()->x - 1].perPtr &&
           this->map[(p->getCoords()->y - 1) * WIDTH + p->getCoords()->x - 1].perPtr->getSteps()->stepUpDown== 0 &&
           this->map[(p->getCoords()->y - 1) * WIDTH + p->getCoords()->x - 1].perPtr->getSteps()->stepLeftRight== 3) ||
          (this->map[(p->getCoords()->y - 1) * WIDTH + p->getCoords()->x + 1].perPtr &&
           this->map[(p->getCoords()->y - 1) * WIDTH + p->getCoords()->x + 1].perPtr->getSteps()->stepUpDown== 0 &&
           this->map[(p->getCoords()->y - 1) * WIDTH + p->getCoords()->x + 1].perPtr->getSteps()->stepLeftRight== 9)))
            return 0;
        if (p->getSteps()->stepUpDown== 12)
            k = 0;
        else if (p->getSteps()->stepUpDown== 6)
            k = 1;
        if (p->getSteps()->stepUpDown!= 0 &&
                ((this->map[(p->getCoords()->y - 1 + k) * WIDTH + p->getCoords()->x].perPtr &&
                  this->map[(p->getCoords()->y - 1 + k) * WIDTH + p->getCoords()->x].perPtr->isAlive() &&
                  this->map[(p->getCoords()->y - 1 + k) * WIDTH + p->getCoords()->x].perPtr != p) ||
             (this->map[(p->getCoords()->y - 1 + k) * WIDTH + p->getCoords()->x - 1].perPtr &&
              this->map[(p->getCoords()->y - 1 + k) * WIDTH + p->getCoords()->x - 1].perPtr->getSteps()->stepLeftRight== 3 &&
              this->map[(p->getCoords()->y - 1 + k) * WIDTH + p->getCoords()->x - 1].perPtr->getSteps()->stepUpDown== 12) ||
             (this->map[(p->getCoords()->y - 1 + k) * WIDTH + p->getCoords()->x + 1].perPtr &&
              this->map[(p->getCoords()->y - 1 + k) * WIDTH + p->getCoords()->x + 1].perPtr->getSteps()->stepLeftRight== 9 &&
              this->map[(p->getCoords()->y - 1 + k) * WIDTH + p->getCoords()->x + 1].perPtr->getSteps()->stepUpDown== 12)  ||
                 ((p->getCoords()->y - 2 + k >= 0) &&
             ((this->map[(p->getCoords()->y - 2 + k) * WIDTH + p->getCoords()->x - 1].perPtr &&
              this->map[(p->getCoords()->y - 2 + k) * WIDTH + p->getCoords()->x - 1].perPtr->getSteps()->stepLeftRight== 3 &&
              this->map[(p->getCoords()->y - 2 + k) * WIDTH + p->getCoords()->x - 1].perPtr->getSteps()->stepUpDown== 6)||
                 (this->map[(p->getCoords()->y - 2 + k) * WIDTH + p->getCoords()->x].perPtr &&
                  this->map[(p->getCoords()->y - 2 + k) * WIDTH + p->getCoords()->x].perPtr->getSteps()->stepUpDown== 6 &&
                  this->map[(p->getCoords()->y - 2 + k) * WIDTH + p->getCoords()->x].perPtr->isAlive()) ||
             (this->map[(p->getCoords()->y - 2 + k) * WIDTH + p->getCoords()->x + 1].perPtr &&
              this->map[(p->getCoords()->y - 2 + k) * WIDTH + p->getCoords()->x + 1].perPtr->getSteps()->stepLeftRight== 9 &&
              this->map[(p->getCoords()->y - 2 + k) * WIDTH + p->getCoords()->x + 1].perPtr->getSteps()->stepUpDown== 6)))))
            return 0;
            if (p->getSteps()->stepUpDown== 0 &&
                ((this->map[(p->getCoords()->y - 1) * WIDTH + p->getCoords()->x].perPtr &&
                 !this->map[(p->getCoords()->y - 1) * WIDTH + p->getCoords()->x].perPtr->isAlive() &&
                  this->map[(p->getCoords()->y - 1) * WIDTH + p->getCoords()->x].perPtr->getSteps()->stepUpDown== 0)))
            {
                if (this->canMoveUp(this->map[(p->getCoords()->y - 1) * WIDTH + p->getCoords()->x].perPtr, n+1))
                    return 2;
                return 0;
            }
            if (p->getSteps()->stepUpDown!= 0 &&
                    (this->map[(p->getCoords()->y - 1 + k) * WIDTH + p->getCoords()->x].perPtr &&
                    !this->map[(p->getCoords()->y - 1 + k) * WIDTH + p->getCoords()->x].perPtr->isAlive() &&
                     this->map[(p->getCoords()->y - 1 + k) * WIDTH + p->getCoords()->x].perPtr->getSteps()->stepUpDown== 12))
            {
                if (this->canMoveUp(this->map[(p->getCoords()->y - 1 + k) * WIDTH + p->getCoords()->x].perPtr, n+1))
                    return 2;
                return 0;
            }

            if (p->getCoords()->y > 1 && p->getSteps()->stepUpDown!= 0 &&
                    (this->map[(p->getCoords()->y - 2 + k) * WIDTH + p->getCoords()->x].perPtr &&
                    !this->map[(p->getCoords()->y - 2 + k) * WIDTH + p->getCoords()->x].perPtr->isAlive() &&
                     this->map[(p->getCoords()->y - 2 + k) * WIDTH + p->getCoords()->x].perPtr->getSteps()->stepUpDown== 6))
            {
                if (this->canMoveUp(this->map[(p->getCoords()->y - 2 + k) * WIDTH + p->getCoords()->x].perPtr, n+1))
                    return 3;
                return 0;
            }
    }
     else
    {
            int j = 0;
            int k = 0;
        if (p->getSteps()->stepLeftRight== 3)
                j = 0;
            else if (p->getSteps()->stepLeftRight== 9)
                j = 1;
        if (p->getSteps()->stepUpDown== 0 &&
                ((this->map[(p->getCoords()->y - 1) * WIDTH + p->getCoords()->x - j].objPtr &&
                !(this->map[(p->getCoords()->y - 1) * WIDTH + p->getCoords()->x - j].objPtr->isWalkable())) ||
             (this->map[(p->getCoords()->y - 1) * WIDTH + p->getCoords()->x + 1 - j].objPtr &&
            !(this->map[(p->getCoords()->y - 1) * WIDTH + p->getCoords()->x + 1 - j].objPtr->isWalkable())) ||
             (this->map[(p->getCoords()->y - 1) * WIDTH + p->getCoords()->x - j].perPtr &&
              this->map[(p->getCoords()->y - 1) * WIDTH + p->getCoords()->x - j].perPtr->getSteps()->stepLeftRight!= 9 &&
              this->map[(p->getCoords()->y - 1) * WIDTH + p->getCoords()->x - j].perPtr->getSteps()->stepUpDown!= 12) ||
         (this->map[(p->getCoords()->y - 1) * WIDTH + p->getCoords()->x + 1 - j].perPtr &&
          this->map[(p->getCoords()->y - 1) * WIDTH + p->getCoords()->x + 1 - j].perPtr->getSteps()->stepLeftRight!= 3 &&
          this->map[(p->getCoords()->y - 1) * WIDTH + p->getCoords()->x + 1 - j].perPtr->getSteps()->stepUpDown!= 12)))
            return 0;
        if (p->getSteps()->stepUpDown== 12)
            k = 0;
        else if (p->getSteps()->stepUpDown== 6)
            k = 1;
        if (p->getSteps()->stepUpDown!= 0 &&
                        ((this->map[(p->getCoords()->y - 1 + k) * WIDTH + p->getCoords()->x - j].perPtr &&
                          this->map[(p->getCoords()->y - 1 + k) * WIDTH + p->getCoords()->x - j].perPtr != p &&
                          this->map[(p->getCoords()->y - 1 + k) * WIDTH + p->getCoords()->x - j].perPtr->getSteps()->stepLeftRight!= 9) ||
                (this->map[(p->getCoords()->y - 1 + k) * WIDTH + p->getCoords()->x + 1 - j].perPtr &&
                 this->map[(p->getCoords()->y - 1 + k) * WIDTH + p->getCoords()->x + 1 - j].perPtr != p &&
                  this->map[(p->getCoords()->y - 1 + k) * WIDTH + p->getCoords()->x + 1 - j].perPtr->getSteps()->stepLeftRight!= 3) ||
                         ((p->getCoords()->y > 1) &&
                         ((this->map[(p->getCoords()->y - 2 + k) * WIDTH + p->getCoords()->x - j].perPtr &&
                           this->map[(p->getCoords()->y - 2 + k) * WIDTH + p->getCoords()->x - j].perPtr->getSteps()->stepLeftRight!= 9 &&
                          this->map[(p->getCoords()->y  - 2 + k) * WIDTH + p->getCoords()->x - j].perPtr->getSteps()->stepUpDown== 6) ||
                         (this->map[(p->getCoords()->y - 2 + k) * WIDTH + p->getCoords()->x + 1 - j].perPtr &&
                           this->map[(p->getCoords()->y - 2 + k) * WIDTH + p->getCoords()->x + 1 - j].perPtr->getSteps()->stepLeftRight!= 3 &&
                          this->map[(p->getCoords()->y - 2 + k) * WIDTH + p->getCoords()->x + 1 - j].perPtr->getSteps()->stepUpDown== 6)))))
            return 0;

    }
    return 1;
}

int Game::canMoveDown(Personage *p, int n)
{
    if (p->getSteps()->stepLeftRight== 0)
    {
        int k = 0;
        if (p->getSteps()->stepUpDown== 0 && ((this->map[(p->getCoords()->y + 1) * WIDTH + p->getCoords()->x].objPtr &&
             !(this->map[(p->getCoords()->y + 1) * WIDTH + p->getCoords()->x].objPtr->isWalkable())) ||
              (this->map[(p->getCoords()->y + 1) * WIDTH + p->getCoords()->x].perPtr &&
               this->map[(p->getCoords()->y + 1) * WIDTH + p->getCoords()->x].perPtr->isAlive() &&
               this->map[(p->getCoords()->y + 1) * WIDTH + p->getCoords()->x].perPtr->getSteps()->stepUpDown== 0) ||
          (this->map[(p->getCoords()->y + 1) * WIDTH + p->getCoords()->x - 1].perPtr &&
           this->map[(p->getCoords()->y + 1) * WIDTH + p->getCoords()->x - 1].perPtr->getSteps()->stepUpDown== 0 &&
           this->map[(p->getCoords()->y + 1) * WIDTH + p->getCoords()->x - 1].perPtr->getSteps()->stepLeftRight== 3) ||
          (this->map[(p->getCoords()->y + 1) * WIDTH + p->getCoords()->x + 1].perPtr &&
           this->map[(p->getCoords()->y + 1) * WIDTH + p->getCoords()->x + 1].perPtr->getSteps()->stepUpDown== 0 &&
           this->map[(p->getCoords()->y + 1) * WIDTH + p->getCoords()->x + 1].perPtr->getSteps()->stepLeftRight== 9)))
            return 0;
        if (p->getSteps()->stepUpDown== 6)
            k = 0;
        else if (p->getSteps()->stepUpDown== 12)
            k = 1;
        if (p->getSteps()->stepUpDown!= 0 &&
                ((this->map[(p->getCoords()->y + 1 - k) * WIDTH + p->getCoords()->x].perPtr &&
                  this->map[(p->getCoords()->y + 1 - k) * WIDTH + p->getCoords()->x].perPtr->isAlive() &&
                  this->map[(p->getCoords()->y + 1 - k) * WIDTH + p->getCoords()->x].perPtr != p) ||
             (this->map[(p->getCoords()->y + 1 - k) * WIDTH + p->getCoords()->x - 1].perPtr &&
              this->map[(p->getCoords()->y + 1 - k) * WIDTH + p->getCoords()->x - 1].perPtr->getSteps()->stepLeftRight== 3 &&
              this->map[(p->getCoords()->y + 1 - k) * WIDTH + p->getCoords()->x - 1].perPtr->getSteps()->stepUpDown== 6) ||
             (this->map[(p->getCoords()->y + 1 - k) * WIDTH + p->getCoords()->x + 1].perPtr &&
              this->map[(p->getCoords()->y + 1 - k) * WIDTH + p->getCoords()->x + 1].perPtr->getSteps()->stepLeftRight== 9 &&
              this->map[(p->getCoords()->y + 1 - k) * WIDTH + p->getCoords()->x + 1].perPtr->getSteps()->stepUpDown== 6)  ||
             (this->map[(p->getCoords()->y + 2 - k) * WIDTH + p->getCoords()->x - 1].perPtr &&
              this->map[(p->getCoords()->y + 2 - k) * WIDTH + p->getCoords()->x - 1].perPtr->getSteps()->stepLeftRight== 3 &&
              this->map[(p->getCoords()->y + 2 - k) * WIDTH + p->getCoords()->x - 1].perPtr->getSteps()->stepUpDown== 12)||
                 (this->map[(p->getCoords()->y + 2 - k) * WIDTH + p->getCoords()->x].perPtr &&
                  this->map[(p->getCoords()->y + 2 - k) * WIDTH + p->getCoords()->x].perPtr->getSteps()->stepUpDown== 12 &&
                  this->map[(p->getCoords()->y + 2 - k) * WIDTH + p->getCoords()->x].perPtr->isAlive()) ||
             (this->map[(p->getCoords()->y + 2 - k) * WIDTH + p->getCoords()->x + 1].perPtr &&
              this->map[(p->getCoords()->y + 2 - k) * WIDTH + p->getCoords()->x + 1].perPtr->getSteps()->stepLeftRight== 9 &&
              this->map[(p->getCoords()->y + 2 - k) * WIDTH + p->getCoords()->x + 1].perPtr->getSteps()->stepUpDown== 12)))
            return 0;
            if (p->getSteps()->stepUpDown== 0 &&
                ((this->map[(p->getCoords()->y + 1) * WIDTH + p->getCoords()->x].perPtr &&
                 !this->map[(p->getCoords()->y + 1) * WIDTH + p->getCoords()->x].perPtr->isAlive() &&
                  this->map[(p->getCoords()->y + 1) * WIDTH + p->getCoords()->x].perPtr->getSteps()->stepUpDown== 0)))
            {
                if (this->canMoveDown(this->map[(p->getCoords()->y + 1) * WIDTH + p->getCoords()->x].perPtr, n+1))
                    return 2;
                return 0;
            }
            if (p->getSteps()->stepUpDown!= 0 &&
                    (this->map[(p->getCoords()->y + 1 - k) * WIDTH + p->getCoords()->x].perPtr &&
                    !this->map[(p->getCoords()->y + 1 - k) * WIDTH + p->getCoords()->x].perPtr->isAlive() &&
                     this->map[(p->getCoords()->y + 1 - k) * WIDTH + p->getCoords()->x].perPtr->getSteps()->stepUpDown== 6))
            {
                if (this->canMoveDown(this->map[(p->getCoords()->y + 1 - k) * WIDTH + p->getCoords()->x].perPtr, n+1))
                    return 2;
                return 0;
            }

            if (p->getSteps()->stepUpDown!= 0 &&
                    (this->map[(p->getCoords()->y + 2 - k) * WIDTH + p->getCoords()->x].perPtr &&
                    !this->map[(p->getCoords()->y + 2 - k) * WIDTH + p->getCoords()->x].perPtr->isAlive() &&
                     this->map[(p->getCoords()->y + 2 - k) * WIDTH + p->getCoords()->x].perPtr->getSteps()->stepUpDown== 12))
            {
                if (this->canMoveDown(this->map[(p->getCoords()->y + 2 - k) * WIDTH + p->getCoords()->x].perPtr, n+1))
                    return 3;
                return 0;
            }
    }
     else
    {
            int j = 0;
            int k = 0;
        if (p->getSteps()->stepLeftRight== 3)
                j = 0;
            else if (p->getSteps()->stepLeftRight== 9)
                j = 1;
        if (p->getSteps()->stepUpDown== 0 &&
                ((this->map[(p->getCoords()->y + 1) * WIDTH + p->getCoords()->x - j].objPtr &&
                !(this->map[(p->getCoords()->y + 1) * WIDTH + p->getCoords()->x - j].objPtr->isWalkable())) ||
             (this->map[(p->getCoords()->y + 1) * WIDTH + p->getCoords()->x + 1 - j].objPtr &&
            !(this->map[(p->getCoords()->y + 1) * WIDTH + p->getCoords()->x + 1 - j].objPtr->isWalkable())) ||
             (this->map[(p->getCoords()->y + 1) * WIDTH + p->getCoords()->x - j].perPtr &&
              this->map[(p->getCoords()->y + 1) * WIDTH + p->getCoords()->x - j].perPtr->getSteps()->stepLeftRight!= 9 &&
              this->map[(p->getCoords()->y + 1) * WIDTH + p->getCoords()->x - j].perPtr->getSteps()->stepUpDown!= 6) ||
         (this->map[(p->getCoords()->y + 1) * WIDTH + p->getCoords()->x + 1 - j].perPtr &&
          this->map[(p->getCoords()->y + 1) * WIDTH + p->getCoords()->x + 1 - j].perPtr->getSteps()->stepLeftRight!= 3 &&
          this->map[(p->getCoords()->y + 1) * WIDTH + p->getCoords()->x + 1 - j].perPtr->getSteps()->stepUpDown!= 6)))
            return 0;
        if (p->getSteps()->stepUpDown== 6)
            k = 0;
        else if (p->getSteps()->stepUpDown== 12)
            k = 1;
        if (p->getSteps()->stepUpDown!= 0 &&
                        ((this->map[(p->getCoords()->y + 1 - k) * WIDTH + p->getCoords()->x - j].perPtr &&
                          this->map[(p->getCoords()->y + 1 - k) * WIDTH + p->getCoords()->x - j].perPtr != p &&
                          this->map[(p->getCoords()->y + 1 - k) * WIDTH + p->getCoords()->x - j].perPtr->getSteps()->stepLeftRight!= 9) ||
                (this->map[(p->getCoords()->y + 1 - k) * WIDTH + p->getCoords()->x + 1 - j].perPtr &&
                 this->map[(p->getCoords()->y + 1 - k) * WIDTH + p->getCoords()->x + 1 - j].perPtr != p &&
                  this->map[(p->getCoords()->y + 1 - k) * WIDTH + p->getCoords()->x + 1 - j].perPtr->getSteps()->stepLeftRight!= 3) ||
                         (this->map[(p->getCoords()->y + 2 - k) * WIDTH + p->getCoords()->x - j].perPtr &&
                           this->map[(p->getCoords()->y + 2 - k) * WIDTH + p->getCoords()->x - j].perPtr->getSteps()->stepLeftRight!= 9 &&
                          this->map[(p->getCoords()->y + 2 - k) * WIDTH + p->getCoords()->x - j].perPtr->getSteps()->stepUpDown== 12) ||
                         (this->map[(p->getCoords()->y + 2 - k) * WIDTH + p->getCoords()->x + 1 - j].perPtr &&
                           this->map[(p->getCoords()->y + 2 - k) * WIDTH + p->getCoords()->x + 1 - j].perPtr->getSteps()->stepLeftRight!= 3 &&
                          this->map[(p->getCoords()->y + 2 - k) * WIDTH + p->getCoords()->x + 1 - j].perPtr->getSteps()->stepUpDown== 12)))
            return 0;

    }
    return 1;
}

void Game::moveLeft(Personage *p, QTimer *timer)
{
    int *x1 = new int;
    int *y1 = new int;
    int *x2 = new int;
    int *y2 = new int;
    static int steps = 0;
    static bool mooving = false;
    p->getRect().getCoords(x1, y1, x2, y2);
    if (this->canMoveLeft(p))
    {
        Personage *per = nullptr;
        if (this->canMoveLeft(p) > 1)
        {
            mooving = true;
            if (this->canMoveLeft(p) == 2)
                per = this->map[p->getCoords()->y * WIDTH + p->getCoords()->x - 1].perPtr;
            else
                per = this->map[p->getCoords()->y * WIDTH + p->getCoords()->x - 2].perPtr;
        }
        p->pImage.rect.moveLeft(*x1 - SIZE/32);

        if (mooving && per)
        {
            per->getRect().getCoords(x1, y1, x2, y2);
            per->pImage.rect.moveLeft(*x1 - SIZE/32);
        }
        steps+=SIZE / 32;
        if (steps >= SIZE/32*2 && steps < SIZE/32*4)
        {
            p->setImgName("lololeft1");
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += p->getImgName();
            path += ".png";
            p->getPixmap() = QPixmap(path.c_str());
        }
        else if (steps >= SIZE/32*4 && steps < SIZE/32*6)
        {
            p->setImgName("lololeft2");
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += p->getImgName();
            path += ".png";
            p->getPixmap() = QPixmap(path.c_str());
        }
        else if (steps >= SIZE/32*6 && steps < SIZE/32*8)
        {
            p->setImgName("lololeft1");
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += p->getImgName();
            path += ".png";
            p->getPixmap() =  QPixmap(path.c_str());
        }
        else if (steps >= SIZE/32*8 && steps < SIZE/32*10)
        {
            p->setImgName("lololeft3");
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += p->getImgName();
            path += ".png";
            p->getPixmap() = QPixmap(path.c_str());
        }
        else if (steps >= SIZE/32*10 && steps < SIZE/32*12)
        {
            p->setImgName("lololeft4");
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += p->getImgName();
            path += ".png";
            p->getPixmap() = QPixmap(path.c_str());
        }
        else if (steps >= SIZE/32*12 && steps < SIZE/32*14)
        {
            p->setImgName("lololeft3");
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += p->getImgName();
            path += ".png";
            p->getPixmap() = QPixmap(path.c_str());
        }
        else if (steps >= SIZE/32*14 && steps < SIZE/32*16)
        {
            p->setImgName("lololeft");
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += p->getImgName();
            path += ".png";
            p->getPixmap() = QPixmap(path.c_str());
        }
        else if (steps == SIZE/2)
        {
            if (p->getSteps()->stepLeftRight)
            {
                if (p->getSteps()->stepLeftRight== 9)
                {
                    if (mooving && per)
                    {
                        if (this->canMoveLeft(p) == 2)
                        {
                            per->getCoords()->x--;
                            this->map[per->getCoords()->y * WIDTH + per->getCoords()->x].perPtr = per;
                            this->map[per->getCoords()->y * WIDTH + per->getCoords()->x + 1].perPtr = nullptr;
                        }
                    }
                    p->getCoords()->x--;
                    if (this->map[p->getCoords()->y * WIDTH + p->getCoords()->x + 1].perPtr == p)
                    this->map[p->getCoords()->y * WIDTH + p->getCoords()->x + 1].perPtr = nullptr;
                    if (p->getSteps()->stepUpDown== 12 && this->map[(p->getCoords()->y - 1) * WIDTH + p->getCoords()->x + 1].perPtr == p)
                        this->map[(p->getCoords()->y - 1) * WIDTH + p->getCoords()->x + 1].perPtr = nullptr;
                    if (p->getSteps()->stepUpDown== 6 && this->map[(p->getCoords()->y + 1) * WIDTH + p->getCoords()->x + 1].perPtr == p)
                        this->map[(p->getCoords()->y + 1) * WIDTH + p->getCoords()->x + 1].perPtr = nullptr;
                    if (!this->map[p->getCoords()->y * WIDTH + p->getCoords()->x].perPtr)
                    this->map[p->getCoords()->y * WIDTH + p->getCoords()->x].perPtr = p;
                }
                {
                    if (mooving && per)
                        per->getSteps()->stepLeftRight = 0;
                    p->getSteps()->stepLeftRight = 0;
                }
            }
        else
            {
                if (mooving && per)
                    per->getSteps()->stepLeftRight = 9;
                p->getSteps()->stepLeftRight = 9;
            }
        steps = 0;
        timer->stop();
        mooving = false;
        }
    }
    else
        timer->stop();
    delete x1;
    delete x2;
    delete y1;
    delete y2;
}

void Game::moveRight(Personage *p, QTimer *timer)
{
    int *x1 = new int;
    int *y1 = new int;
    int *x2 = new int;
    int *y2 = new int;
    static int steps = 0;
    static bool mooving = false;
    p->getRect().getCoords(x1, y1, x2, y2);
    if (this->canMoveRight(p))
    {
        Personage *per = nullptr;
        if (this->canMoveRight(p) > 1)
        {
            mooving = true;
            if (this->canMoveRight(p) == 2)
                per = this->map[p->getCoords()->y * WIDTH + p->getCoords()->x + 1].perPtr;
            else
                per = this->map[p->getCoords()->y * WIDTH + p->getCoords()->x + 2].perPtr;
        }
        p->pImage.rect.moveLeft(*x1 + SIZE/32);
        if (mooving && per)
        {
            per->getRect().getCoords(x1, y1, x2, y2);
            per->pImage.rect.moveLeft(*x1 + SIZE/32);
        }
        steps += SIZE / 32;
        if (steps >= SIZE/32*2 && steps < SIZE/32*4)
        {
            p->setImgName("loloright1");
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += p->getImgName();
            path += ".png";
            p->getPixmap() = QPixmap(path.c_str());
        }
        else if (steps >= SIZE/32*4 && steps < SIZE/32*6)
        {
            p->setImgName("loloright2");
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += p->getImgName();
            path += ".png";
            p->getPixmap() = QPixmap(path.c_str());
        }
        else if (steps >= SIZE/32*6 && steps < SIZE/32*8)
        {
            p->setImgName("loloright1");
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += p->getImgName();
            path += ".png";
            p->getPixmap() = QPixmap(path.c_str());
        }
        else if (steps >= SIZE/32*8 && steps < SIZE/32*10)
        {
            p->setImgName("loloright3");
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += p->getImgName();
            path += ".png";
            p->getPixmap() = QPixmap(path.c_str());
        }
        else if (steps >= SIZE/32*10 && steps < SIZE/32*12)
        {
            p->setImgName("loloright4");
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += p->getImgName();
            path += ".png";
            p->getPixmap() = QPixmap(path.c_str());
        }
        else if (steps >= SIZE/32*12 && steps < SIZE/32*14)
        {
            p->setImgName("loloright3");
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += p->getImgName();
            path += ".png";
            p->getPixmap() = QPixmap(path.c_str());
        }
        else if (steps >= SIZE/32*14 && steps < SIZE/32*16)
        {
            p->setImgName("loloright");
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += p->getImgName();
            path += ".png";
            p->getPixmap() = QPixmap(path.c_str());
        }
        else if (steps == SIZE/2)
        {
            if (p->getSteps()->stepLeftRight)
            {
                if (p->getSteps()->stepLeftRight== 3)
                {
                    if (mooving && per)
                    {
                        if (this->canMoveRight(p) == 2)
                        {
                            per->getCoords()->x++;
                            this->map[per->getCoords()->y * WIDTH + per->getCoords()->x].perPtr = per;
                            this->map[per->getCoords()->y * WIDTH + per->getCoords()->x - 1].perPtr = nullptr;
                        }
                    }
                    p->getCoords()->x++;
                    if (this->map[p->getCoords()->y * WIDTH + p->getCoords()->x - 1].perPtr == p)
                    this->map[p->getCoords()->y * WIDTH + p->getCoords()->x - 1].perPtr = nullptr;
                    if (p->getSteps()->stepUpDown== 12 && this->map[(p->getCoords()->y - 1) * WIDTH + p->getCoords()->x - 1].perPtr == p)
                        this->map[(p->getCoords()->y - 1) * WIDTH + p->getCoords()->x - 1].perPtr = nullptr;
                    if (p->getSteps()->stepUpDown== 6 && this->map[(p->getCoords()->y + 1) * WIDTH + p->getCoords()->x - 1].perPtr == p)
                        this->map[(p->getCoords()->y + 1) * WIDTH + p->getCoords()->x - 1].perPtr = nullptr;
                    if (!this->map[p->getCoords()->y * WIDTH + p->getCoords()->x].perPtr)
                        this->map[p->getCoords()->y * WIDTH + p->getCoords()->x].perPtr = p;
                }
                {
                    if (mooving && per)
                        per->getSteps()->stepLeftRight = 0;
                    p->getSteps()->stepLeftRight = 0;
                }
            }
        else
            {
                if (mooving && per)
                    per->getSteps()->stepLeftRight = 3;
                p->getSteps()->stepLeftRight = 3;
            }
        steps = 0;
        timer->stop();
        mooving = false;
        }
    }
    else
        timer->stop();
    delete x1;
    delete x2;
    delete y1;
    delete y2;
}

void Game::moveUp(Personage *p, QTimer *timer)
{
    int *x1 = new int;
    int *y1 = new int;
    int *x2 = new int;
    int *y2 = new int;
    static int steps = 0;
    static bool mooving = false;
    p->getRect().getCoords(x1, y1, x2, y2);
    if (this->canMoveUp(p))
    {
        Personage *per = nullptr;
        if (this->canMoveUp(p) > 1)
        {
            mooving = true;
            if (this->canMoveUp(p) == 2)
                per = this->map[(p->getCoords()->y - 1) * WIDTH + p->getCoords()->x].perPtr;
            else
                per = this->map[(p->getCoords()->y - 2) * WIDTH + p->getCoords()->x].perPtr;
        }
        p->pImage.rect.moveTop(*y1 - SIZE/32);
        if (mooving && per)
        {
            per->getRect().getCoords(x1, y1, x2, y2);
            per->pImage.rect.moveTop(*y1 - SIZE/32);
        }
        steps+=SIZE / 32;
        if (steps >= SIZE/32*2 && steps < SIZE/32*4)
        {
            p->setImgName("loloup1");
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += p->getImgName();
            path += ".png";
            p->getPixmap() = QPixmap(path.c_str());
        }
        else if (steps >= SIZE/32*4 && steps < SIZE/32*6)
        {
            p->setImgName("loloup2");
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += p->getImgName();
            path += ".png";
            p->getPixmap() = QPixmap(path.c_str());
        }
        else if (steps >= SIZE/32*6 && steps < SIZE/32*8)
        {
            p->setImgName("loloup1");
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += p->getImgName();
            path += ".png";
            p->getPixmap() = QPixmap(path.c_str());
        }
        else if (steps >= SIZE/32*8 && steps < SIZE/32*10)
        {
            p->setImgName("loloup3");
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += p->getImgName();
            path += ".png";
            p->getPixmap() = QPixmap(path.c_str());
        }
        else if (steps >= SIZE/32*10 && steps < SIZE/32*12)
        {
            p->setImgName("loloup4");
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += p->getImgName();
            path += ".png";
            p->getPixmap() = QPixmap(path.c_str());
        }
        else if (steps >= SIZE/32*12 && steps < SIZE/32*14)
        {
            p->setImgName("loloup3");
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += p->getImgName();
            path += ".png";
            p->getPixmap() = QPixmap(path.c_str());
        }
        else if (steps >= SIZE/32*14 && steps < SIZE/32*16)
        {
            p->setImgName("loloup");
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += p->getImgName();
            path += ".png";
            p->getPixmap() = QPixmap(path.c_str());
        }
        else if (steps == SIZE/2)
        {
            if (p->getSteps()->stepUpDown)
            {
                if (p->getSteps()->stepUpDown == 12)
                {
                    if (mooving && per)
                    {
                        if (this->canMoveUp(p) == 2)
                        {
                            per->setCoords(per->getCoords()->x, per->getCoords()->y - 1);
                            this->map[per->getCoords()->y * WIDTH + per->getCoords()->x].perPtr = per;
                            this->map[(per->getCoords()->y + 1) * WIDTH + per->getCoords()->x].perPtr = nullptr;
                        }
                    }
                    p->setCoords(p->getCoords()->x, p->getCoords()->y - 1);
                    if (this->map[(p->getCoords()->y + 1) * WIDTH + p->getCoords()->x].perPtr == p)
                    this->map[(p->getCoords()->y + 1) * WIDTH + p->getCoords()->x].perPtr = nullptr;
                    if (p->getSteps()->stepLeftRight== 9 && this->map[(p->getCoords()->y + 1) * WIDTH + p->getCoords()->x - 1].perPtr == p)
                        this->map[(p->getCoords()->y + 1) * WIDTH + p->getCoords()->x - 1].perPtr = nullptr;
                    if (p->getSteps()->stepLeftRight== 3 && this->map[(p->getCoords()->y + 1) * WIDTH + p->getCoords()->x + 1].perPtr == p)
                        this->map[(p->getCoords()->y + 1) * WIDTH + p->getCoords()->x + 1].perPtr = nullptr;
                    if (!this->map[p->getCoords()->y * WIDTH + p->getCoords()->x].perPtr)
                    this->map[p->getCoords()->y * WIDTH + p->getCoords()->x].perPtr = p;
                }
                {
                    {
                        if (mooving && per)
                            per->getSteps()->stepUpDown = 0;
                        p->getSteps()->stepUpDown = 0;
                    }
                }
            }
        else
            {
                if (mooving && per)
                    per->getSteps()->stepUpDown = 12;
                p->getSteps()->stepUpDown = 12;
            }
        steps = 0;
        timer->stop();
        mooving = false;
        }
    }
    else
        timer->stop();
    delete x1;
    delete x2;
    delete y1;
    delete y2;
}

void Game::moveDown(Personage *p, QTimer *timer)
{
    int *x1 = new int;
    int *y1 = new int;
    int *x2 = new int;
    int *y2 = new int;
    static int steps = 0;
    static bool mooving = false;
    p->getRect().getCoords(x1, y1, x2, y2);
    if (this->canMoveDown(p))
    {
        Personage *per = nullptr;
        if (this->canMoveDown(p) > 1)
        {
            mooving = true;
            if (this->canMoveDown(p) == 2)
                per = this->map[(p->getCoords()->y + 1) * WIDTH + p->getCoords()->x].perPtr;
            else
                per = this->map[(p->getCoords()->y + 2) * WIDTH + p->getCoords()->x].perPtr;
        }
        p->pImage.rect.moveTop(*y1 + SIZE/32);
        if (mooving && per)
        {
            per->getRect().getCoords(x1, y1, x2, y2);
            per->getRect().moveTop(*y1 + SIZE/32);
        }
        steps+=SIZE / 32;
        if (steps >= SIZE/32*2 && steps < SIZE/32*4)
        {
            p->setImgName("lolodown1");
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += p->getImgName();
            path += ".png";
            p->getPixmap() = QPixmap(path.c_str());
        }
        else if (steps >= SIZE/32*4 && steps < SIZE/32*6)
        {
            p->setImgName("lolodown2");
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += p->getImgName();
            path += ".png";
            p->getPixmap() = QPixmap(path.c_str());
        }
        else if (steps >= SIZE/32*6 && steps < SIZE/32*8)
        {
            p->setImgName("lolodown1");
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += p->getImgName();
            path += ".png";
            p->getPixmap() = QPixmap(path.c_str());
        }
        else if (steps >= SIZE/32*8 && steps < SIZE/32*10)
        {
            p->setImgName("lolodown3");
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += p->getImgName();
            path += ".png";
            p->getPixmap() = QPixmap(path.c_str());
        }
        else if (steps >= SIZE/32*10 && steps < SIZE/32*12)
        {
            p->setImgName("lolodown4");
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += p->getImgName();
            path += ".png";
            p->getPixmap() = QPixmap(path.c_str());
        }
        else if (steps >= SIZE/32*12 && steps < SIZE/32*14)
        {
            p->setImgName("lolodown3");
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += p->getImgName();
            path += ".png";
            p->getPixmap() = QPixmap(path.c_str());
        }
        else if (steps >= SIZE/32*14 && steps < SIZE/32*16)
        {
            p->setImgName("lolo");
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += p->getImgName();
            path += ".png";
            p->getPixmap() = QPixmap(path.c_str());
        }
        else if (steps == SIZE/2)
        {
            if (p->getSteps()->stepUpDown)
            {
                if (p->getSteps()->stepUpDown== 6)
                {
                    if (mooving && per)
                    {
                        if (this->canMoveDown(p) == 2)
                        {
                            per->setCoords(per->getCoords()->x, per->getCoords()->y + 1);

                            this->map[per->getCoords()->y * WIDTH + per->getCoords()->x].perPtr = per;
                            this->map[(per->getCoords()->y - 1) * WIDTH + per->getCoords()->x].perPtr = nullptr;
                        }
                    }
                    p->setCoords(p->getCoords()->x, p->getCoords()->y + 1);
                    if (this->map[(p->getCoords()->y - 1) * WIDTH + p->getCoords()->x].perPtr == p)
                    this->map[(p->getCoords()->y - 1) * WIDTH + p->getCoords()->x].perPtr = nullptr;
                    if (p->getSteps()->stepLeftRight== 9 && this->map[(p->getCoords()->y - 1) * WIDTH + p->getCoords()->x - 1].perPtr == p)
                        this->map[(p->getCoords()->y - 1) * WIDTH + p->getCoords()->x - 1].perPtr = nullptr;
                    if (p->getSteps()->stepLeftRight== 3 && this->map[(p->getCoords()->y - 1) * WIDTH + p->getCoords()->x + 1].perPtr == p)
                        this->map[(p->getCoords()->y - 1) * WIDTH + p->getCoords()->x + 1].perPtr = nullptr;
                    if (!this->map[p->getCoords()->y * WIDTH + p->getCoords()->x].perPtr)
                    this->map[p->getCoords()->y * WIDTH + p->getCoords()->x].perPtr = p;
                }
                {
                    if (mooving && per)
                        per->getSteps()->stepUpDown = 0;
                    p->getSteps()->stepUpDown = 0;
                }
            }
        else
            {
                if (mooving && per)
                    per->getSteps()->stepUpDown = 6;
                p->getSteps()->stepUpDown = 6;
            }
        steps = 0;
        timer->stop();
        mooving = false;
        }
    }
    else
        timer->stop();
    delete x1;
    delete x2;
    delete y1;
    delete y2;
}
void Game::checkPickUp()
{
    if (this->getMap()[lolo->getCoords()->y * WIDTH + lolo->getCoords()->x].objPtr &&
            dynamic_cast<Heart*>(this->getMap()[lolo->getCoords()->y * WIDTH + lolo->getCoords()->x].objPtr))
    {
        lolo->setShoots(lolo->getShoots()+2);
        lolo->setHeartsPicked(lolo->getHeartsPicked()+1);
        if (lolo->getHeartsPicked() == this->getHeartsToPick())
            this->getChest()->open();
        delete dynamic_cast<Heart*>(this->getMap()[lolo->getCoords()->y * WIDTH + lolo->getCoords()->x].objPtr);
        this->getMap()[lolo->getCoords()->y * WIDTH + lolo->getCoords()->x].objPtr = nullptr;
    }
    if (this->getMap()[lolo->getCoords()->y * WIDTH + lolo->getCoords()->x].objPtr &&
        this->getMap()[lolo->getCoords()->y * WIDTH + lolo->getCoords()->x].objPtr == this->getChest() &&
            this->getChest()->isOpened() && this->getChest()->hasJewellery())
    {
        this->getChest()->finish();
        this->clear();
        this->getEXit()->setImgName("exitopen");
        this->getEXit()->makeWalkable();
        this->setFirstDraw(true);
    }
    if (this->getMap()[lolo->getCoords()->y * WIDTH + lolo->getCoords()->x].objPtr &&
        this->getMap()[lolo->getCoords()->y * WIDTH + lolo->getCoords()->x].objPtr == this->getEXit())
    {
        this->disactivate();
        this->nextLevel();
        this->getWidget()->connectTimers();
        this->activate();
    }
}

int Game::shooted(Personage *p, int x, int y)
{
    if ((this->map[y * WIDTH + x].objPtr || this->map[y * WIDTH + x].perPtr) &&
            this->map[y * WIDTH + x].perPtr != p)
    {
        if (this->map[y * WIDTH + x].perPtr)
            return 2;
        if (!this->map[y * WIDTH + x].objPtr->isShootable())
        {
            return 1;
        }
    }
    return 0;
}
