#ifndef OBJECTS_H
# define OBJECTS_H
# define HEIGHT 13
# define WIDTH 13
# define SIZE 128

#include <iostream>


class Objects
{
private:
protected:
    bool            shootable;
    bool            walkable;
    std::string     imgName;
public:
    Objects(bool shootable, bool walkable, std::string imgName);

    bool        isShootable();
    bool        isWalkable();
    void        setImgName(std::string imgName);
    std::string getImgName();

    virtual ~Objects() = default;
};

#endif // OBJECTS_H
