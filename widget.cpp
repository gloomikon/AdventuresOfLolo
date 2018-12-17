#include "widget.h"
#include "ui_widget.h"
#include "game.h"
#include "heart.h"

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
    for (int i = 5; i < 10; i++)
    {
        for (int j = 4; j < 10; j++)
            qDebug() << i << j << game->getMap()[i * WIDTH + j].objPtr << " , " << game->getMap()[i * WIDTH + j].perPtr;
        qDebug() << "\n";
    }
}
Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setFixedSize(WIDTH*SIZE,HEIGHT*SIZE);
    this->setAttribute(Qt::WA_OpaquePaintEvent);
    this->setWindowTitle("Adventures of Lolo by KOLUMBIA");
    this->game = new Game(this);
    connectTimers();
    this->timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(moving()));
    QTimer *actionTimer = new QTimer(this);
    connect(actionTimer, SIGNAL(timeout()), this, SLOT(acting()));
    actionTimer->start(1000);
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
    this->game->getLolo()->drawSelf(this);
}

void Widget::connectTimers()
{
    for (int i = 0; i < WIDTH * HEIGHT; i++)
        if (this->game->getMap()[i].perPtr)
        {
            this->game->getMap()[i].perPtr->setTimer(new QTimer(this));
            connect(this->game->getMap()[i].perPtr->getTimer(), SIGNAL(timeout()), this, SLOT(shooting()));
        }
}
void Widget::drawObjects()
{
    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
        {
            if (this->game->getMap()[i * WIDTH + j].perPtr && !dynamic_cast<Lolo*>(this->game->getMap()[i * WIDTH + j].perPtr))
            {
                if (this->game->getMap()[i * WIDTH + j].perPtr->getSteps().stepLeftRight == 9)
                    this->drawCell(j-1,i);
                if (this->game->getMap()[i * WIDTH + j].perPtr->getSteps().stepLeftRight == 3)
                    this->drawCell(j+1,i);
                if (this->game->getMap()[i * WIDTH + j].perPtr->getSteps().stepUpDown == 12)
                    this->drawCell(j,i-1);
                if (this->game->getMap()[i * WIDTH + j].perPtr->getSteps().stepUpDown == 6)
                    this->drawCell(j,i+1);
                                this->drawCell(j,i);
            }
            if (this->game->getMap()[i * WIDTH + j].objPtr == this->game->getChest())
                this->drawCell(j,i);
        }
}

