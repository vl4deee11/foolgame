#ifndef FOOLGAME_CONTROLLER_H
#define FOOLGAME_CONTROLLER_H


#include "GameState.h"


class ControllerInterface {
public:
    explicit
    ControllerInterface(GameState * state)
    {};

    virtual void
    make_move() = 0;

    virtual void
    make_prediction() = 0;
};


class UnoController : public ControllerInterface {
public:
    explicit
    UnoController(GameState * state);

    void
    make_move() override;

    void
    make_prediction() override;


private:
    GameState * state;
};


#endif //FOOLGAME_CONTROLLER_H
