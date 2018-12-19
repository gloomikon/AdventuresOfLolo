#ifndef GOL_H
#define GOL_H


#include "personages.h"
class Gol : public Personage
{
private:
public:
    Gol(int x, int y, int direction, std::string imgName);
    virtual void doAction() override final;
};

#endif // GOL_H
