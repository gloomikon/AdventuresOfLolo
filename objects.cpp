#include "objects.h"
#include <QPainter>
#include "widget.h"

Object::Object(bool shootable, bool walkable, std::string imgName, int x, int y):
    shootable{shootable}, walkable{walkable}, imgName{imgName}, coords{x,y}
{
}

bool Object::isShootable()
{
    return this->shootable;
}

bool Object::isWalkable()
{
    return this->walkable;
}

void Object::setImgName(std::string imgName)
{
    this->imgName = imgName;
}

void Object::makeWalkable()
{
    this->walkable = true;
}

std::string Object::getImgName()
{
    return this->imgName;
}

Coords Object::getCoords()
{
    return this->coords;
}

void Object::setCoords(int x, int y)
{
    this->coords.x = x;
    this->coords.y = y;
}

void Object::drawSelf(Widget *w)
{
    QPainter painter(w);
    QRect rect;
    rect.setCoords(this->coords.x * SIZE,
                   this->coords.y * SIZE,
                   (this->coords.x+1) * SIZE,
                   (this->coords.y+1) * SIZE);
    std::string path= "C://Users/gloomikon/Documents/AndenturesOfLolo/imgs/";
    path += this->imgName;
    path += ".png";
    QPixmap pixmap(path.c_str());
    painter.drawPixmap(rect, pixmap);
}
