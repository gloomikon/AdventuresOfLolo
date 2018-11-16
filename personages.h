#ifndef PERSONAGES_H
#define PERSONAGES_H

#include "objects.h"

class Personages : public Objects
{
private:
protected:
public:
    unsigned int    x;
    unsigned int    y;
    unsigned int    stepUpDown;
    unsigned int    stepLeftRight;
    unsigned int    direction;

    Personages(bool shootable, unsigned int x, unsigned int y, unsigned int direction);
};

#endif // PERSONAGES_H
