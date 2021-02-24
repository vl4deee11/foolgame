#ifndef FOOLGAME_MODEL_H
#define FOOLGAME_MODEL_H


#include <cstdio>
#include "GameState.h"


class ModelInterFace {
public:
    explicit ModelInterFace(GameState * state) : state(state) {};

private:
    GameState * state;
};


class UnoModel : public ModelInterFace {
public:
    explicit UnoModel(GameState * state, size_t player_count = 2);

private:
    const size_t player_count;
};


#endif //FOOLGAME_MODEL_H
