#include "state.h"
#include "chest.h"
#include "game.h"

void ClosedState::chestAction(Chest *chest)
{
    if (Game::Instance().getHeartsToPick() == Game::Instance().getLolo()->getHeartsPicked())
    {
        chest->setImgName("chest02");
        chest->setCurrentState(new OpenedStateWithJewellery);
        delete this;
    }
}

ClosedState::~ClosedState()
{

}


void OpenedStateWithJewellery::chestAction(Chest *chest)
{
     chest->setImgName("chest03");
     chest->setCurrentState(new OpenedStateWithoutJewellery);
     Game::Instance().clear();
     Game::Instance().getEXit()->setImgName("exitopen");
     Game::Instance().getEXit()->makeWalkable();
     Game::Instance().setFirstDraw(true);
     delete this;
}

void OpenedStateWithoutJewellery::chestAction(Chest *)
{

}

State::~State()
{

}
