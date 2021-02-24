#include <iostream>
#include "UnoGameEngine.h"

UnoGameEngine::UnoGameEngine(GameState *state)
    : state(state)
{}


void
UnoGameEngine::start_game()
{
    state->init();

    std::cout << "Starting game..." << std::endl;
    start_game_loop();
}


void
UnoGameEngine::start_game_loop()
{
    while (get_winner() == -1) {
//        auto top_card = state->get_top_card();
        process_special_cards();

        state->print_info_about_player();

        if (state->can_current_player_move()) {
            state->make_move();
        }

        std::cout << std::endl;
        state->change_player();
    }

    std::cout << "Player " << get_winner() << " has WON!!!" << std::endl;
}

int
UnoGameEngine::get_winner()
{
    return state->get_winner();
}

void
UnoGameEngine::process_special_cards()
{
    auto top_card = state->get_top_card();

    if (state->need_process_top_card()) {
        if (top_card->has_type(UNO::card_type_t::CANCEL)) {
            state->cancel_current_move();
        } else if (top_card->has_type(UNO::card_type_t::REVERSE)) {
            state->reverse_moving();
        } else if (top_card->has_type(UNO::card_type_t::TAKE_2)) {
            state->add_cards_to_current_player(2);
            state->cancel_current_move();
        } else if (top_card->has_type(UNO::card_type_t::TAKE_4)) {
            state->add_cards_to_current_player(4);
            state->change_color(top_card->get_next_color());
            state->cancel_current_move();
        } else if (top_card->has_type(UNO::card_type_t::CHANGE_COLOR)) {
            state->change_color(top_card->get_next_color());
        }
        else return;
        state->set_processed();
    }
}

