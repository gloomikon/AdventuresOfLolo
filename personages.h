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
    struct Image
    {
        QRect   rect;
        QPixmap pixmap;
    };
    struct Shoot
    {
        Coords  coords;
        Image   image;
        int     direction;
    };

    bool        alive;
    bool        shoot;
    Coords      coords;
    Steps       steps;
    int         direction;
    Image       pImage;
    Shoot       *pShoot;
    QTimer      *timer;

protected:
public:


    Personages(bool shootable, int x, int y, int direction, QRect rect, QPixmap pixmap, std::string imgName);

    bool            isAlive();

    bool            madeShoot();

    int             canMoveLeft(Game *game, int n = 0);
    int             canMoveRight(Game *game, int n = 0);
    int             canMoveUp(Game *game, int n = 0);
    int             canMoveDown(Game *game, int n = 0);

    void            moveLeft(Game *game, QTimer *timer);
    void            moveRight(Game *game, QTimer *timer);
    void            moveUp(Game *game, QTimer *timer);
    void            moveDown(Game *game, QTimer *timer);

    int             shooted(Game *game, int x, int y);

    void            shootUp();
    void            shootDown();
    void            shootRight();
    void            shootLeft();


    Coords          getCoords();
    void            setCoords(int x, int y);

    Steps           getSteps();
    void            setSteps(int stepUpDown, int stepLeftRight);

    int             getDirection();
    void            setDirection(int direction);

    void            setShootDirection(int shootDirection);

    QRect           getRect();

    QPixmap         getPixmap();

    QTimer          *getTimer();
    void            setTimer(QTimer *timer);

    Image           getSImage();

    void            createShoot();
    Shoot           *getShoot();

    void            setBoolShoot(bool shoot);
    void            kill();
    void            reincarnate();
};

#endif // PERSONAGES_H
