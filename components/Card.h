#ifndef FOOLGAME_CARD_H
#define FOOLGAME_CARD_H


#include <cstdint>
#include <array>
#include <vector>
#include "UnoRules.h"



class Card {
public:
//    constexpr
    /// TODO: поменять next_color на Nothing и реализовать нормальное поведение
    Card(UNO::color_t color = UNO::color_t::NOTHING, UNO::card_type_t type = UNO::card_type_t::NOTHING,
         UNO::color_t next_color = UNO::color_t::NOTHING);

//    constexpr
    Card(Card&) noexcept;

    Card(Card&&) noexcept;

    //    constexpr
    Card(UNO::card_prototype&);

//    constexpr
    Card&
    operator=(Card const&) = default;

//    constexpr
    Card&
    operator=(UNO::card_prototype const&);

    friend void swap(Card&, Card&);

    bool
    has_color(UNO::color_t);

    bool
    has_type(UNO::card_type_t);

    [[nodiscard]] UNO::color_t
    get_color() const;

    [[nodiscard]] UNO::card_type_t
    get_type() const;

    [[nodiscard]] UNO::color_t
    get_next_color() const;

    void
    set_color(UNO::color_t);

    void
    set_next_color(UNO::color_t);

private:
    UNO::color_t color;
    UNO::card_type_t type;
    UNO::color_t next_color;
};


#endif //FOOLGAME_CARD_H
