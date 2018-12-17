#ifndef LOLO_H
# define LOLO_H

# include "personages.h"

class Lolo : public Personage
{
private:
    int    shoots;
    int    heartPicked;
public:
    Lolo(int x, int y, int direction, std::string imgName);
    void    checkPickUp(Game *game);
};

#endif // LOLO_H
