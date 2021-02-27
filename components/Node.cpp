#include "Node.h"

Node::Node(GameState *p_state, uint_fast8_t lvl) {
    level = lvl;
    state = p_state;
    parent = nullptr;
}

Node::~Node() {}

void
Node::add_children(Node *tree) {
    children.push_back(tree);
}

void
Node::add_estimation(int p) {
    max_estimation = std::max(max_estimation, p);
    min_estimation = std::min(min_estimation, p);
}

void
clear(struct Node *node) {
    if (node != nullptr) {
        for (auto n : node->children) {
            clear(n);
        }
        delete node;
    }
}