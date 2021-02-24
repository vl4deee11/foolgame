#ifndef FOOLGAME_CARD_H
#define FOOLGAME_CARD_H


#include <cstdint>
#include <array>
#include <vector>
#include "UnoRules.h"



class Card {
public:
//    constexpr
    Card(UNO::color_t color = UNO::color_t::NOTHING, UNO::card_type_t type = UNO::card_type_t::NOTHING);

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

    UNO::color_t
    get_color() const;

    UNO::card_type_t
    get_type() const;


private:
    UNO::color_t color;
    UNO::card_type_t type;
};


#endif //FOOLGAME_CARD_H
