#ifndef GAME_H
# define GAME_H
# include <iostream>
# include "chest.h"
# include "heart.h"
# include "lolo.h"
class Widget;

class Game
{
private:
    struct  cell
    {
        Objects     *objPtr;
        Personages  *perPtr;
        char        typeOfSurface;
    };

    int     heartsToPick;
    int     lives;
    int     level;
    bool    active;
    bool    firstDraw;
    cell    *map;
    Lolo    *lolo;
    Chest   *chest;
    Objects *exit;
    Widget  *w;
public:

    bool            wasHeartPicked();
    void            setHeartPickedStatus(bool picked);

    Game(Widget *w);

    void readFromFile(std::string fileName);
    void nextLevel();

    cell    *getMap();
    Lolo    *getLolo();
    Chest   *getChest();
    bool    isActive();
    Objects *getEXit();
    void    disactivate();
    void    activate();
    int     getHeartsToPick();
    bool    getFirstDraw();
    void    setFirstDraw(bool f);
    void    clear();
    Widget *getWidget();
    ~Game();
};

#endif // GAME_H
