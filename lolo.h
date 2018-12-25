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
    int     getShoots();
    void    setShoots(int shoots);
    int     getHeartsPicked();
    void    setHeartsPicked(int hearts);
    void    suicide(Game *game);
};

#endif // LOLO_H
