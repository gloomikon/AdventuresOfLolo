#ifndef LOLO_H
#define LOLO_H

#include "personages.h"

class Lolo : public Personages
{
private:
    unsigned int    hp;
    unsigned int    shoots;
public:
    Lolo(unsigned int moveSpeed, unsigned int x, unsigned int y, unsigned int hp, unsigned int shoots);
};

#endif // LOLO_H
