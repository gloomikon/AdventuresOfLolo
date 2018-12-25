#include "widget.h"
#include "ui_widget.h"
#include "game.h"
#include "heart.h"

#include <iostream>
#include <fstream>
#include <QMessageBox>
#include <QPainter>
#include <cmath>
#include <QKeyEvent>
#include <QTimer>
#include <QThread>
#include <QDebug>

void drawMap(Game *game)
{
    for (int i = 3; i < 5; i++)
    {
        for (int j = 1; j < 3; j++)
            qDebug() << i << j << game->getMap()[i * WIDTH + j].perPtr;
        qDebug() << "\n";
    }
}
Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setFixedSize(WIDTH*SIZE,HEIGHT*SIZE);
    this->setAttribute(Qt::WA_OpaquePaintEvent);
    this->setWindowTitle("Adventures of Lolo by KOLUMBIA");
    Game::Instance();
    Game::Instance().setWidget(this);
    connectTimers();
    this->timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(moving()));
    QTimer *actionTimer = new QTimer(this);
    connect(actionTimer, SIGNAL(timeout()), this, SLOT(acting()));
    actionTimer->start(20);
}


void Widget::drawSurface()
{
    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
        {
            this->drawCell(j,i);
        }
}
void Widget::drawLolo()
{
    Game::Instance().getLolo()->drawSelf(this);
}

void Widget::connectTimers()
{
    for (int i = 0; i < WIDTH * HEIGHT; i++)
        if (Game::Instance().getMap()[i].perPtr)
        {
            Game::Instance().getMap()[i].perPtr->setTimer(new QTimer(this));
            connect(Game::Instance().getMap()[i].perPtr->getTimer(), SIGNAL(timeout()), this, SLOT(shooting()));
        }
}

void Widget::drawObjects()
{
    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
        {
            if (Game::Instance().getMap()[i * WIDTH + j].perPtr && !dynamic_cast<Lolo*>(Game::Instance().getMap()[i * WIDTH + j].perPtr))
            {
                if (Game::Instance().getMap()[i * WIDTH + j].perPtr->getSteps()->stepLeftRight == 9)
                    this->drawCell(j-1,i);
                if (Game::Instance().getMap()[i * WIDTH + j].perPtr->getSteps()->stepLeftRight == 3)
                    this->drawCell(j+1,i);
                if (Game::Instance().getMap()[i * WIDTH + j].perPtr->getSteps()->stepUpDown == 12)
                    this->drawCell(j,i-1);
                if (Game::Instance().getMap()[i * WIDTH + j].perPtr->getSteps()->stepUpDown == 6)
                    this->drawCell(j,i+1);
                                this->drawCell(j,i);
            }
            if (Game::Instance().getMap()[i * WIDTH + j].objPtr == Game::Instance().getChest())
                this->drawCell(j,i);
        }
}

void Widget::drawShoots()
{
    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
        {
            if (Game::Instance().getMap()[i * WIDTH + j].perPtr && Game::Instance().getMap()[i * WIDTH + j].perPtr->madeShoot())
            {
                updShootBg(Game::Instance().getMap()[i * WIDTH + j].perPtr);
                QPainter painter(this);
                painter.drawPixmap(Game::Instance().getMap()[i * WIDTH + j].perPtr->getSImage().rect,
                        Game::Instance().getMap()[i * WIDTH + j].perPtr->getSImage().pixmap);
                if (Game::Instance().shooted(Game::Instance().getMap()[i * WIDTH + j].perPtr,
                                                                        Game::Instance().getMap()[i * WIDTH + j].perPtr->getShoot()->coords.x,
                                                                        Game::Instance().getMap()[i * WIDTH + j].perPtr->getShoot()->coords.y))
                {
                    this->drawCell(Game::Instance().getMap()[i * WIDTH + j].perPtr->getShoot()->coords.x, Game::Instance().getMap()[i * WIDTH + j].perPtr->getShoot()->coords.y);
                    Game::Instance().getMap()[i * WIDTH + j].perPtr->getTimer()->stop();
                    Game::Instance().getMap()[i * WIDTH + j].perPtr->setBoolShoot(false);
                    if (Game::Instance().shooted(Game::Instance().getMap()[i * WIDTH + j].perPtr,
                                                                            Game::Instance().getMap()[i * WIDTH + j].perPtr->getShoot()->coords.x,
                                                                            Game::Instance().getMap()[i * WIDTH + j].perPtr->getShoot()->coords.y) == 2)
                    {

                        Game::Instance().getMap()[Game::Instance().getMap()[i * WIDTH + j].perPtr->getShoot()->coords.y * WIDTH + Game::Instance().getMap()[i * WIDTH + j].perPtr->getShoot()->coords.x].perPtr->kill();
                    }


                        delete Game::Instance().getMap()[i * WIDTH + j].perPtr->getShoot();

                }
            }
        }
    update();
}

void Widget::updBg(Personage *p)
{
    for (int i = -1; i < 2; i++)
        for (int j = -1; j < 2; j++)
        {
            this->drawCell(p->getCoords()->x + j, p->getCoords()->y + i, p);
        }
}

