#ifndef HEART_H
#define HEART_H

#include "objects.h"

class Heart : public Objects
{
private:
public:
    Heart(bool shootable, bool walkable, std::string imgName);
};

#endif // HEART_H
