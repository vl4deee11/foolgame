#ifndef FOOLGAME_UNOBOT_H
#define FOOLGAME_UNOBOT_H

#include <list>
#include "Card.h"
#include "Deck.h"
#include "GameState.h"


class UnoBot {
public:
    explicit
    UnoBot(GameState * state);

    Card *
    make_move();

    [[nodiscard]] bool
    empty() const;

    void
    take_cards(size_t count);

    bool
    can_move(Card *);

    std::list<Card *> *
    get_hand();


private:
    GameState * state;
    std::list<Card *> hand;
};


#endif //FOOLGAME_UNOBOT_H
