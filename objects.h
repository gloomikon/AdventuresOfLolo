#ifndef OBJECTS_H
# define OBJECTS_H
# define HEIGHT 13
# define WIDTH 13
# define SIZE 128

# include "drawable.h"
# include <iostream>
# include <QObject>
# include <QRect>
# include <QPixmap>

struct Coords
{
    int x;
    int y;
};

class Widget;

class Object : public Drawable
{
private:
protected:
    bool            shootable;
    bool            walkable;
    std::string     imgName;
    Coords          coords;
public:
    Object(bool shootable, bool walkable, std::string imgName, int x, int y);
    void        drawSelf(Widget *w) override;
    virtual     ~Object() = default;

    bool        isShootable();
    bool        isWalkable();
    virtual void        setImgName(std::string imgName);
    void        makeWalkable();
    std::string getImgName();  
    Coords      getCoords();
    void        setCoords(int x, int y);
};

#endif // OBJECTS_H
