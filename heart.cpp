#include "heart.h"
#include "objects.h"

Heart::Heart(bool shootable, bool walkable, int giveAmmo):
    Objects(shootable, walkable), giveAmmo{giveAmmo}
{
}
