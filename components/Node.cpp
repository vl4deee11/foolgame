
#include "Node.h"

Node
::Node(GameState *p_state, uint_fast8_t lvl) {
    level = lvl;
    state = p_state;
    children = std::vector<Node *>();
    parent = nullptr;
}

void
Node::add_children(Node *tree) {
    children.push_back(tree);
}
