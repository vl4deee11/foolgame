#include "tree.cpp"

#ifndef TREE_FUNCS
#define TREE_FUNCS

struct Tree *newTreeNode(GameState *state);

void bfs(struct Tree *root);

void clear(struct Tree *node);

#endif
