#include "../state/structs.h"
#ifndef TREE_STRUCTS
#define TREE_STRUCTS
struct Tree {
    GameState *data;
    Tree *left;
    Tree *right;
    Tree *parent;
};
#endif
