#ifndef FOOLGAME_VIEW_H
#define FOOLGAME_VIEW_H


#include <iostream>
#include "Deck.h"
#include "GameState.h"


class ViewInterface {
public:
    explicit
    ViewInterface(GameState * state) : state(state) {};

    virtual void
    start_game() = 0;

    virtual void
    enemy_move(std::string) = 0;

    virtual void
    move(Card) = 0;

private:
    GameState * state;
};


class CommandLineView : public ViewInterface {
public:
    explicit CommandLineView(GameState *);

    void
    start_game() override;

    void
    enemy_move(std::string) override;

    void
    move(Card) override;
};


#endif //FOOLGAME_VIEW_H
