cmake_minimum_required(VERSION 3.17)
project(foolgame)

set(CMAKE_CXX_STANDARD 20)

add_executable(foolgame main.cpp
        components/UnoBot.cpp components/UnoBot.h
        components/Deck.cpp components/Deck.h
        components/Card.cpp components/Card.h
#        components/Model.cpp components/Model.h
#        components/View.cpp components/View.h
#        components/Controller.cpp components/Controller.h
        components/GameState.cpp components/GameState.h
        components/UnoRules.h components/Exceptions.h
        components/UnoGameEngine.cpp components/UnoGameEngine.h)