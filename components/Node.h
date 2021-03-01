#ifndef FOOLGAME_NODE_H
#define FOOLGAME_NODE_H

#include <vector>
#include "GameState.h"
#include "Card.h"

class Node {
public:
    Node(GameState *p_state, uint_fast8_t lvl, Node * parent,
         Card * card, std::list<Card *> * hand, std::list<Node *> * children);

    ~Node();

    void
    add_children(Node *tree);

    void
    add_estimation(float p);

    GameState state;
    uint_fast8_t level;
    Node *parent;
    Card *card;
    std::list<Card *> hand;
    std::list<Node *> children;
    float max_estimation;
    float min_estimation;
};

#endif //FOOLGAME_NODE_H
