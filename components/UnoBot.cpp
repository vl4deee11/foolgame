#include "UnoBot.h"


UnoBot::UnoBot(GameState *state)
        : state(state) {
    take_cards(state->get_card_in_hand());
}

Card *
UnoBot::make_move() {
    /// TODO: написать класс Predictor
    Card *best = nullptr;
    auto opponent_cards = get_opponent_cards();

    for (auto card : hand) {
        if (can_move(card)) {
            best = card;
        }
    }

    if (best == nullptr) {
        hand.push_back(state->get_next_card());
        if (can_move(hand.back())) {
            best = hand.back();
        }
    }

    hand.remove(best);
    if (!hand.empty() && best != nullptr)
        best->set_next_color(hand.front()->get_color());

    return best;
}

bool
UnoBot::empty() const {
    return hand.empty();
}

void
UnoBot::take_cards(size_t count) {
    for (int i = 0; i < count; ++i)
        hand.push_back(state->get_next_card());
}

bool UnoBot::can_move(Card *card) {
    auto top_card = state->get_top_card();

    return card->has_color(UNO::color_t::BLACK)
           || top_card->has_color(card->get_color())
           || top_card->has_type(card->get_type());
}

std::list<Card *> *UnoBot::get_hand() {
    return &hand;
}

std::set<Card *> UnoBot::get_hand_set() {
    std::set<Card *> s;
    for (Card *card : *get_hand()) {
        s.insert(card);
    }
    return s;
}

std::list<Card *> UnoBot::get_opponent_cards() {
    std::list<Card *> r;
    auto hand_set = get_hand_set();
    auto all_cards = state->get_all_cards();
    auto current_deck = state->get_current_deck();
    auto discard_deck = state->get_discard_deck();

    for (Card *c : all_cards) {
        if (!current_deck.contains(c) && !discard_deck.contains(c) && !hand_set.contains(c)) {
            r.push_back(c);
        }
    }
    return r;
}
