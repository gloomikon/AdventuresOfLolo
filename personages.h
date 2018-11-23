#ifndef PERSONAGES_H
# define PERSONAGES_H
# include "objects.h"
# include <QRect>
# include <QPixmap>
# include <QTimer>

class Game;

class Personages : public Objects
{
private:
    struct Coords
    {
        int x;
        int y;
    };

    struct Steps
    {
        int stepUpDown;
        int stepLeftRight;
    };

    Coords      coords;
    Steps       steps;
    int         direction;
    QRect       rect;
    QPixmap     pixmap;

protected:
public:


    Personages(bool shootable, int x, int y, int direction, QRect rect, QPixmap pixmap, std::string imgName);

    bool            canMoveLeft(Game *game);
    bool            canMoveRight(Game *game);
    bool            canMoveUp(Game *game);
    bool            canMoveDown(Game *game);

    void            moveLeft(Game *game, QTimer *timer);
    void            moveRight(Game *game, QTimer *timer);
    void            moveUp(Game *game, QTimer *timer);
    void            moveDown(Game *game, QTimer *timer);


    Coords          getCoords();
    void            setCoords(int x, int y);

    Steps           getSteps();
    void            setSteps(int stepUpDown, int stepLeftRight);

    int             getDirection();
    void            setDirection(int direction);

    QRect           getRect();

    QPixmap         getPixmap();

};

#endif // PERSONAGES_H
