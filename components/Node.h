#ifndef FOOLGAME_NODE_H
#define FOOLGAME_NODE_H

#include <vector>
#include "GameState.h"
#include "Card.h"

struct Node {
    explicit Node(GameState *p_state, uint_fast8_t lvl);

    void add_children(Node *tree);

    uint_fast8_t level;
    GameState *state;
    Node *parent;
    std::list<Card *> hand;
    std::vector<Node *> children;

};

#endif //FOOLGAME_NODE_H
