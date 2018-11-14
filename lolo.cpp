#include "lolo.h"


Lolo::Lolo(unsigned int moveSpeed, unsigned int x, unsigned int y, unsigned int hp, unsigned int shoots):
    Personages(moveSpeed, x, y), hp{hp}, shoots{shoots}
{}
