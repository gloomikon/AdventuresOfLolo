#ifndef PERSONAGES_H
#define PERSONAGES_H

#include "objects.h"

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

    Personages(bool shootable, int x, int y, int direction);
};

#endif // PERSONAGES_H
