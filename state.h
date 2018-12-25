#ifndef STATE_H
#define STATE_H


class Chest;

class State
{
public:
    virtual void chestAction(Chest *chest) = 0;
    virtual ~State() = 0;
};


class ClosedState : public State
{
    virtual void chestAction(Chest *chest) override;
    virtual ~ClosedState() override;
};

class OpenedStateWithJewellery : public State
{
    virtual void chestAction(Chest *chest) override;
};

class OpenedStateWithoutJewellery : public State
{
    virtual void chestAction(Chest *chest) override;
};

#endif // STATE_H
