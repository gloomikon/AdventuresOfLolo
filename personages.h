#ifndef PERSONAGES_H
# define PERSONAGES_H
# include "objects.h"
# include <QTimer>

struct Image
{
    QRect   rect;
    QPixmap pixmap;
};
struct Steps
{
    int stepUpDown;
    int stepLeftRight;
};
struct Shoot
{
    Coords  coords;
    Image   image;
    int     direction;
};

class Game;

class Personage : public Object
{
protected:
    bool        alive;
    bool        shoot;
    Steps       steps;
    int         direction;
    Shoot       *pShoot;
    QTimer      *timer;
    Image       pImage;
private:
public:

    Personage(bool shootable, int x, int y, int direction, std::string imgName);
    virtual void drawSelf(Widget *w) override;
    virtual void doAction();
    virtual void setImgName(std::string imgName) override final;
    virtual ~Personage() override;

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
    virtual void            kill(Game*);
    void            reincarnate();
};

#endif // PERSONAGES_H
