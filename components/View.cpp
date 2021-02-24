#include "View.h"
#include "Exceptions.h"


CommandLineView::CommandLineView(GameState * state)
    : ViewInterface(state)
{}


void
CommandLineView::start_game()
{
    std::cout << "start game" << std::endl;
}


void
CommandLineView::enemy_move(std::string move)
{
    auto index = std::find_if(move.begin(), move.end(), [](auto c) { return c == ' '; });

    if (index == move.end()) {
        throw WrongTypeException();
    }

    auto color_count = index - move.begin();

    std::string color = move.substr(0, color_count);
    std::string type = move.substr(color_count + 1);

    std::cout << "Противник сделал ход"
              << ": цвет = " << color
              << ", тип карты = " << type
              << std::endl;
}


void
CommandLineView::move(Card card)
{
    std::cout << "our move" << std::endl;
}