void Widget::drawShoots()
{
    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
        {
            if (this->game->getMap()[i * WIDTH + j].perPtr && this->game->getMap()[i * WIDTH + j].perPtr->madeShoot())
            {
                updShootBg(this->game->getMap()[i * WIDTH + j].perPtr);
                QPainter painter(this);
                painter.drawPixmap(this->game->getMap()[i * WIDTH + j].perPtr->getSImage().rect,
                        this->game->getMap()[i * WIDTH + j].perPtr->getSImage().pixmap);
                if (this->game->getMap()[i * WIDTH + j].perPtr->shooted(this->game,
                                                                        this->game->getMap()[i * WIDTH + j].perPtr->getShoot()->coords.x,
                                                                        this->game->getMap()[i * WIDTH + j].perPtr->getShoot()->coords.y))
                {
                    if (this->game->getMap()[i * WIDTH + j].perPtr->shooted(this->game,
                                                                            this->game->getMap()[i * WIDTH + j].perPtr->getShoot()->coords.x,
                                                                            this->game->getMap()[i * WIDTH + j].perPtr->getShoot()->coords.y) == 2)
                        this->game->getMap()[this->game->getMap()[i * WIDTH + j].perPtr->getShoot()->coords.y * WIDTH + this->game->getMap()[i * WIDTH + j].perPtr->getShoot()->coords.x].perPtr->kill();
                    this->drawCell(this->game->getMap()[i * WIDTH + j].perPtr->getShoot()->coords.x,
                                   this->game->getMap()[i * WIDTH + j].perPtr->getShoot()->coords.y);
                    this->game->getMap()[i * WIDTH + j].perPtr->getTimer()->stop();
                    this->game->getMap()[i * WIDTH + j].perPtr->setBoolShoot(false);
                    delete this->game->getMap()[i * WIDTH + j].perPtr->getShoot();
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
            this->drawCell(p->getCoords().x + j, p->getCoords().y + i, p);
        }
}

void Widget::updShootBg(Personage *p)
{
    this->drawCell(p->getShoot()->coords.x, p->getShoot()->coords.y);
    drawCell(p->getCoords().x, p->getCoords().y, p);
    if (abs(p->getCoords().x - p->getShoot()->coords.x) <= 1 && abs(p->getCoords().y - p->getShoot()->coords.y) <= 1)
    {
        this->drawCell(p->getShoot()->coords.x, p->getShoot()->coords.y, p);
    }
}
void Widget::paintEvent(QPaintEvent *)
{
    if (this->game->isActive())
    {
        if (game->getFirstDraw())
        {
            this->drawSurface();
            game->setFirstDraw(false);
        }
        this->updBg(this->game->getLolo());
        this->drawObjects();
        this->drawLolo();
        this->drawShoots();
    }
}

void Widget::moving()
{
    //Down
    if (this->game->getLolo()->getDirection() == 6)
    {
        this->game->getLolo()->moveDown(this->game, this->timer);
    }
    //Up
    else if (this->game->getLolo()->getDirection() == 12)
    {
        this->game->getLolo()->moveUp(this->game, this->timer);
    }
    //Left
    else if (this->game->getLolo()->getDirection() == 9)
    {
        this->game->getLolo()->moveLeft(this->game, this->timer);
    }
    //Right
    else if (this->game->getLolo()->getDirection() == 3)
    {
        this->game->getLolo()->moveRight(this->game, this->timer);
    }
    this->game->getLolo()->checkPickUp(this->game);

    //drawMap(this->game);
    update();
}

void Widget::shooting()
{
    //Up
    if (this->game->getLolo()->getShoot()->direction == 12)
    {
        this->game->getLolo()->shootUp();
    }
    //Down
    else if (this->game->getLolo()->getShoot()->direction == 6)
    {
        this->game->getLolo()->shootDown();
    }
    //Right
    else if (this->game->getLolo()->getShoot()->direction == 3)
    {
        this->game->getLolo()->shootRight();
    }
    //Left
    else if (this->game->getLolo()->getShoot()->direction == 9)
    {
        this->game->getLolo()->shootLeft();
    }
}

void Widget::acting()
{
    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
            if (this->game->getMap()[i * HEIGHT + j].perPtr)
                this->game->getMap()[i * HEIGHT + j].perPtr->doAction();
}

void Widget::drawCell(int x, int y, Personage *p)
{
    if (x < 0 || y < 0)
        return;
    QPainter painter(this);
    QRect rect;
    QPixmap pixmap("C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/f.png");
    rect.setCoords(x * SIZE,
                   y * SIZE,
                   (x + 1) * SIZE,
                   (y + 1) * SIZE);
    painter.drawPixmap(rect, pixmap);
    if (this->game->getMap()[y * WIDTH + x].objPtr)
    {
        this->game->getMap()[y * WIDTH + x].objPtr->drawSelf(this);
    }
    if (this->game->getMap()[y * WIDTH + x].perPtr && this->game->getMap()[y * WIDTH + x].perPtr != p)
    {
        this->game->getMap()[y * WIDTH + x].perPtr->drawSelf(this);
    }
    if (p)
    {
        p->drawSelf(this);
    }
}
void Widget::keyPressEvent(QKeyEvent *e)
{
    if(this->game->isActive())
    {
        if (e->key() == Qt::Key_S || e->key() == Qt::Key_Down)
        {
            if (!this->timer->isActive())
            {
                this->game->getLolo()->setImgName("lolo");
                this->game->getLolo()->setDirection(6);
                this->timer->start(10);
            }
        }
        else if (e->key() == Qt::Key_W || e->key() == Qt::Key_Up)
        {
            if (!this->timer->isActive())
            {
                this->game->getLolo()->setImgName("loloup");
                this->game->getLolo()->setDirection(12);
                this->timer->start(10);
            }
        }
        else if (e->key() == Qt::Key_A || e->key() == Qt::Key_Left)
        {
            if (!this->timer->isActive())
            {
                this->game->getLolo()->setImgName("lololeft");
                this->game->getLolo()->setDirection(9);
                this->timer->start(10);
            }
        }
        else if (e->key() == Qt::Key_D || e->key() == Qt::Key_Right)
        {
            if (!this->timer->isActive())
            {
                this->game->getLolo()->setImgName("loloright");
                this->game->getLolo()->setDirection(3);
                this->timer->start(10);
            }
        }
        else if (e->key() == Qt::Key_Space)
        {
            if (!this->game->getLolo()->getTimer()->isActive())
            {
                this->game->getLolo()->createShoot();
                this->game->getLolo()->setShootDirection(this->game->getLolo()->getDirection());
                this->game->getLolo()->getTimer()->start(10);
            }
        }
    }
}
Widget::~Widget()
{
    delete ui;
}
