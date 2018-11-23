#ifndef LOLO_H
# define LOLO_H

# include "personages.h"

class Lolo : public Personages
{
private:
public:
    int    shoots;
    Lolo(int x, int y, int direction);
    void    makeWalkable();
};

#endif // LOLO_H
