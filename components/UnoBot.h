#ifndef FOOLGAME_UNOBOT_H
#define FOOLGAME_UNOBOT_H

#include <list>
#include <set>
#include "Card.h"
#include "Deck.h"
#include "GameState.h"


class UnoBot {
public:
    explicit
    UnoBot(GameState *state);

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

    std::set<Card *>
    get_hand_set();


private:
    GameState *state;
    std::list<Card *> hand;

    std::list<Card *> get_opponent_cards();
};


#endif //FOOLGAME_UNOBOT_H
