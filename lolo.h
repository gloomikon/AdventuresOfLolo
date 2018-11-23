#ifndef LOLO_H
# define LOLO_H

# include "personages.h"

class Lolo : public Personages
{
private:
    int    shoots;
public:
    Lolo(int x, int y, int direction, QRect rect, QPixmap pixmap, std::string imgName);
    void    makeWalkable();
};

#endif // LOLO_H
