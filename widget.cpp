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
    QPainter painter(this);
    QRect rect;

    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
        {
            rect.setCoords(j * 128,
                           i * 128,
                           (j + 1) * 128,
                           (i + 1) * 128);
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->game->getMap()[i * WIDTH + j].typeOfSurface;
            path += ".png";
            QPixmap pixmap(path.c_str());
            painter.drawPixmap(rect, pixmap);
            if (this->game->getMap()[i * WIDTH + j].ptr && this->game->getMap()[i * WIDTH + j].typeOfSthElse != 'b'
                     && this->game->getMap()[i * WIDTH + j].typeOfSthElse != 'l')
            {
                path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
                path += this->game->getMap()[i * WIDTH + j].ptr->getImgName();
                path += ".png";
                QPixmap pixmap(path.c_str());
                painter.drawPixmap(rect, pixmap);
            }
        }
}
void Widget::drawLolo()
{
    QPainter painter(this);
    painter.drawPixmap(this->game->getLolo()->getRect(), this->game->getLolo()->getPixmap());
}
void Widget::drawObjects()
{
    QPainter painter(this);
    QRect rect;

    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
        {
            if (this->game->getMap()[i * WIDTH + j].typeOfSthElse == 'b')
            {
                rect.setCoords(j * 128,
                               i * 128,
                               (j + 1) * 128,
                               (i + 1) * 128);
                std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
                path += this->game->getMap()[i * WIDTH + j].ptr->getImgName();
                path += ".png";
                QPixmap pixmap(path.c_str());
                painter.drawPixmap(rect, pixmap);
            }
        }
}

void Widget::drawShoots()
{
    QPainter painter(this);

    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
        {
            if (dynamic_cast<Personages*>(this->game->getMap()[i * WIDTH + j].ptr) &&
                    dynamic_cast<Personages*>(this->game->getMap()[i * WIDTH + j].ptr)->madeShoot())
            {
                painter.drawPixmap(static_cast<Personages*>(this->game->getMap()[i * WIDTH + j].ptr)->getSImage().rect,
                        static_cast<Personages*>(this->game->getMap()[i * WIDTH + j].ptr)->getSImage().pixmap);
            }
        }
    update();
}

void Widget::updBg(Personages *p)
{
    QPainter painter(this);
    QRect rect;
    for (int i = -1; i < 2; i++)
        for (int j = -1; j < 2; j++)
        {
            rect.setCoords((p->getCoords().x + i) * 128,
                           (p->getCoords().y + j) * 128,
                           (p->getCoords().x + i + 1) * 128,
                           (p->getCoords().y + j + 1) * 128);
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->game->getMap()[(p->getCoords().y + j) * WIDTH + p->getCoords().x + i].typeOfSurface;
            path += ".png";
            QPixmap pixmap(path.c_str());
            painter.drawPixmap(rect, pixmap);        

            if (this->game->getMap()[(p->getCoords().y + j) * WIDTH + p->getCoords().x + i].ptr &&
                    this->game->getMap()[(p->getCoords().y + j) * WIDTH + p->getCoords().x + i].ptr != p)
            {
                rect.setCoords((p->getCoords().x + i) * 128,
                               (p->getCoords().y + j) * 128,
                               (p->getCoords().x + i + 1) * 128,
                               (p->getCoords().y + j + 1) * 128);
                std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
                path += this->game->getMap()[(p->getCoords().y + j) * WIDTH + p->getCoords().x + i].ptr->getImgName();
                path += ".png";
                QPixmap pixmap(path.c_str());
                painter.drawPixmap(rect, pixmap);
            }
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
    else
    {
        this->updBg(this->game->getLolo());
    }
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
    if (this->game->getLolo()->getShootDirection() == 12)
    {
        this->game->getLolo()->shootUp(this->game);
    }
    //Down
    else if (this->game->getLolo()->getShootDirection() == 6)
    {
        this->game->getLolo()->shootDown(this->game);
    }
    //Right
    else if (this->game->getLolo()->getShootDirection() == 3)
    {
        this->game->getLolo()->shootRight(this->game);
    }
    //Left
    else if (this->game->getLolo()->getShootDirection() == 9)
    {
        this->game->getLolo()->shootLeft(this->game);
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
                this->game->getLolo()->setShootDirection(this->game->getLolo()->getDirection());
                this->game->getLolo()->getTimer()->start(10);
            }
        }
}
Widget::~Widget()
{
    delete ui;
}
