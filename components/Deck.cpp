#include <random>
#include <map>
#include <set>
#include "Deck.h"


Card *
UnoDeck::next() {
    if (current_deck.empty()) {
        shuffle_discard_deck();
    }

    auto card = current_deck.front();
    current_deck.pop_front();
    return card;
}

UnoDeck::UnoDeck()
        : DeckInterface(), current(0) {
    constexpr auto deck = UNO::generate_deck();
    all_cards.resize(deck.size());
    all_cards_ptrs.resize(deck.size());
    current_deck.resize(deck.size());

    std::copy(deck.begin(), deck.end(), all_cards.begin());
    std::transform(all_cards.begin(), all_cards.end(), current_deck.begin(), [](Card &card) { return &card; });
    std::copy(current_deck.begin(), current_deck.end(), all_cards_ptrs.begin());
}

void
UnoDeck::discard(Card *card) {
    discard_deck.push_back(card);
}

void
UnoDeck::shuffle_discard_deck() {
    current_deck.resize(discard_deck.size());

    std::copy(discard_deck.begin(), discard_deck.end(),
              current_deck.begin());

    discard_deck.clear();
}


RandomUnoDeck::RandomUnoDeck()
        : UnoDeck() {
    this->random_shuffle();
}

void
RandomUnoDeck::random_shuffle() {
    auto device = std::random_device{};
    auto engine = std::default_random_engine{device()};

    std::vector<Card *> temp_deck(current_deck.size());

    std::copy(current_deck.begin(), current_deck.end(), temp_deck.begin());
    std::shuffle(temp_deck.begin(), temp_deck.end(), engine);
    std::copy(temp_deck.begin(), temp_deck.end(), current_deck.begin());
}

void RandomUnoDeck::shuffle_discard_deck() {
    UnoDeck::shuffle_discard_deck();
    random_shuffle();
}

std::vector<Card *>
UnoDeck::get_all_cards() {
    return all_cards_ptrs;
}

std::set<Card *> UnoDeck::get_discard_deck() {
    std::set<Card *> s;
    for (Card *card : discard_deck) {
        s.insert(card);
    }
    return s;
}

std::set<Card *> UnoDeck::get_current_deck() {
    std::set<Card *> s;
    for (Card *card : current_deck) {
        s.insert(card);
    }
    return s;
}

UnoDeck *UnoDeck::make_copy() {
    auto *d = new UnoDeck();
    std::copy(all_cards.begin(), all_cards.end(), d->all_cards.begin());
    std::copy(all_cards_ptrs.begin(), all_cards_ptrs.end(), d->all_cards_ptrs.begin());
    d->discard_deck = std::list<Card *>(discard_deck);
    d->current_deck = std::list<Card *>(current_deck);
    d->current = current;
    return d;
}