void Widget::updShootBg(Personage *p)
{
    this->drawCell(p->getShoot()->coords.x, p->getShoot()->coords.y);
    this->drawCell(p->getCoords()->x, p->getCoords()->y, p);
}
void Widget::paintEvent(QPaintEvent *)
{
    if (Game::Instance().isActive())
    {
       if (Game::Instance().getFirstDraw())
        {
            this->drawSurface();
            Game::Instance().setFirstDraw(false);
        }
        this->drawObjects();
        this->updBg(Game::Instance().getLolo());
        this->drawLolo();
        this->drawShoots();
    }
}

void Widget::moving()
{
    //Down
    if (Game::Instance().getLolo()->getDirection() == 6)
    {
        Game::Instance().moveDown(Game::Instance().getLolo(), this->timer);
    }
    //Up
    else if (Game::Instance().getLolo()->getDirection() == 12)
    {
        Game::Instance().moveUp(Game::Instance().getLolo(), this->timer);
    }
    //Left
    else if (Game::Instance().getLolo()->getDirection() == 9)
    {
        Game::Instance().moveLeft(Game::Instance().getLolo(), this->timer);
    }
    //Right
    else if (Game::Instance().getLolo()->getDirection() == 3)
    {
        Game::Instance().moveRight(Game::Instance().getLolo(), this->timer);
    }
    Game::Instance().checkPickUp();

    //drawMap(this->game);
    update();
}

void Widget::shooting()
{
    //Up
    if (Game::Instance().getLolo()->getShoot()->direction == 12)
    {
        Game::Instance().getLolo()->shootUp();
    }
    //Down
    else if (Game::Instance().getLolo()->getShoot()->direction == 6)
    {
        Game::Instance().getLolo()->shootDown();
    }
    //Right
    else if (Game::Instance().getLolo()->getShoot()->direction == 3)
    {
        Game::Instance().getLolo()->shootRight();
    }
    //Left
    else if (Game::Instance().getLolo()->getShoot()->direction == 9)
    {
        Game::Instance().getLolo()->shootLeft();
    }
}

void Widget::acting()
{
    /*for (auto c = std::begin(*Game::Instance().getSharedPtrMap()); c!=std::end(*Game::Instance().getSharedPtrMap()); ++c)
        if (c->perPtr)
            c->perPtr->doAction();*/
    /*for (auto c : *Game::Instance().getClassMap())
        if (c.perPtr)
            c.perPtr->doAction();*/
    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
            if (Game::Instance().getMap()[i * HEIGHT + j].perPtr)
                Game::Instance().getMap()[i * HEIGHT + j].perPtr->doAction();

}

void Widget::drawCell(int x, int y, Personage *p)
{
    if (x < 0 || y < 0 || x > WIDTH - 1 || y > WIDTH - 1)
        return;
    QPainter painter(this);
    QRect rect;
    QPixmap pixmap("C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/f.png");
    rect.setCoords(x * SIZE,
                   y * SIZE,
                   (x + 1) * SIZE,
                   (y + 1) * SIZE);
    painter.drawPixmap(rect, pixmap);
    if (Game::Instance().getMap()[y * WIDTH + x].objPtr)
    {
        Game::Instance().getMap()[y * WIDTH + x].objPtr->drawSelf(this);
    }
    if (Game::Instance().getMap()[y * WIDTH + x].perPtr && Game::Instance().getMap()[y * WIDTH + x].perPtr != p)
    {
        Game::Instance().getMap()[y * WIDTH + x].perPtr->drawSelf(this);
    }
    if (p)
    {
        p->drawSelf(this);
    }
}
void Widget::keyPressEvent(QKeyEvent *e)
{
    if(Game::Instance().isActive() && Game::Instance().getLolo()->isAlive())
    {
        if (e->key() == Qt::Key_S || e->key() == Qt::Key_Down)
        {
            if (!this->timer->isActive())
            {
                Game::Instance().getLolo()->setImgName("lolo");
                Game::Instance().getLolo()->setDirection(6);
                this->timer->start(10);
            }
        }
        else if (e->key() == Qt::Key_W || e->key() == Qt::Key_Up)
        {
            if (!this->timer->isActive())
            {
                Game::Instance().getLolo()->setImgName("loloup");
                Game::Instance().getLolo()->setDirection(12);
                this->timer->start(10);
            }
        }
        else if (e->key() == Qt::Key_A || e->key() == Qt::Key_Left)
        {
            if (!this->timer->isActive())
            {
                Game::Instance().getLolo()->setImgName("lololeft");
                Game::Instance().getLolo()->setDirection(9);
                this->timer->start(10);
            }
        }
        else if (e->key() == Qt::Key_D || e->key() == Qt::Key_Right)
        {
            if (!this->timer->isActive())
            {
                Game::Instance().getLolo()->setImgName("loloright");
                Game::Instance().getLolo()->setDirection(3);
                this->timer->start(10);
            }
        }
        else if (e->key() == Qt::Key_Space)
        {
            if (!Game::Instance().getLolo()->getTimer()->isActive() && Game::Instance().getLolo()->getShoots() > 0)
            {
                Game::Instance().getLolo()->setShoots(Game::Instance().getLolo()->getShoots() - 1);
                Game::Instance().getLolo()->createShoot();
                Game::Instance().getLolo()->setShootDirection(Game::Instance().getLolo()->getDirection());
                Game::Instance().getLolo()->getTimer()->start(10);
            }
        }
        else if (e->key() == Qt::Key_Shift)
        {
            Game::Instance().getLolo()->suicide(&Game::Instance());
        }
    }
}
Widget::~Widget()
{
    delete ui;
}
