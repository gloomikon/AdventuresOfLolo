#ifndef PERSONAGES_H
#define PERSONAGES_H

class Personages
{
private:
    unsigned int    moveSpeed;
protected:
public:
    unsigned int    x;
    unsigned int    y;
    Personages(unsigned int moveSpeed, unsigned int x, unsigned int y);
};

#endif // PERSONAGES_H
