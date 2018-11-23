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
    this->setFixedSize(13*128,13*128);
    this->setAttribute(Qt::WA_OpaquePaintEvent);
    this->setWindowTitle("Adventures of Lolo by KOLUMBIA");
    this->game = new Game("level1.txt");
    this->timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(ex_code()));
    QRect rect;
    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
        {
            if (this->game->map[i * WIDTH + j].typeOfSthElse == 'L')
            {
                rect.setCoords(static_cast<int>(j) * 128,
                               static_cast<int>(i) * 128,
                               static_cast<int>((j + 1)) * 128,
                               static_cast<int>((i + 1)) * 128);
                this->rectLolo = rect;
            }
        }

    /*std::ofstream file;
    file.open("C://Users/gloomikon/Documents/AndenturesOfLolo/lvls/level1o.txt");
    for (int i =0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
            file << this->game->map[i * 13 + j].typeOfSurface;
        file << "\n";
    }
    file.close();*/
}

void Widget::drawSurface()
{
    QPainter painter(this);
    QRect rect;

    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
        {
            rect.setCoords(static_cast<int>(j) * 128,
                           static_cast<int>(i) * 128,
                           static_cast<int>((j + 1)) * 128,
                           static_cast<int>((i + 1)) * 128);
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->game->map[i * WIDTH + j].typeOfSurface;
            path += ".png";
            QPixmap pixmap(path.c_str());
            painter.drawPixmap(rect, pixmap);
            if (this->game->map[i * WIDTH + j].typeOfSthElse == 't' ||
                this->game->map[i * WIDTH + j].typeOfSthElse == 'r' ||
                this->game->map[i * WIDTH + j].typeOfSthElse == 'e')
            {
                path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
                path += this->game->map[i * WIDTH + j].typeOfSthElse;
                path += ".png";
                QPixmap pixmap(path.c_str());
                painter.drawPixmap(rect, pixmap);
            }
        }
}
void Widget::drawLolo()
{
    QPainter painter(this);
    std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
    path += this->imgLolo;
    path += ".png";
    QPixmap pixmap(path.c_str());
    painter.drawPixmap(this->rectLolo, pixmap);
}
void Widget::drawObjects()
{
    QPainter painter(this);
    QRect rect;

    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
        {
            if (!(this->game->map[i * WIDTH + j].typeOfSthElse == 't' ||
                  this->game->map[i * WIDTH + j].typeOfSthElse == 'r' ||
                  this->game->map[i * WIDTH + j].typeOfSthElse == 'e' ||
                  this->game->map[i * WIDTH + j].typeOfSthElse == 'L'))
            {
                rect.setCoords(static_cast<int>(j) * 128,
                               static_cast<int>(i) * 128,
                               static_cast<int>((j + 1)) * 128,
                               static_cast<int>((i + 1)) * 128);
                std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
                path += this->game->map[i * WIDTH + j].imgName;
                path += ".png";
                QPixmap pixmap(path.c_str());
                painter.drawPixmap(rect, pixmap);
            }
        }
}

void Widget::updBg()
{
    QPainter painter(this);
    QRect rect;
    for (int i = -1; i < 2; i++)
        for (int j = -1; j < 2; j++)
        {
            rect.setCoords((this->game->lolo->x + i) * 128,
                           (this->game->lolo->y + j) * 128,
                           (this->game->lolo->x + i + 1) * 128,
                           (this->game->lolo->y + j + 1) * 128);
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->game->map[(static_cast<int>(this->game->lolo->y) + j) * static_cast<int>(WIDTH) +
                    static_cast<int>(this->game->lolo->x) + i].typeOfSurface;
            path += ".png";
            QPixmap pixmap(path.c_str());
            painter.drawPixmap(rect, pixmap);

            path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            if (this->game->map[(this->game->lolo->y + j) * WIDTH + this->game->lolo->x + i].typeOfSthElse == 't' ||
                this->game->map[(this->game->lolo->y + j) * WIDTH + this->game->lolo->x + i].typeOfSthElse == 'r' ||
                this->game->map[(this->game->lolo->y + j) * WIDTH + this->game->lolo->x + i].typeOfSthElse == 'e')
                path += this->game->map[(this->game->lolo->y + j) * WIDTH + this->game->lolo->x + i].typeOfSthElse;
            else if (this->game->map[(this->game->lolo->y + j) * WIDTH + this->game->lolo->x + i].typeOfSthElse != 'L')
                path += this->game->map[(this->game->lolo->y + j) * WIDTH + this->game->lolo->x + i].imgName;
            path += ".png";
            pixmap = QPixmap(path.c_str());
            painter.drawPixmap(rect, pixmap);
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
        this->updBg();
    }
    this->drawLolo();
}

