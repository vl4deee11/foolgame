#ifndef FOOLGAME_UNOGAMEENGINE_H
#define FOOLGAME_UNOGAMEENGINE_H


#include <cstdio>
#include "GameState.h"
#include "Deck.h"


class UnoGameEngine {
public:
    explicit
    UnoGameEngine(GameState * state);

    void
    start_game();

    int
    get_winner();


private:
    void
    start_game_loop();

    void
    process_special_cards();

    GameState * state;
};


#endif //FOOLGAME_UNOGAMEENGINE_H
