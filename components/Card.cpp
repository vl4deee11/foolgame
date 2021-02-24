#include "Card.h"

//constexpr
Card::Card(UNO::color_t color, UNO::card_type_t type, UNO::color_t next_color)
    : color(color), type(type), next_color(next_color)
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
    this->next_color = UNO::color_t::NOTHING;

    return *this;
}

//constexpr
Card::Card(Card &card) noexcept
    : Card(card.color, card.type)
{}

Card::Card(Card&& card) noexcept
    : color(card.color), type(card.type), next_color(card.next_color)
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

void
Card::set_color(UNO::color_t color)
{
    this->color = color;
}

void
Card::set_next_color(UNO::color_t next)
{
    this->next_color = next;
}

UNO::color_t Card::get_next_color() const {
    return next_color;
}
