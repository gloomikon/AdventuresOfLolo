#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "lolo.h"
#include "personages.h"

class Game
{
private:
    struct  cell
    {
        Objects     *ptr;
        char        typeOfSurface;
        char        typeOfSthElse;
        std::string imgName;
    };

public:
    unsigned int    height;
    unsigned int    width;
    cell            *map;
    Lolo            *lolo;

    bool            canMoveLeft(Personages *p);
    bool            canMoveRight(Personages *p);
    bool            canMoveUp(Personages *p);
    bool            canMoveDown(Personages *p);

    Game(std::string fileName);
    ~Game();
};

#endif // GAME_H
