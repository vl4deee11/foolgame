#include "Model.h"


UnoModel::UnoModel(GameState * state, const size_t player_count)
    : ModelInterFace(state), player_count(player_count)
{}
