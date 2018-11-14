#include "heart.h"
#include "objects.h"

Heart::Heart(bool shootable, bool walkable, unsigned int giveAmmo):
    Objects(shootable, walkable), giveAmmo{giveAmmo}
{
}
