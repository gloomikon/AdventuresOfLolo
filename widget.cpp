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
    Game::Instance(this);
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
    Game::Instance(this).getLolo()->drawSelf(this);
}

void Widget::connectTimers()
{
    for (int i = 0; i < WIDTH * HEIGHT; i++)
        if (Game::Instance(this).getMap()[i].perPtr)
        {
            Game::Instance(this).getMap()[i].perPtr->setTimer(new QTimer(this));
            connect(Game::Instance(this).getMap()[i].perPtr->getTimer(), SIGNAL(timeout()), this, SLOT(shooting()));
        }
}

void Widget::drawObjects()
{
    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
        {
            if (Game::Instance(this).getMap()[i * WIDTH + j].perPtr && !dynamic_cast<Lolo*>(Game::Instance(this).getMap()[i * WIDTH + j].perPtr))
            {
                if (Game::Instance(this).getMap()[i * WIDTH + j].perPtr->getSteps()->stepLeftRight == 9)
                    this->drawCell(j-1,i);
                if (Game::Instance(this).getMap()[i * WIDTH + j].perPtr->getSteps()->stepLeftRight == 3)
                    this->drawCell(j+1,i);
                if (Game::Instance(this).getMap()[i * WIDTH + j].perPtr->getSteps()->stepUpDown == 12)
                    this->drawCell(j,i-1);
                if (Game::Instance(this).getMap()[i * WIDTH + j].perPtr->getSteps()->stepUpDown == 6)
                    this->drawCell(j,i+1);
                                this->drawCell(j,i);
            }
            if (Game::Instance(this).getMap()[i * WIDTH + j].objPtr == Game::Instance(this).getChest())
                this->drawCell(j,i);
        }
}