void Widget::ex_code()
{
    int *x1 = new int;
    int *y1 = new int;
    int *x2 = new int;
    int *y2 = new int;
    static unsigned int steps = 0;
    this->rectLolo.getCoords(x1, y1, x2, y2);
    //Down
    if (this->direction == 6)
    {
        if (this->game->lolo->canMoveDown(this->game))
        {
            this->rectLolo.moveTop(*y1 + 4);
            steps+=4;
            if (steps >= 8 && steps < 16)
                this->imgLolo = "lolodown1";
            else if (steps >= 16 && steps < 24)
                this->imgLolo = "lolodown2";
            else if (steps >= 24 && steps < 32)
                this->imgLolo = "lolodown1";
            else if (steps >= 32 && steps < 40)
                this->imgLolo = "lolodown3";
            else if (steps >= 40 && steps < 48)
                this->imgLolo = "lolodown4";
            else if (steps >= 48 && steps < 56)
                this->imgLolo = "lolodown3";
            else if (steps >= 56 && steps < 64)
                this->imgLolo = "lolo";
            else if (steps == 64)
            {
                if (this->game->lolo->stepUpDown)
                {
                    if (this->game->lolo->stepUpDown == 6)
                    {
                        this->game->lolo->y++;
                        this->game->map[(this->game->lolo->y - 1) * WIDTH + this->game->lolo->x].isLoloHere = false;
                    if (this->game->lolo->stepLeftRight == 3)
                        this->game->map[(this->game->lolo->y - 1) * WIDTH + this->game->lolo->x + 1].isLoloHere = false;
                    if (this->game->lolo->stepLeftRight == 9)
                        this->game->map[(this->game->lolo->y - 1) * WIDTH + this->game->lolo->x - 1].isLoloHere = false;
                    this->game->map[(this->game->lolo->y) * WIDTH + this->game->lolo->x].isLoloHere = true;
                    if (this->game->lolo->stepLeftRight == 3)
                        this->game->map[(this->game->lolo->y) * WIDTH + this->game->lolo->x + 1].isLoloHere = true;
                    if (this->game->lolo->stepLeftRight == 9)
                        this->game->map[(this->game->lolo->y) * WIDTH + this->game->lolo->x - 1].isLoloHere = true;
                    }
                    this->game->lolo->stepUpDown = 0;
                }
                else
                {
                    this->game->lolo->stepUpDown = 6;
                }
                steps = 0;
                this->timer->stop();
            }
        }
        else
            this->timer->stop();
    }
    //Up
    if (this->direction == 12)
    {
        if (this->game->lolo->canMoveUp(this->game))
        {
            this->rectLolo.moveTop(*y1 - 4);
            steps+=4;
            if (steps >= 8 && steps < 16)
                this->imgLolo = "loloup1";
            else if (steps >= 16 && steps < 24)
                this->imgLolo = "loloup2";
            else if (steps >= 24 && steps < 32)
                this->imgLolo = "loloup1";
            else if (steps >= 32 && steps < 40)
                this->imgLolo = "loloup3";
            else if (steps >= 40 && steps < 48)
                this->imgLolo = "loloup4";
            else if (steps >= 48 && steps < 56)
                this->imgLolo = "loloup3";
            else if (steps >= 56 && steps < 64)
                this->imgLolo = "loloup";
            else if (steps == 64)
            {
                if (this->game->lolo->stepUpDown)
                {
                    if (this->game->lolo->stepUpDown == 12)
                    {
                        this->game->lolo->y--;
                        this->game->map[(this->game->lolo->y + 1) * WIDTH + this->game->lolo->x].isLoloHere = false;
                        if (this->game->lolo->stepLeftRight == 3)
                            this->game->map[(this->game->lolo->y + 1) * WIDTH + this->game->lolo->x + 1].isLoloHere = false;
                        if (this->game->lolo->stepLeftRight == 9)
                            this->game->map[(this->game->lolo->y + 1) * WIDTH + this->game->lolo->x - 1].isLoloHere = false;
                        this->game->map[(this->game->lolo->y) * WIDTH + this->game->lolo->x].isLoloHere = true;
                        if (this->game->lolo->stepLeftRight == 3)
                            this->game->map[(this->game->lolo->y) * WIDTH + this->game->lolo->x + 1].isLoloHere = true;
                        if (this->game->lolo->stepLeftRight == 9)
                            this->game->map[(this->game->lolo->y) * WIDTH + this->game->lolo->x - 1].isLoloHere = true;
                    }
                    this->game->lolo->stepUpDown = 0;
                }
                else
                    this->game->lolo->stepUpDown = 12;
                steps = 0;
                this->timer->stop();
            }
        }
        else
            this->timer->stop();
    }
    //Left
    if (this->direction == 9)
    {
        if (this->game->lolo->canMoveLeft(this->game))
        {
            this->rectLolo.moveLeft(*x1 - 4);
            steps+=4;
            if (steps >= 8 && steps < 16)
                this->imgLolo = "lololeft1";
            else if (steps >= 16 && steps < 24)
                this->imgLolo = "lololeft2";
            else if (steps >= 24 && steps < 32)
                this->imgLolo = "lololeft1";
            else if (steps >= 32 && steps < 40)
                this->imgLolo = "lololeft3";
            else if (steps >= 40 && steps < 48)
                this->imgLolo = "lololeft4";
            else if (steps >= 48 && steps < 56)
                this->imgLolo = "lololeft3";
            else if (steps >= 56 && steps < 64)
                this->imgLolo = "lololeft";
            else if (steps == 64)
            {
                if (this->game->lolo->stepLeftRight)
                {
                    if (this->game->lolo->stepLeftRight == 9)
                        this->game->lolo->x--;
                    this->game->map[(this->game->lolo->y) * WIDTH + this->game->lolo->x + 1].isLoloHere = false;
                    if (this->game->lolo->stepUpDown == 12)
                        this->game->map[(this->game->lolo->y - 1) * WIDTH + this->game->lolo->x + 1].isLoloHere = false;
                    if (this->game->lolo->stepUpDown == 6)
                        this->game->map[(this->game->lolo->y + 1) * WIDTH + this->game->lolo->x + 1].isLoloHere = false;
                    this->game->map[(this->game->lolo->y) * WIDTH + this->game->lolo->x].isLoloHere = true;
                    if (this->game->lolo->stepUpDown == 12)
                        this->game->map[(this->game->lolo->y - 1) * WIDTH + this->game->lolo->x].isLoloHere = true;
                    if (this->game->lolo->stepUpDown == 6)
                        this->game->map[(this->game->lolo->y + 1) * WIDTH + this->game->lolo->x].isLoloHere = true;
                    this->game->lolo->stepLeftRight = 0;
                }
                else
                    this->game->lolo->stepLeftRight = 9;
                steps = 0;
                this->timer->stop();
            }
        }
        else
            this->timer->stop();
    }
    //Right
    if (this->direction == 3)
    {
        if (this->game->lolo->canMoveRight(this->game))
        {
            this->rectLolo.moveLeft(*x1 + 4);
            steps+=4;
            if (steps >= 8 && steps < 16)
                this->imgLolo = "loloright1";
            else if (steps >= 16 && steps < 24)
                this->imgLolo = "loloright2";
            else if (steps >= 24 && steps < 32)
                this->imgLolo = "loloright1";
            else if (steps >= 32 && steps < 40)
                this->imgLolo = "loloright3";
            else if (steps >= 40 && steps < 48)
                this->imgLolo = "loloright4";
            else if (steps >= 48 && steps < 56)
                this->imgLolo = "loloright3";
            else if (steps >= 56 && steps < 64)
                this->imgLolo = "loloright";
            else if (steps == 64)
            {
                if (this->game->lolo->stepLeftRight)
                {
                    if (this->game->lolo->stepLeftRight == 3)
                        this->game->lolo->x++;
                    this->game->map[(this->game->lolo->y) * WIDTH + this->game->lolo->x - 1].isLoloHere = false;
                    if (this->game->lolo->stepUpDown == 12)
                        this->game->map[(this->game->lolo->y - 1) * WIDTH + this->game->lolo->x - 1].isLoloHere = false;
                    if (this->game->lolo->stepUpDown == 6)
                        this->game->map[(this->game->lolo->y + 1) * WIDTH + this->game->lolo->x - 1].isLoloHere = false;
                    this->game->map[(this->game->lolo->y) * WIDTH + this->game->lolo->x].isLoloHere = true;
                    if (this->game->lolo->stepUpDown == 12)
                        this->game->map[(this->game->lolo->y - 1) * WIDTH + this->game->lolo->x].isLoloHere = true;
                    if (this->game->lolo->stepUpDown == 6)
                        this->game->map[(this->game->lolo->y + 1) * WIDTH + this->game->lolo->x].isLoloHere = true;
                    this->game->lolo->stepLeftRight = 0;
                }
                else
                    this->game->lolo->stepLeftRight = 3;
                steps = 0;
                this->timer->stop();
            }
        }
        else
            this->timer->stop();
    }
    if (this->game->map[this->game->lolo->y * WIDTH + this->game->lolo->x].typeOfSthElse == 'h')
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

    }
    update();
}
void Widget::keyPressEvent(QKeyEvent *e)
{
    if (!(this->timer->isActive()))
    {
        if (e->key() == Qt::Key_S || e->key() == Qt::Key_Down)
        {
            this->imgLolo = "lolo";
            this->direction = 6;
            timer->start(10);
        }
        else if (e->key() == Qt::Key_W || e->key() == Qt::Key_Up)
        {
            this->imgLolo = "loloup";
            this->direction = 12;
            timer->start(10);
        }
        else if (e->key() == Qt::Key_A || e->key() == Qt::Key_Left)
        {
            this->imgLolo = "lololeft";
            this->direction = 9;
            this->timer->start(10);
        }
        else if (e->key() == Qt::Key_D || e->key() == Qt::Key_Right)
        {
            this->imgLolo = "loloright";
            this->direction = 3;
            this->timer->start(10);
        }
    }
}
Widget::~Widget()
{
    delete ui;
}
