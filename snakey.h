#ifndef SNAKEY_H
#define SNAKEY_H

#include "personages.h"
class Snakey : public Personage
{
private:
    int    shoots;
    int    heartPicked;
public:
    Snakey(int x, int y, int direction, std::string imgName);
    virtual void doAction() override final;
};
#endif // SNAKEY_H
