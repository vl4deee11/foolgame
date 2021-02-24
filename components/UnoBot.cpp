#include "UnoBot.h"


UnoBot::UnoBot(GameState *state)
    : state(state)
{
    take_cards(state->get_card_in_hand());
}

Card*
UnoBot::make_move() {
    /// TODO: написать класс Predictor
    Card * best = nullptr;

    for (auto card : hand) {
        if (can_move(card)) {
            best = card;
        }
    }

    while (best == nullptr) {
        hand.push_back(state->get_next_card());
        if (can_move(hand.back())) {
            best = hand.back();
        }
    }

    hand.remove(best);

    return best;
}

bool
UnoBot::empty() const
{
    return hand.empty();
}

void
UnoBot::take_cards(size_t count)
{
    for (int i = 0; i < count; ++i)
        hand.push_back(state->get_next_card());
}

bool UnoBot::can_move(Card * card) {
    auto top_card = state->get_top_card();

    return top_card->has_color(card->get_color()) || top_card->has_type(card->get_type());
}

std::list<Card *> * UnoBot::get_hand() {
    return &hand;
}
