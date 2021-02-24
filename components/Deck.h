#ifndef FOOLGAME_DECK_H
#define FOOLGAME_DECK_H


#include <vector>
#include "Card.h"


class DeckInterface {
public:
    DeckInterface() = default;
    virtual Card * next() = 0;
};


class UnoDeck : public DeckInterface {
public:
    UnoDeck();

    Card * next() override;


protected:
    size_t current;
    std::vector<Card> cards;
};


class RandomUnoDeck : public UnoDeck {
public:
    RandomUnoDeck();
};


#endif //FOOLGAME_DECK_H