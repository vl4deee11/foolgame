#include <iostream>
#include "tree/structs.h"
#include "tree/funcs.h"
#include "state/structs.h"

void someCallBack(struct GameState *s) {
    if (s != nullptr) {
        cout << s->data << " ";
    }
}

int main() {
    // only for example
    GameState *s = new GameState;
    s->data = 'C';
    Tree *root = newTreeNode(s);
    bfs(root, someCallBack);
    clear(root);
    return 0;
}

