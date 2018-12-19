#ifndef GAME_H
# define GAME_H
# include <iostream>
# include "chest.h"
# include "heart.h"
# include "lolo.h"
# include "snakey.h"
# include "gol.h"
# include <memory>

class Widget;

struct  cell
{
    Object     *objPtr;
    Personage  *perPtr;
    char        typeOfSurface;
};

class Map
{
private:
    std::unique_ptr<cell[]> map;
public:
    Map() {map.reset(new cell[HEIGHT * WIDTH]);}
    auto begin() {return map.get();}
    auto end() {return map.get() + sizeof(cell) * (HEIGHT + WIDTH - 1);}
};

class Game
{
private:

    int     heartsToPick;
    int     lives;
    int     level;
    bool    active;
    bool    firstDraw;
    //Map     *map;
    std::shared_ptr<cell[]> map;
    Lolo    *lolo;
    Chest   *chest;
    Object *exit;
    Widget  *w;
public:
    Game(Widget *w);

    void readFromFile(std::string fileName);
    void restartLevel();
    void nextLevel();

    std::shared_ptr<cell[]>    getMap();
    Map*     getClassMap();
    Lolo*    getLolo();
    Chest*   getChest();
    bool    isActive();
    Object* getEXit();
    void    disactivate();
    void    activate();
    int     getHeartsToPick();
    bool    getFirstDraw();
    void    setFirstDraw(bool f);
    void    setLvl(int lvl);
    int     getLives();
    void     setLives(int lives);
    void    clear();
    Widget *getWidget();
    ~Game();
};

#endif // GAME_H
