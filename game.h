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

class Game
{
private:

    int     heartsToPick;
    int     lives;
    int     level;
    bool    active;
    bool    firstDraw;
    std::shared_ptr<cell[]> map;
    Lolo    *lolo;
    Chest   *chest;
    Object *exit;
    Widget  *w;

    Game();
    ~Game();
    Game(Game const&) = delete;
    Game& operator=(Game const&) = delete;
public:

    static Game &Instance();
    void readFromFile(std::string fileName);
    void restartLevel();
    void nextLevel();

    std::shared_ptr<cell[]>    getMap();
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
    int             canMoveLeft(Personage *p, int n = 0);
    int             canMoveRight(Personage *p, int n = 0);
    int             canMoveUp(Personage *p, int n = 0);
    int             canMoveDown(Personage *p, int n = 0);

    void            moveLeft(Personage *p, QTimer *timer);
    void            moveRight(Personage *p, QTimer *timer);
    void            moveUp(Personage *p, QTimer *timer);
    void            moveDown(Personage *p, QTimer *timer);
    void            checkPickUp();

    int             shooted(Personage *p, int x, int y);
    void   setWidget(Widget *w);
    Widget *getWidget();
};

#endif // GAME_H
