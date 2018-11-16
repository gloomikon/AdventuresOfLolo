#ifndef OBJECTS_H
#define OBJECTS_H

class Objects
{
private:
    bool            shootable;
    bool            walkable;
protected:
public:
    Objects(bool shootable, bool walkable);
    bool    isShootable();
    bool    isWalkable();
};

#endif // OBJECTS_H
