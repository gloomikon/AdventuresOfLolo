#ifndef OBJECTS_H
#define OBJECTS_H
#define HEIGHT 13
#define WIDTH 13

class Objects
{
private:
protected:
    bool            shootable;
    bool            walkable;
public:
    Objects(bool shootable, bool walkable);
    bool    isShootable();
    bool    isWalkable();
};

#endif // OBJECTS_H
