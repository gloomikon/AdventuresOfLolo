#ifndef CHEST_H
#define CHEST_H

#include "objects.h"

class Chest : public Objects
{
private:
    bool    opened;
    bool    jewellery;
public:
    Chest(std::string imgName);
    bool    isOpened();
    bool    hasJewellery();
    void    open();
    void    finish();
};

#endif // CHEST_H
