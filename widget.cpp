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


Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setFixedSize(WIDTH*128,HEIGHT*128);
    this->setAttribute(Qt::WA_OpaquePaintEvent);
    this->setWindowTitle("Adventures of Lolo by KOLUMBIA");
    this->game = new Game("level1.txt");
    this->game->getLolo()->setTimer(new QTimer(this));
    connect(this->game->getLolo()->getTimer(), SIGNAL(timeout()), this, SLOT(shooting()));
    this->timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(moving()));
}

Game *Widget::getGame()
{
    return this->game;
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
    QPainter painter(this);
    painter.drawPixmap(this->game->getLolo()->getRect(), this->game->getLolo()->getPixmap());
}
void Widget::drawObjects()
{
    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
        {
            if (this->game->getMap()[i * WIDTH + j].typeOfSthElse == 'b')
            {
                this->drawCell(j,i);
            }
        }
}

void Widget::drawShoots()
{
    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
        {
            if (dynamic_cast<Personages*>(this->game->getMap()[i * WIDTH + j].ptr) &&
                    dynamic_cast<Personages*>(this->game->getMap()[i * WIDTH + j].ptr)->madeShoot())
            {
                Personages *p = dynamic_cast<Personages*>(this->game->getMap()[i * WIDTH + j].ptr);
                updShootBg(p);
                QPainter painter(this);
                painter.drawPixmap(static_cast<Personages*>(this->game->getMap()[i * WIDTH + j].ptr)->getSImage().rect,
                        static_cast<Personages*>(this->game->getMap()[i * WIDTH + j].ptr)->getSImage().pixmap);
                if (p->shooted(this->game, p->getShoot()->coords.x, p->getShoot()->coords.y))
                {
                    this->drawCell(p->getShoot()->coords.x, p->getShoot()->coords.y);
                    p->getTimer()->stop();
                    p->setBoolShoot(false);
                    delete p->getShoot();
                }
            }
        }
    update();
}

void Widget::updBg(Personages *p)
{
    for (int i = -1; i < 2; i++)
        for (int j = -1; j < 2; j++)
        {
            this->drawCell(p->getCoords().x + j, p->getCoords().y + i, p);
        }
}

void Widget::updShootBg(Personages *p)
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
    static bool drawed = false;
    if (!drawed)
    {
        this->drawSurface();
        drawed = true;
    }
    this->updBg(this->game->getLolo());
    this->drawObjects();
    this->drawLolo();
    this->drawShoots();
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
    /*if (this->game->map[this->game->lolo->y * WIDTH + this->game->lolo->x].typeOfSthElse == 'h')
    {
        if (!this->game->wasHeartPicked())
        {
            this->game->setHeartPickedStatus(true);
            this->game->lolo->shoots = 2;
        }
        delete static_cast<Heart*>(this->game->map[this->game->lolo->y * WIDTH + this->game->lolo->x].ptr);
        //qDebug() << this->game->map[this->game->lolo->y * WIDTH + this->game->lolo->x].ptr;
        this->game->map[this->game->lolo->y * WIDTH + this->game->lolo->x].isLoloHere = false;
        this->game->map[this->game->lolo->y * WIDTH + this->game->lolo->x].ptr = nullptr;
        this->game->map[this->game->lolo->y * WIDTH + this->game->lolo->x].typeOfSthElse = 'f';
        this->game->map[this->game->lolo->y * WIDTH + this->game->lolo->x].imgName = "";

    }*/
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

void Widget::drawCell(int x, int y, Personages *p)
{
    if (x < 0 || y < 0)
        return;
    QPainter painter(this);
    QRect rect;
    std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
    path += this->game->getMap()[y * WIDTH + x].typeOfSurface;
    path += ".png";
    QPixmap pixmap(path.c_str());
    rect.setCoords(x * 128,
                   y * 128,
                   (x + 1) * 128,
                   (y + 1) * 128);
    painter.drawPixmap(rect, pixmap);
    if (this->game->getMap()[y * WIDTH + x].ptr && this->game->getMap()[y * WIDTH + x].ptr != static_cast<Objects*>(p))
    {
        std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
        path += this->game->getMap()[y * WIDTH + x].ptr->getImgName();
        path += ".png";
        QPixmap pixmap(path.c_str());
        painter.drawPixmap(rect, pixmap);
    }
    if (p)
    {
        int *cx1 = new int;
        int *cx2 = new int;
        int *cy1 = new int;
        int *cy2 = new int;
                //qDebug() << "PERS" << p->getCoords().x << p->getCoords().y << "\nSHOOT" << p->getShoot()->coords.x << p->getShoot()->coords.y;
        QRect rect;
        QPainter painter(this);
        p->getRect().getCoords(cx1, cy1, cx2, cy2);
        rect.setCoords(*cx1, *cy1, *cx2, *cy2);
        painter.drawPixmap(rect, p->getPixmap());
        delete cx1;
        delete cx2;
        delete cy1;
        delete cy2;
    }
}
void Widget::keyPressEvent(QKeyEvent *e)
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
Widget::~Widget()
{
    delete ui;
}
