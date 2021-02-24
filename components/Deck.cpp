#include <random>
#include <map>
#include "Deck.h"


Card *
UnoDeck::next()
{
    if (current_deck.empty()) {
        shuffle_discard_deck();
    }

    auto card = current_deck.front();
    current_deck.pop_front();
    return card;
}


UnoDeck::UnoDeck()
    : DeckInterface(), current(0)
{
    constexpr auto deck = UNO::generate_deck();
    all_cards.resize(deck.size());
    current_deck.resize(deck.size());

    std::copy(deck.begin(), deck.end(), all_cards.begin());
    std::transform(all_cards.begin(), all_cards.end(),
                   current_deck.begin(),
                   [] (Card& card) { return &card; });
}

void
UnoDeck::discard(Card* card)
{
    discard_deck.push_back(card);
}

void
UnoDeck::shuffle_discard_deck()
{
    current_deck.resize(discard_deck.size());

    std::copy(discard_deck.begin(), discard_deck.end(),
              current_deck.begin());

    discard_deck.clear();
}


RandomUnoDeck::RandomUnoDeck()
    : UnoDeck()
{
    this->random_shuffle();
}

void
RandomUnoDeck::random_shuffle()
{
    auto device = std::random_device {};
    auto engine = std::default_random_engine { device() };

    std::vector<Card *> temp_deck(current_deck.size());

    std::copy(current_deck.begin(), current_deck.end(), temp_deck.begin());
    std::shuffle(temp_deck.begin(), temp_deck.end(), engine);
    std::copy(temp_deck.begin(), temp_deck.end(), current_deck.begin());
}

void RandomUnoDeck::shuffle_discard_deck() {
    UnoDeck::shuffle_discard_deck();
    random_shuffle();
}


