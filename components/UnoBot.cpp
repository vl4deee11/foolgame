#include <deque>
#include<algorithm>
#include <map>
#include "UnoBot.h"
#include "Node.h"
#include "Heuristics.h"

UnoBot::UnoBot(GameState *state)
        : state(state), predictor(this) {
    take_cards(state->get_card_in_hand());
}

Card *
UnoBot::make_move() {
    auto best = predictor.predict_best_move();

    if (best == nullptr) {
        hand.push_back(state->get_next_card());
        if (can_move(hand.back())) {
            best = hand.back();
        }
    }

    hand.remove(best);

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

bool
UnoBot::can_move(Card *card, GameState *p_state) {
    if (p_state == nullptr) p_state = state;
    auto top_card = p_state->get_top_card();

    return card->has_color(UNO::color_t::BLACK)
           || top_card->has_color(card->get_color())
           || top_card->has_type(card->get_type());
}


std::list<Card *> *
UnoBot::get_hand() {
    return &hand;
}

std::set<Card *>
UnoBot::get_hand_set() {
    std::set<Card *> s;
    for (Card *card : *get_hand()) {
        s.insert(card);
    }
    return s;
}

std::list<Card *>
UnoBot::get_opponent_cards() {
    std::list<Card *> r;
    auto hand_set = get_hand_set();
    auto all_cards = state->get_all_cards();
    // auto current_deck = state->get_current_deck();
    auto discard_deck = state->get_discard_deck();

    for (Card *c : all_cards) {
        // auto not_in_current = !current_deck.contains(c);
        auto not_in_discard = !discard_deck.contains(c);
        auto not_in_hand = !hand_set.contains(c);
        auto not_top_card = c != state->get_top_card();
        if (/* not_in_current && */ not_in_discard && not_in_hand && not_top_card) {
            r.push_back(c);
        }
    }
    return r;
}