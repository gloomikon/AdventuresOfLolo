#ifndef CHEST_H
#define CHEST_H

#include "objects.h"

class Chest : public Objects
{
private:
    bool    opened;
public:
    Chest(std::string imgName);
    bool    isOpened();
};

#endif // CHEST_H