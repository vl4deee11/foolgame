#include <iostream>
#include <deque>

using namespace std;

void clear(struct Tree *node) {
    if (node != nullptr) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

struct Tree *newTreeNode(struct GameState *state) {
    Tree *node = new Tree;
    node->data = state;
    node->left = nullptr;
    node->right = nullptr;
    node->parent = nullptr;

    return node;
}

/*
 * Breath first search, with callback
 */
void bfs(Tree *root, void callback(GameState *state)) {
    if (root == nullptr) return;
    deque<Tree *> queue;
    queue.push_back(root);

    while (!queue.empty()) {
        Tree *p = queue.front();
        // TODO: make some logic
        callback(p->data);
        queue.pop_front();

        if (p->left != nullptr)
            queue.push_back(p->left);
        if (p->right != nullptr)
            queue.push_back(p->right);
    }
}