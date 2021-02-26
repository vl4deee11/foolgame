#include <iostream>
#include "GameState.h"
#include "UnoBot.h"


GameState::GameState(DeckInterface *deck, size_t card_in_hand)
        : deck(deck), top_card(), card_in_hand(card_in_hand), current_player(0), cancel_move(false),
          reversed_order(false), need_process_card(true), virtual_color(UNO::color_t::NOTHING) {}

void
GameState::set_top_card(Card *card) {
    need_process_card = true;
    virtual_color = UNO::color_t::NOTHING;
    top_card = *card;
    deck->discard(card);
}

Card *
GameState::get_top_card() {
    return &top_card;
}

void
GameState::init() {
    set_top_card(deck->next());

    std::cout << "Initializing game state: " << std::endl
              << "\tcard_in_hands = " << card_in_hand << std::endl
              << "\ttop_card = (" << UNO::color_to_string(get_top_card()->get_color()) << ", "
              << UNO::type_to_string(get_top_card()->get_type()) << ")" << std::endl
              << "\tcurrent_player = " << current_player << std::endl;
}

bool
GameState::can_current_player_move() const {
    return !cancel_move;
}

void
GameState::cancel_current_move() {
    cancel_move = true;
}

int
GameState::next_player() {
    auto next = current_player;
    next += (reversed_order ? -1 : 1);
    next = next % static_cast<int>(bots.size());
    if (next < 0) next += bots.size();

    return next;
}


void
GameState::reverse_moving() {
    reversed_order = !reversed_order;
}

void
GameState::add_cards_to_current_player(size_t count) {
    bots[current_player]->take_cards(count);
}

void
GameState::change_color(UNO::color_t color) {
    top_card.set_color(color);
}

bool
GameState::has_winner() {
    return get_winner() != -1;
}

int
GameState::get_winner() {
    auto winner = -1;

    for (auto i = 0; i < bots.size(); ++i) {
        if (bots[i]->empty()) winner = i;
    }

    return winner;
}

Card *
GameState::get_next_card() {
    return deck->next();
}

size_t
GameState::get_card_in_hand() const {
    return card_in_hand;
}

void
GameState::add_bot(UnoBot *bot) {
    bots.emplace_back(bot);
}


void
GameState::make_move() {
    auto new_card = bots[current_player]->make_move();
    if (new_card != nullptr) {
        set_top_card(new_card);
        std::cout << "Player " << current_player << " make move: ("
                  << UNO::color_to_string(get_top_card()->get_color()) << ", "
                  << UNO::type_to_string(get_top_card()->get_type()) << ")" << std::endl;
    }
}

void
GameState::print_info_about_player() {
    auto bot = bots[current_player];

    std::cout << "Player " << current_player << ": " << std::endl
              << "\thas " << bot->get_hand()->size() << " all_cards in hand" << std::endl;
}

void
GameState::set_processed() {
    need_process_card = false;
}

bool
GameState::need_process_top_card() const {
    return need_process_card;
}

void
GameState::change_player() {
    cancel_move = false;
    current_player = next_player();
}

std::vector<Card *> GameState::get_all_cards() {
    return deck->get_all_cards();
}

std::set<Card *> GameState::get_current_deck() {
    return deck->get_current_deck();
}

std::set<Card *> GameState::get_discard_deck() {
    return deck->get_discard_deck();
}
