#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "lolo.h"

class Game
{
private:
    struct  cell
    {
        void        *ptr;
        char        typeOfSurface;
        char        typeOfSthElse;
        std::string imgName;
    };

public:
    unsigned int    height;
    unsigned int    width;
    cell            *map;
    Lolo            *lolo;

    Game(std::string fileName);
    Game::cell   *returnMap();
    ~Game();
};

#endif // GAME_H
