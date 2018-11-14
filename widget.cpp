#include "widget.h"
#include "ui_widget.h"
#include "game.h"

#include <fstream>
#include <QMessageBox>
#include <QPainter>
#include <cmath>
#include <QKeyEvent>
Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setFixedSize(13*128,13*128);
    this->setWindowTitle("Adventures of Lolo by KOLUMBIA");
    this->game = new Game("level1.txt");
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
    file.open("C://Users/gloomikon/Documents/AdventuresOfLolo/lvls/level1o.txt");
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
void Widget::drawLolo()
{
    QPainter painter(this);
    QPixmap pixmap("C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/lolo.png");
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
    this->drawLolo();
}
void Widget::keyPressEvent(QKeyEvent *e)
{
    int *x1 = new int;
    int *y1 = new int;
    int *x2 = new int;
    int *y2 = new int;
    this->rectLolo.getCoords(x1, y1, x2, y2);
    if (e->key() == Qt::Key_S || e->key() == Qt::Key_Down)
    {
        this->rectLolo.moveTop(*y1 + 64);
        this->game->lolo->x++;
    }
    if (e->key() == Qt::Key_W || e->key() == Qt::Key_Up)
    {
        this->rectLolo.moveTop(*y1 - 64);
        this->game->lolo->x--;
    }
    if (e->key() == Qt::Key_A || e->key() == Qt::Key_Left)
    {
        this->rectLolo.moveLeft(*x1 - 64);
        this->game->lolo->x++;
    }
    if (e->key() == Qt::Key_D || e->key() == Qt::Key_Right)
    {
        this->rectLolo.moveLeft(*x1 + 64);
        this->game->lolo->x++;
    }
    update();
}
Widget::~Widget()
{
    delete ui;
}
