#ifndef FOOLGAME_NODE_H
#define FOOLGAME_NODE_H

#include <vector>
#include "GameState.h"
#include "Card.h"

struct Node {
    Node(GameState *p_state, uint_fast8_t lvl);

    ~Node();

    void
    add_children(Node *tree);

    void
    add_estimation(int p);

    uint_fast8_t level;
    GameState *state;
    Node *parent;
    Card *card;
    int max_estimation;
    int min_estimation;
    std::list<Card *> hand;
    std::list<Node *> children;
};

void
clear(struct Node *node);

#endif //FOOLGAME_NODE_H
