#ifndef HEART_H
#define HEART_H

#include "objects.h"

class Heart : public Objects
{
private:
    unsigned int    giveAmmo;
public:
    Heart(bool shootable, bool walkable, unsigned int giveAmmo);
};

#endif // HEART_H
