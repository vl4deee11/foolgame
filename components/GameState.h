#ifndef FOOLGAME_GAMESTATE_H
#define FOOLGAME_GAMESTATE_H


#include <utility>
#include <vector>
#include "Card.h"
#include "Deck.h"


class UnoBot;


class GameState {
public:
    explicit
    GameState(DeckInterface *deck, size_t card_in_hand = 6);

    void
    add_bot(UnoBot *);

    Card *
    get_top_card();

    void
    set_top_card(Card *card);

    void
    init();

    [[nodiscard]] bool
    can_current_player_move() const;

    void
    cancel_current_move();

    void
    reverse_moving();

    void
    add_cards_to_current_player(size_t count);

    int
    next_player();

    void
    change_color(UNO::color_t);

    bool
    has_winner();

    int
    get_winner();

    Card *
    get_next_card();

    [[nodiscard]] size_t
    get_card_in_hand() const;

    void
    make_move();

    void
    print_info_about_player();

    [[nodiscard]] bool
    need_process_top_card() const;

    void
    set_processed();

    void
    change_player();

    std::vector<Card *>
    get_all_cards();

    std::set<Card *>
    get_current_deck();

    std::set<Card *>
    get_discard_deck();

    DeckInterface * deck;

private:
    Card top_card;
    size_t card_in_hand;
    int current_player;
    bool cancel_move;
    bool reversed_order;
    bool need_process_card;
    UNO::color_t virtual_color;

    std::vector<UnoBot *> bots;
};


#endif //FOOLGAME_GAMESTATE_H
