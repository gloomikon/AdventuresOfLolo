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
        bool        isLoloHere = false;
        char        typeOfSurface;
        char        typeOfSthElse;
        std::string imgName;
    };

public:
    cell    *map;
    Lolo    *lolo;
    int     lives;
    bool    heartPicked;

    bool            wasHeartPicked();
    void            setHeartPickedStatus(bool picked);

    Game(std::string fileName);
    ~Game();
};

#endif // GAME_H