void Widget::drawShoots()
{
    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
        {
            if (Game::Instance(this).getMap()[i * WIDTH + j].perPtr && Game::Instance(this).getMap()[i * WIDTH + j].perPtr->madeShoot())
            {
                updShootBg(Game::Instance(this).getMap()[i * WIDTH + j].perPtr);
                QPainter painter(this);
                painter.drawPixmap(Game::Instance(this).getMap()[i * WIDTH + j].perPtr->getSImage().rect,
                        Game::Instance(this).getMap()[i * WIDTH + j].perPtr->getSImage().pixmap);
                if (Game::Instance(this).shooted(Game::Instance(this).getMap()[i * WIDTH + j].perPtr,
                                                                        Game::Instance(this).getMap()[i * WIDTH + j].perPtr->getShoot()->coords.x,
                                                                        Game::Instance(this).getMap()[i * WIDTH + j].perPtr->getShoot()->coords.y))
                {
                    this->drawCell(Game::Instance(this).getMap()[i * WIDTH + j].perPtr->getShoot()->coords.x, Game::Instance(this).getMap()[i * WIDTH + j].perPtr->getShoot()->coords.y);
                    Game::Instance(this).getMap()[i * WIDTH + j].perPtr->getTimer()->stop();
                    Game::Instance(this).getMap()[i * WIDTH + j].perPtr->setBoolShoot(false);
                    if (Game::Instance(this).shooted(Game::Instance(this).getMap()[i * WIDTH + j].perPtr,
                                                                            Game::Instance(this).getMap()[i * WIDTH + j].perPtr->getShoot()->coords.x,
                                                                            Game::Instance(this).getMap()[i * WIDTH + j].perPtr->getShoot()->coords.y) == 2)
                    {

                        Game::Instance(this).getMap()[Game::Instance(this).getMap()[i * WIDTH + j].perPtr->getShoot()->coords.y * WIDTH + Game::Instance(this).getMap()[i * WIDTH + j].perPtr->getShoot()->coords.x].perPtr->kill();
                    }


                        delete Game::Instance(this).getMap()[i * WIDTH + j].perPtr->getShoot();

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
    if (Game::Instance(this).isActive())
    {
       if (Game::Instance(this).getFirstDraw())
        {
            this->drawSurface();
            Game::Instance(this).setFirstDraw(false);
        }
        this->drawObjects();
        this->updBg(Game::Instance(this).getLolo());
        this->drawLolo();
        this->drawShoots();
    }
}

void Widget::moving()
{
    //Down
    if (Game::Instance(this).getLolo()->getDirection() == 6)
    {
        Game::Instance(this).moveDown(Game::Instance(this).getLolo(), this->timer);
    }
    //Up
    else if (Game::Instance(this).getLolo()->getDirection() == 12)
    {
        Game::Instance(this).moveUp(Game::Instance(this).getLolo(), this->timer);
    }
    //Left
    else if (Game::Instance(this).getLolo()->getDirection() == 9)
    {
        Game::Instance(this).moveLeft(Game::Instance(this).getLolo(), this->timer);
    }
    //Right
    else if (Game::Instance(this).getLolo()->getDirection() == 3)
    {
        Game::Instance(this).moveRight(Game::Instance(this).getLolo(), this->timer);
    }
    Game::Instance(this).checkPickUp();

    //drawMap(this->game);
    update();
}

void Widget::shooting()
{
    //Up
    if (Game::Instance(this).getLolo()->getShoot()->direction == 12)
    {
        Game::Instance(this).getLolo()->shootUp();
    }
    //Down
    else if (Game::Instance(this).getLolo()->getShoot()->direction == 6)
    {
        Game::Instance(this).getLolo()->shootDown();
    }
    //Right
    else if (Game::Instance(this).getLolo()->getShoot()->direction == 3)
    {
        Game::Instance(this).getLolo()->shootRight();
    }
    //Left
    else if (Game::Instance(this).getLolo()->getShoot()->direction == 9)
    {
        Game::Instance(this).getLolo()->shootLeft();
    }
}

void Widget::acting()
{
    /*for (auto c = std::begin(*Game::Instance(this).getSharedPtrMap()); c!=std::end(*Game::Instance(this).getSharedPtrMap()); ++c)
        if (c->perPtr)
            c->perPtr->doAction();*/
    /*for (auto c : *Game::Instance(this).getClassMap())
        if (c.perPtr)
            c.perPtr->doAction();*/
    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
            if (Game::Instance(this).getMap()[i * HEIGHT + j].perPtr)
                Game::Instance(this).getMap()[i * HEIGHT + j].perPtr->doAction();

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
    if (Game::Instance(this).getMap()[y * WIDTH + x].objPtr)
    {
        Game::Instance(this).getMap()[y * WIDTH + x].objPtr->drawSelf(this);
    }
    if (Game::Instance(this).getMap()[y * WIDTH + x].perPtr && Game::Instance(this).getMap()[y * WIDTH + x].perPtr != p)
    {
        Game::Instance(this).getMap()[y * WIDTH + x].perPtr->drawSelf(this);
    }
    if (p)
    {
        p->drawSelf(this);
    }
}
void Widget::keyPressEvent(QKeyEvent *e)
{
    if(Game::Instance(this).isActive() && Game::Instance(this).getLolo()->isAlive())
    {
        if (e->key() == Qt::Key_S || e->key() == Qt::Key_Down)
        {
            if (!this->timer->isActive())
            {
                Game::Instance(this).getLolo()->setImgName("lolo");
                Game::Instance(this).getLolo()->setDirection(6);
                this->timer->start(10);
            }
        }
        else if (e->key() == Qt::Key_W || e->key() == Qt::Key_Up)
        {
            if (!this->timer->isActive())
            {
                Game::Instance(this).getLolo()->setImgName("loloup");
                Game::Instance(this).getLolo()->setDirection(12);
                this->timer->start(10);
            }
        }
        else if (e->key() == Qt::Key_A || e->key() == Qt::Key_Left)
        {
            if (!this->timer->isActive())
            {
                Game::Instance(this).getLolo()->setImgName("lololeft");
                Game::Instance(this).getLolo()->setDirection(9);
                this->timer->start(10);
            }
        }
        else if (e->key() == Qt::Key_D || e->key() == Qt::Key_Right)
        {
            if (!this->timer->isActive())
            {
                Game::Instance(this).getLolo()->setImgName("loloright");
                Game::Instance(this).getLolo()->setDirection(3);
                this->timer->start(10);
            }
        }
        else if (e->key() == Qt::Key_Space)
        {
            if (!Game::Instance(this).getLolo()->getTimer()->isActive() && Game::Instance(this).getLolo()->getShoots() > 0)
            {
                Game::Instance(this).getLolo()->setShoots(Game::Instance(this).getLolo()->getShoots() - 1);
                Game::Instance(this).getLolo()->createShoot();
                Game::Instance(this).getLolo()->setShootDirection(Game::Instance(this).getLolo()->getDirection());
                Game::Instance(this).getLolo()->getTimer()->start(10);
            }
        }
        else if (e->key() == Qt::Key_Shift)
        {
            Game::Instance(this).getLolo()->suicide(&Game::Instance(this));
        }
    }
}
Widget::~Widget()
{
    delete ui;
}
