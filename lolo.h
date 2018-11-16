#ifndef LOLO_H
#define LOLO_H

#include "personages.h"

class Lolo : public Personages
{
private:
    unsigned int    shoots;
public:
    Lolo(unsigned int x, unsigned int y, unsigned int direction);
};

#endif // LOLO_H
