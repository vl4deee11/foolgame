#include "Node.h"

Node::Node(GameState *p_state, uint_fast8_t lvl, Node * parent,
           Card * card, std::list<Card *> * hand, std::list<Node *> * children
)   : level(lvl), state(*p_state), parent(parent), card(card)
    , max_estimation(std::numeric_limits<float>::min())
    , min_estimation(std::numeric_limits<float>::max())
{
    if (hand) this->hand = *hand;
    if (children) this->children = *children;
    if (parent) parent->add_children(this);

    this->hand.remove(card);

    state.deck = p_state->deck->make_copy();
    state.set_top_card(card);
}

Node::~Node() {
    for (auto n : children) {
        delete n;
    }
}

void
Node::add_children(Node *tree) {
    children.push_back(tree);
}

void
Node::add_estimation(float p) {
    max_estimation = std::max(max_estimation, p);
    min_estimation = std::min(min_estimation, p);
}

//void
//clear(struct Node *node) {
//    if (node != nullptr) {
//        for (auto n : node->children) {
//            clear(n);
//        }
//        delete node;
//    }
//}