#ifndef FOOLGAME_UNORULES_H
#define FOOLGAME_UNORULES_H


#include <cmath>
#include <string>
#include <array>
#include <unordered_map>
#include <initializer_list>
#include <cstring>


namespace UNO {
    #define STRINGIFY(enum_variable) remove_namespace(#enum_variable)
    #define SWITCH(default_enum, variable)                      \
        std::string_view result = STRINGIFY(default_enum);      \
        switch (variable)

    #define CASE(enum_value)                                          \
        case enum_value:                                              \
            result = STRINGIFY(enum_value);                           \
            break;

    #define IF_EQUAL(str, enum_name, enum_variable)              \
        if (strcmp(str, #enum_variable) == 0) {                  \
            color = enum_name::enum_variable;                    \
        }


    enum class color_t : uint8_t { NOTHING, RED, GREEN, ORANGE, BLUE, BLACK, };
    enum class card_type_t : uint8_t {
        ZERO = 0, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE,
        CANCEL, REVERSE, TAKE_2, TAKE_4, CHANGE_COLOR, NOTHING
    };

    constexpr auto
    remove_namespace(std::string_view enum_variable)
    {
        auto index = enum_variable.rfind(':');

        return enum_variable.substr( index + 1);
    }

    constexpr auto
    color_to_string(color_t color)
    {
        SWITCH(color_t::NOTHING, color) {
            CASE(color_t::BLACK);
            CASE(color_t::RED);
            CASE(color_t::ORANGE);
            CASE(color_t::GREEN);
            CASE(color_t::BLUE);

            default:
                break;
        }

        return result;
    }

    constexpr auto
    type_to_string(card_type_t type)
    {
        SWITCH(card_type_t::NOTHING, type) {
            CASE(card_type_t::ZERO);
            CASE(card_type_t::ONE);
            CASE(card_type_t::TWO);
            CASE(card_type_t::THREE);
            CASE(card_type_t::FOUR);
            CASE(card_type_t::FIVE);
            CASE(card_type_t::SIX);
            CASE(card_type_t::SEVEN);
            CASE(card_type_t::EIGHT);
            CASE(card_type_t::NINE);

            CASE(card_type_t::CANCEL);
            CASE(card_type_t::REVERSE);
            CASE(card_type_t::TAKE_2);

            CASE(card_type_t::CHANGE_COLOR);
            CASE(card_type_t::TAKE_4);

            default:
                break;
        }

        return result;
    }

    auto
    string_to_color(auto color_string)
    {
        color_t color = color_t::NOTHING;

        IF_EQUAL(color_string, color_t, RED)
        else IF_EQUAL(color_string, color_t, GREEN)
        else IF_EQUAL(color_string, color_t, BLUE)
        else IF_EQUAL(color_string, color_t, ORANGE)
        else IF_EQUAL(color_string, color_t, BLACK)

        return color;
    }

    auto
    string_to_type(auto type_string)
    {
        auto color = card_type_t::NOTHING;

        IF_EQUAL(type_string, card_type_t, ZERO)
        else IF_EQUAL(type_string, card_type_t, ONE)
        else IF_EQUAL(type_string, card_type_t, TWO)
        else IF_EQUAL(type_string, card_type_t, THREE)
        else IF_EQUAL(type_string, card_type_t, FOUR)
        else IF_EQUAL(type_string, card_type_t, FIVE)
        else IF_EQUAL(type_string, card_type_t, SIX)
        else IF_EQUAL(type_string, card_type_t, SEVEN)
        else IF_EQUAL(type_string, card_type_t, EIGHT)
        else IF_EQUAL(type_string, card_type_t, NINE)

        else IF_EQUAL(type_string, card_type_t, CANCEL)
        else IF_EQUAL(type_string, card_type_t, REVERSE)
        else IF_EQUAL(type_string, card_type_t, TAKE_2)

        else IF_EQUAL(type_string, card_type_t, CHANGE_COLOR)
        else IF_EQUAL(type_string, card_type_t, TAKE_4)

        return color;
    }


    constexpr std::array colors = { color_t::RED, color_t::GREEN, color_t::ORANGE,
                                    color_t::BLUE, color_t::BLACK };

    constexpr std::array all_card_types = {
            card_type_t::ZERO, card_type_t::ONE, card_type_t::TWO,
            card_type_t::THREE, card_type_t::FOUR,card_type_t::FIVE,
            card_type_t::SIX, card_type_t::SEVEN, card_type_t::EIGHT,
            card_type_t::NINE,card_type_t::CANCEL, card_type_t::REVERSE,
            card_type_t::TAKE_2,

            card_type_t::TAKE_4, card_type_t::CHANGE_COLOR
    };



    constexpr size_t CARD_IN_DECK = 108;

    struct card_prototype {
        color_t color;
        card_type_t type;
    };


    constexpr int
    abs(int number)
    {
        return number >= 0 ? number : -number;
    }


    template <int count, typename T, size_t N>
    constexpr auto
    drop(std::array<T, N> arr)
    {
        std::array<T, N - abs(count)> result{};

        if constexpr (count > 0)
            std::copy(arr.begin() + count, arr.end(), result.begin());
        else
            std::copy(arr.begin(), arr.end() + count, result.begin());

        return result;
    }


    constexpr auto
    generate_deck()
    {
        std::array<card_prototype, CARD_IN_DECK> deck{};
        auto current = deck.begin();

        for (auto color : drop<-1>(colors)) {
            for (auto type : drop<-2>(all_card_types)) {
                *current++ = { color, type };
            }
        }

        for (auto color : drop<-1>(colors)) {
            for (auto type : drop<1>(drop<-2>(all_card_types))) {
                *current++ = { color, type };
            }
        }

        for (int i = 0; i < 4; ++i) *current++ = { color_t::BLACK, card_type_t::CHANGE_COLOR };
        for (int i = 0; i < 4; ++i) *current++ = { color_t::BLACK, card_type_t::TAKE_4 };

        return deck;
    }
};


#endif //FOOLGAME_UNORULES_H
