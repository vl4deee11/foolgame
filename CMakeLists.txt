cmake_minimum_required(VERSION 3.17)
project(foolgame)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        foolgame main.cpp
        components/UnoBot.cpp components/UnoBot.h
        components/Deck.cpp components/Deck.h
        components/Card.cpp components/Card.h
        components/GameState.cpp components/GameState.h
        components/UnoRules.h components/Exceptions.h
        components/UnoGameEngine.cpp components/UnoGameEngine.h
        components/Node.cpp components/Node.h
        components/Heuristics.cpp components/Heuristics.h
        components/Predictor.cpp components/Predictor.h)