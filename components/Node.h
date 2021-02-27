#ifndef FOOLGAME_NODE_H
#define FOOLGAME_NODE_H

#include <vector>
#include "GameState.h"
#include "Card.h"

struct Node {
    explicit
    Node(GameState *p_state, uint_fast8_t lvl);

    void
    add_children(Node *tree);

    void
    add_point(int p);

    uint_fast8_t level;
    GameState *state;
    Node *parent;
    Card *card;
    std::list<Card *> hand;
    std::vector<Node *> children;
    std::vector<int> points;
};

void
clear(struct Node *node);

#endif //FOOLGAME_NODE_H
