#include "Predictor.h"
#include "UnoBot.h"

Predictor::Predictor(UnoBot * bot) : bot(bot) {}

Card *Predictor::predict_best_move() {
    Card * best = nullptr;

    /// TODO: реализовать выбор карты
    for (auto card : *bot->get_hand()) {
        if (bot->can_move(card)) {
            best = card;
        }
    }

    /// TODO: реализовать выбор следующего цвета
    if (!bot->get_hand()->empty() && best != nullptr)
        best->set_next_color(bot->get_hand()->front()->get_color());

    return best;
//    auto opponent_cards = get_opponent_cards();
//    Node *root = new Node(state, 0, nullptr, state->get_top_card(), nullptr, nullptr);
//
//    std::deque<Node *> dq;
//    //  prediction_root initialization from hand
//    for (auto card : hand) {
//        if (can_move(card)) {
//            dq.push_back(new Node(state, root->level + 1, root, card, &hand, nullptr));
//        }
//    }
//
//    std::deque<Node *> leafs;
//    while (!dq.empty()) {
//        Node *node = dq.back();
//        dq.pop_back();
//        if (node->level == 3) {
//            leafs.push_back(node);
//            continue;
//        }
//        bool is_leaf = true;
//        for (auto card : node->level == 1 ? opponent_cards : node->parent->hand) {
//            if (can_move(card, &node->state)) {
//                is_leaf = false;
////                dq.push_back(create_new_node(node, &node->state, card, &node->parent->hand));
//                dq.push_back(new Node(&node->state, node->level + 1, node, card,
//                                         &node->parent->hand, nullptr));
//            }
//        }
//        if (is_leaf) leafs.push_back(node);
//    }
//
//    std::map<float, Node *> estimation_to_node;
//    while (!leafs.empty()) {
//        Node *node = leafs.front();
//        leafs.pop_front();
//        if (node->parent != nullptr) {
//            if (node->children.empty()) {
//                // TODO: call a heuristic function here (now use [rand()])
//                float e = (node->level & 1) != 0 ? heuristics_estimation(node) : -heuristics_estimation(node);
//                estimation_to_node[e] = node;
//                node->parent->add_estimation(e);
//                continue;
//            } else if ((node->level & 1) != 0) {
//                estimation_to_node[node->max_estimation] = node;
//                node->parent->add_estimation(node->max_estimation);
//            } else {
//                estimation_to_node[node->min_estimation] = node;
//                node->parent->add_estimation(node->min_estimation);
//            }
//
//            leafs.push_back(node->parent);
//        }
//    }
//
//    if (!estimation_to_node.contains(root->max_estimation)) {
//        float max = 0;
//        Card *best_card = nullptr;
//        for (auto child : root->children) {
//            if (child->max_estimation > max) {
//                max = child->max_estimation;
//                best_card = child->card;
//            }
//        }
//        delete root;
//
//        this->hand.remove(best_card);
//        return best_card;
//    }
//
//    auto best_node = estimation_to_node[root->max_estimation];
//    Card *best_card = nullptr;
//    if (best_node != nullptr) {
//        best_card = best_node->card;
//    }
//
//    delete root;
//
//    this->hand.remove(best_card);
//    return best_card;
}
