#include <random>
#include "Deck.h"


Card *
UnoDeck::next()
{
    return current < cards.size() ? &cards[current++] : nullptr;
}


UnoDeck::UnoDeck()
    : DeckInterface(), current(0)
{
    constexpr auto deck = UNO::generate_deck();
    cards.resize(deck.size());

    std::copy(deck.begin(), deck.end(), cards.begin());
}


RandomUnoDeck::RandomUnoDeck()
    : UnoDeck()
{
    auto device = std::random_device {};
    auto engine = std::default_random_engine { device() };
    std::shuffle(cards.begin(), this->cards.end(), engine);
}