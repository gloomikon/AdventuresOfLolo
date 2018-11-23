#ifndef GAME_H
# define GAME_H
# include <iostream>
# include "chest.h"
# include "heart.h"
# include "lolo.h"
class Game
{
private:
    struct  cell
    {
        Objects     *ptr;
        bool        isSome1Here = false;
        char        typeOfSurface;
        char        typeOfSthElse;
    };
    bool    heartPicked;
    int     lives;
public:
    cell    *map;
    Lolo    *lolo;

    bool            wasHeartPicked();
    void            setHeartPickedStatus(bool picked);

    Game(std::string fileName);
    ~Game();
};

#endif // GAME_H
