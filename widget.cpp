#include "widget.h"
#include "ui_widget.h"
#include "game.h"

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
    this->setWindowTitle("Adventures of Lolo by KOLUMBIA");
    this->game = new Game("level1.txt");
    this->timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(ex_code()));
    QRect rect;
    for (unsigned int i = 0; i < this->game->height; i++)
        for (unsigned int j = 0; j < this->game->width; j++)
        {
            if (this->game->map[i * this->game->width + j].typeOfSthElse == 'L')
            {
                rect.setCoords(static_cast<int>(j) * 128,
                               static_cast<int>(i) * 128,
                               static_cast<int>((j + 1)) * 128,
                               static_cast<int>((i + 1)) * 128);
                this->rectLolo = rect;
            }
        }

    std::ofstream file;
    file.open("C://Users/gloomikon/Documents/AndenturesOfLolo/lvls/level1o.txt");
    for (int i =0; i < this->game->height; i++)
    {
        for (int j = 0; j < this->game->width; j++)
            file << this->game->map[i * 13 + j].typeOfSurface;
        file << "\n";
    }
    file.close();
}

void Widget::drawSurface()
{
    QPainter painter(this);
    QRect rect;

    for (unsigned int i = 0; i < this->game->height; i++)
        for (unsigned int j = 0; j < this->game->width; j++)
        {
            rect.setCoords(static_cast<int>(j) * 128,
                           static_cast<int>(i) * 128,
                           static_cast<int>((j + 1)) * 128,
                           static_cast<int>((i + 1)) * 128);
            std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
            path += this->game->map[i * this->game->width + j].typeOfSurface;
            path += ".png";
            QPixmap pixmap(path.c_str());
            painter.drawPixmap(rect, pixmap);
            if (this->game->map[i * this->game->width + j].typeOfSthElse == 't' ||
                this->game->map[i * this->game->width + j].typeOfSthElse == 'r' ||
                this->game->map[i * this->game->width + j].typeOfSthElse == 'c' ||
                this->game->map[i * this->game->width + j].typeOfSthElse == 'e')
            {
                path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
                path += this->game->map[i * this->game->width + j].typeOfSthElse;
                path += ".png";
                QPixmap pixmap(path.c_str());
                painter.drawPixmap(rect, pixmap);
            }
        }
}
void Widget::drawLolo(std::string image)
{
    QPainter painter(this);
    std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
    path += image;
    path += ".png";
    QPixmap pixmap(path.c_str());
    painter.drawPixmap(this->rectLolo, pixmap);
}
void Widget::drawObjects()
{
    QPainter painter(this);
    QRect rect;

    for (unsigned int i = 0; i < this->game->height; i++)
        for (unsigned int j = 0; j < this->game->width; j++)
        {
            if (!(this->game->map[i * this->game->width + j].typeOfSthElse == 't' ||
                  this->game->map[i * this->game->width + j].typeOfSthElse == 'r' ||
                  this->game->map[i * this->game->width + j].typeOfSthElse == 'c' ||
                  this->game->map[i * this->game->width + j].typeOfSthElse == 'e' ||
                  this->game->map[i * this->game->width + j].typeOfSthElse == 'L'))
            {
                rect.setCoords(static_cast<int>(j) * 128,
                               static_cast<int>(i) * 128,
                               static_cast<int>((j + 1)) * 128,
                               static_cast<int>((i + 1)) * 128);
                std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
                path += this->game->map[i * this->game->width + j].imgName;
                path += ".png";
                QPixmap pixmap(path.c_str());
                painter.drawPixmap(rect, pixmap);
            }
        }
}
void Widget::paintEvent(QPaintEvent *)
{
    this->drawSurface();
    this->drawObjects();
    this->drawLolo(this->imgLolo);
}

void Widget::ex_code()
{
    int *x1 = new int;
    int *y1 = new int;
    int *x2 = new int;
    int *y2 = new int;
    this->rectLolo.getCoords(x1, y1, x2, y2);
    if (this->direction == 6)
    {
        this->rectLolo.moveTop(*y1 + 4);
        this->steps+=4;
        if (this->steps >= 8 && this->steps < 16)
            this->imgLolo = "lolodown1";
        else if (this->steps >= 16 && this->steps < 24)
            this->imgLolo = "lolodown2";
        else if (this->steps >= 24 && this->steps < 32)
            this->imgLolo = "lolodown1";
        else if (this->steps >= 32 && this->steps < 40)
            this->imgLolo = "lolodown3";
        else if (this->steps >= 40 && this->steps < 48)
            this->imgLolo = "lolodown4";
        else if (this->steps >= 48 && this->steps < 56)
            this->imgLolo = "lolodown3";
        else if (this->steps >= 56 && this->steps < 64)
            this->imgLolo = "lolo";
        else if (this->steps == 64)
        {
            this->steps = 0;
            this->timer->stop();
        }
    }
    if (this->direction == 12)
    {
        this->rectLolo.moveTop(*y1 - 4);
        this->steps+=4;
        if (this->steps >= 8 && this->steps < 16)
            this->imgLolo = "loloup1";
        else if (this->steps >= 16 && this->steps < 24)
            this->imgLolo = "loloup2";
        else if (this->steps >= 24 && this->steps < 32)
            this->imgLolo = "loloup1";
        else if (this->steps >= 32 && this->steps < 40)
            this->imgLolo = "loloup3";
        else if (this->steps >= 40 && this->steps < 48)
            this->imgLolo = "loloup4";
        else if (this->steps >= 48 && this->steps < 56)
            this->imgLolo = "loloup3";
        else if (this->steps >= 56 && this->steps < 64)
            this->imgLolo = "loloup";
        else if (this->steps == 64)
        {
            this->steps = 0;
            this->timer->stop();
        }
    }
            qDebug() << this->steps << this->timer->isActive();

    update();
}
void Widget::keyPressEvent(QKeyEvent *e)
{
    if (!(this->timer->isActive()))
    {
        if (e->key() == Qt::Key_S || e->key() == Qt::Key_Down)
        {
            this->imgLolo = "lolodown1";
            this->direction = 6;
            timer->start(1);
        }
        if (e->key() == Qt::Key_W || e->key() == Qt::Key_Up)
        {
            this->imgLolo = "loloup1";
            this->direction = 12;
            timer->start(1);
        }
    }
}
Widget::~Widget()
{
    delete ui;
}
