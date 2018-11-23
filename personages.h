#ifndef PERSONAGES_H
# define PERSONAGES_H
# include "objects.h"

class Game;

class Personages : public Objects
{
private:
protected:
public:
    int    x;
    int    y;
    int    stepUpDown;
    int    stepLeftRight;
    int    direction;
    bool    action(Game *game);

    Personages(bool shootable, int x, int y, int direction);
    bool            canMoveLeft(Game *map);
    bool            canMoveRight(Game *map);
    bool            canMoveUp(Game *map);
    bool            canMoveDown(Game *map);
};

#endif // PERSONAGES_H
