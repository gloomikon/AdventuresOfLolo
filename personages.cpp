#include "personages.h"
#include "game.h"

Personages::Personages(bool shootable, int x, int y, int direction):
    Objects(shootable, false), x{x}, y{y}, stepUpDown{0}, stepLeftRight{0}, direction{direction}
{}

bool Personages::canMoveLeft(Game *game)
{
    if (this->stepLeftRight == 3)
        return (true);
    if (game->map[this->y * WIDTH + this->x - 1].ptr)
    {
        if (!(game->map[this->y * WIDTH + this->x - 1].ptr->isWalkable()))
            return (false);
    }
    if (game->map[(this->y - 1) * WIDTH + this->x - 1].ptr)
    {
        if (this->stepUpDown == 12 &&
                !(game->map[(this->y - 1) * WIDTH + this->x - 1].ptr->isWalkable()))
            return (false);
    }
    if (game->map[(this->y + 1) * WIDTH + this->x - 1].ptr)
    {
        if (this->stepUpDown == 6 &&
                !(game->map[(this->y + 1) * WIDTH + this->x - 1].ptr->isWalkable()))
            return (false);
    }
    return (true);
}

bool Personages::canMoveRight(Game *game)
{
    if (this->stepLeftRight == 9)
        return (true);
    if (game->map[this->y * WIDTH + this->x + 1].ptr)
    {
        if (!(game->map[this->y * WIDTH + this->x + 1].ptr->isWalkable()))
            return (false);
    }
    if (game->map[(this->y - 1) * WIDTH + this->x + 1].ptr)
    {
        if (this->stepUpDown == 12 &&
                !(game->map[(this->y - 1) * WIDTH + this->x + 1].ptr->isWalkable()))
            return (false);
    }
    if (game->map[(this->y + 1) * WIDTH + this->x + 1].ptr)
    {
        if (this->stepUpDown == 6 &&
                !(game->map[(this->y + 1) * WIDTH + this->x + 1].ptr->isWalkable()))
            return (false);
    }
    return (true);
}

bool Personages::canMoveUp(Game *game)
{
    if (this->stepUpDown == 6)
        return (true);
    if (game->map[(this->y - 1) * WIDTH + this->x].ptr)
    {
        if (!(game->map[(this->y - 1) * WIDTH + this->x].ptr->isWalkable()))
            return (false);
    }
    if (game->map[(this->y - 1) * WIDTH + (this->x + 1)].ptr)
    {
        if (this->stepLeftRight == 3 &&
                !(game->map[(this->y - 1) * WIDTH + (this->x + 1)].ptr->isWalkable()))
            return (false);
    }
    if (game->map[(this->y - 1) * WIDTH + (this->x - 1)].ptr)
    {
        if (this->stepLeftRight == 9 &&
                !(game->map[(this->y - 1) * WIDTH + (this->x - 1)].ptr->isWalkable()))
            return (false);
    }
    return (true);
}

bool Personages::canMoveDown(Game *game)
{
    if (this->stepUpDown == 12)
        return (true);
    if (game->map[(this->y + 1) * WIDTH + this->x].ptr)
    {
        if (!(game->map[(this->y + 1) * WIDTH + this->x].ptr->isWalkable()))
            return (false);
    }
    if (game->map[(this->y + 1) * WIDTH + (this->x + 1)].ptr)
    {
        if (this->stepLeftRight == 3 &&
                !(game->map[(this->y + 1) * WIDTH + (this->x + 1)].ptr->isWalkable()))
            return (false);
    }
    if (game->map[(this->y + 1) * WIDTH + (this->x - 1)].ptr)
    {
        if (this->stepLeftRight == 9 &&
                !(game->map[(this->y + 1) * WIDTH + (this->x - 1)].ptr->isWalkable()))
            return (false);
    }
    return (true);
}
