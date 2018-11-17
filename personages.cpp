#include "personages.h"

Personages::Personages(bool shootable, int x, int y, int direction):
    Objects(shootable, false), x{x}, y{y}, stepUpDown{0}, stepLeftRight{0}, direction{direction}
{}
