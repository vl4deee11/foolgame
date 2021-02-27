#include "Node.h"

Node::Node(GameState *p_state, uint_fast8_t lvl) {
    level = lvl;
    state = p_state;
    children = std::vector<Node *>();
    points = std::vector<int>();
    parent = nullptr;
}

Node::~Node() {}

void
Node::add_children(Node *tree) {
    children.push_back(tree);
}

void
Node::add_point(int p) {
    points.push_back(p);
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