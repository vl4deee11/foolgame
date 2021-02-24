#include "Card.h"

//constexpr
Card::Card(UNO::color_t color, UNO::card_type_t type)
    : color(color), type(type)
{}

//constexpr
Card::Card(UNO::card_prototype& card)
    : Card(card.color, card.type)
{}

//constexpr
Card &
Card::operator=(UNO::card_prototype const& card)
{
    this->color = card.color;
    this->type = card.type;

    return *this;
}

//constexpr
Card::Card(Card &card) noexcept
    : Card(card.color, card.type)
{}

Card::Card(Card&& card) noexcept
    : color(card.color), type(card.type)
{}

bool
Card::has_color(UNO::color_t color)
{
    return this->color == color;
}

bool
Card::has_type(UNO::card_type_t type)
{
    return this->type == type;
}

UNO::color_t
Card::get_color() const
{
    return this->color;
}

UNO::card_type_t
Card::get_type() const
{
    return this->type;
}


void
swap(Card &a, Card &b)
{
    std::swap(a.color, b.color);
    std::swap(a.type, b.type);
}
