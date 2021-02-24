#ifndef FOOLGAME_DECK_H
#define FOOLGAME_DECK_H


#include <vector>
#include <list>

#include "Card.h"


class DeckInterface {
public:
    DeckInterface() = default;
    virtual Card * next() = 0;
    virtual void discard(Card *) = 0;
    virtual void shuffle_discard_deck() = 0;
};


class UnoDeck : public DeckInterface {
public:
    UnoDeck();

    Card * next() override;
    void discard(Card *) override;
    void shuffle_discard_deck() override;


protected:
    size_t current;
    std::vector<Card> all_cards;
    std::list<Card *> current_deck;
    std::list<Card *> discard_deck;
};


class RandomUnoDeck : public UnoDeck {
public:
    RandomUnoDeck();

    void random_shuffle();

    void shuffle_discard_deck() override;
};


#endif //FOOLGAME_DECK_H