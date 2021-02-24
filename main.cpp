#include "components/UnoGameEngine.h"
#include "components/UnoBot.h"


int main() {
    RandomUnoDeck deck;
    GameState state(&deck);
    UnoGameEngine engine(&state);

    UnoBot first(&state);
    UnoBot second(&state);
    UnoBot third(&state);
    UnoBot four(&state);
    UnoBot five(&state);

    state.add_bot(&first);
    state.add_bot(&second);
    state.add_bot(&third);
    state.add_bot(&four);
    state.add_bot(&five);

    engine.start_game();

    return 0;
}


