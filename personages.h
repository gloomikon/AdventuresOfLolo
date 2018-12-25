#ifndef PERSONAGES_H
# define PERSONAGES_H
# include "objects.h"
# include <QTimer>
# include <iostream>
# include <memory>

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
    Steps       *steps;
    int         direction;
    Shoot       *pShoot;
    QTimer      *timer = nullptr;
private:
public:
    Image     pImage;
    Personage(bool shootable, int x, int y, int direction, std::string imgName);
    virtual void drawSelf(Widget *w) override final;
    virtual void doAction();
    virtual void setImgName(std::string imgName) override final;
    virtual ~Personage() override;

    bool            isAlive();

    bool            madeShoot();

    void            shootUp();
    void            shootDown();
    void            shootRight();
    void            shootLeft();


    Steps*           getSteps();
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
    virtual void            kill();
    void            reincarnate();
    static Personage *makePersonage(std::string choice, int x, int y);
};

#endif // PERSONAGES_H
