#include "components/UnoGameEngine.h"
#include "components/UnoBot.h"


int main() {
    RandomUnoDeck deck;
    GameState state(&deck);
    UnoGameEngine engine(&state);

    UnoBot first(&state);
    UnoBot second(&state);

    state.add_bot(&first);
    state.add_bot(&second);

    engine.start_game();
    return 0;
}


