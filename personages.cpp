#include "personages.h"

Personages::Personages(bool shootable, unsigned int x, unsigned int y, unsigned int direction):
    Objects(shootable, false), x{x}, y{y}, stepUpDown{0}, stepLeftRight{0}, direction{direction}
{}
