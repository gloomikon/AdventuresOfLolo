#ifndef HEART_H
#define HEART_H

#include "objects.h"

class Heart : public Objects
{
private:
    int    giveAmmo;
public:
    Heart(bool shootable, bool walkable, int giveAmmo);
};

#endif // HEART_H
