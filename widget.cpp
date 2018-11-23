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
    this->timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(ex_code()));
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
            path += this->game->map[i * WIDTH + j].typeOfSurface;
            path += ".png";
            QPixmap pixmap(path.c_str());
            painter.drawPixmap(rect, pixmap);
            if (this->game->map[i * WIDTH + j].ptr && this->game->map[i * WIDTH + j].typeOfSthElse != 'b'
                     && this->game->map[i * WIDTH + j].typeOfSthElse != 'l')
            {
                path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
                path += this->game->map[i * WIDTH + j].ptr->getImgName();
                path += ".png";
                QPixmap pixmap(path.c_str());
                painter.drawPixmap(rect, pixmap);
            }
        }
}
void Widget::drawLolo()
{
    QPainter painter(this);
    painter.drawPixmap(this->game->lolo->getRect(), this->game->lolo->getPixmap());
}
void Widget::drawObjects()
{
    QPainter painter(this);
    QRect rect;

    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
        {
            if (this->game->map[i * WIDTH + j].typeOfSthElse == 'b')
            {
                rect.setCoords(j * 128,
                               i * 128,
                               (j + 1) * 128,
                               (i + 1) * 128);
                std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
                path += this->game->map[i * WIDTH + j].ptr->getImgName();
                path += ".png";
                QPixmap pixmap(path.c_str());
                painter.drawPixmap(rect, pixmap);
            }
        }
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
            path += this->game->map[(p->getCoords().y + j) * WIDTH + p->getCoords().x + i].typeOfSurface;
            path += ".png";
            QPixmap pixmap(path.c_str());
            painter.drawPixmap(rect, pixmap);        

            if (this->game->map[(p->getCoords().y + j) * WIDTH + p->getCoords().x + i].ptr &&
                    this->game->map[(p->getCoords().y + j) * WIDTH + p->getCoords().x + i].ptr != p)
            {
                rect.setCoords((p->getCoords().x + i) * 128,
                               (p->getCoords().y + j) * 128,
                               (p->getCoords().x + i + 1) * 128,
                               (p->getCoords().y + j + 1) * 128);
                std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
                path += this->game->map[(p->getCoords().y + j) * WIDTH + p->getCoords().x + i].ptr->getImgName();
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
        this->drawObjects();
        drawed = true;
    }
    else
    {
        this->updBg(this->game->lolo);
    }
    this->drawLolo();
}

void Widget::ex_code()
{

    //Down
    if (this->game->lolo->getDirection() == 6)
    {
        this->game->lolo->moveDown(this->game, this->timer);
    }
    //Up
    if (this->game->lolo->getDirection() == 12)
    {
        this->game->lolo->moveUp(this->game, this->timer);
    }
    //Left
    if (this->game->lolo->getDirection() == 9)
    {
        this->game->lolo->moveLeft(this->game, this->timer);
    }
    //Right
    if (this->game->lolo->getDirection() == 3)
    {
        this->game->lolo->moveRight(this->game, this->timer);
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
void Widget::keyPressEvent(QKeyEvent *e)
{
    if (!(this->timer->isActive()))
    {
        if (e->key() == Qt::Key_S || e->key() == Qt::Key_Down)
        {
            this->game->lolo->setImgName("lolo");
            this->game->lolo->setDirection(6);
            timer->start(10);
        }
        else if (e->key() == Qt::Key_W || e->key() == Qt::Key_Up)
        {
            this->game->lolo->setImgName("loloup");
            this->game->lolo->setDirection(12);
            timer->start(10);
        }
        else if (e->key() == Qt::Key_A || e->key() == Qt::Key_Left)
        {
            this->game->lolo->setImgName("lololeft");
            this->game->lolo->setDirection(9);
            this->timer->start(10);
        }
        else if (e->key() == Qt::Key_D || e->key() == Qt::Key_Right)
        {
            this->game->lolo->setImgName("loloright");
            this->game->lolo->setDirection(3);
            this->timer->start(10);
        }
    }
}
Widget::~Widget()
{
    delete ui;
}
