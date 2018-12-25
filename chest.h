#ifndef CHEST_H
#define CHEST_H

#include "objects.h"
class State;
class Chest : public Object
{
private:
    bool    opened;
    bool    jewellery;
    State*  current;
public:
    Chest(std::string imgName, int x, int y);
    bool    isOpened();
    bool    hasJewellery();
    void    perfomSth();
    void    setCurrentState(State *s);
};

#endif // CHEST_H
