#ifndef CHEST_H
#define CHEST_H

#include "objects.h"

class Chest : public Object
{
private:
    bool    opened;
    bool    jewellery;
public:
    Chest(std::string imgName, int x, int y);
    bool    isOpened();
    bool    hasJewellery();
    void    open();
    void    finish();
};

#endif // CHEST_H
