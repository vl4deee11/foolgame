#include <deque>
#include<algorithm>
#include <map>
#include "UnoBot.h"
#include "Node.h"


UnoBot::UnoBot(GameState *state)
        : state(state) {
    take_cards(state->get_card_in_hand());
}

Card *
UnoBot::make_move() {
    auto opponent_cards = get_opponent_cards();
    Node *root = new Node(state, 0);

    std::deque<Node *> dq;
    //  prediction_root initialization from hand
    for (auto card : hand) {
        if (can_move(card)) {
            dq.push_back(create_new_node(root, state, card, &hand));
        }
    }

    std::deque<Node *> leafs;
    while (!dq.empty()) {
        Node *node = dq.back();
        dq.pop_back();
        if (node->level == 3) {
            leafs.push_back(node);
            continue;
        }
        bool is_leaf = true;
        for (auto card : node->level == 1 ? opponent_cards : node->parent->hand) {
            if (can_move(card, node->state)) {
                is_leaf = false;
                dq.push_back(create_new_node(node, node->state, card, &node->parent->hand));
            }
        }
        if (is_leaf) leafs.push_back(node);
    }

    std::map<int, Node *> estimation_to_node;
    while (!leafs.empty()) {
        Node *node = leafs.front();
        leafs.pop_front();
        if (node->parent != nullptr) {
            if (node->children.empty()) {
                // TODO: call a heuristic function here (now use [rand()])
                auto e = (node->level & 1) != 0 ? rand() : -rand();
                estimation_to_node[e] = node;
                node->parent->add_estimation(e);
            } else if ((node->level & 1) != 0) estimation_to_node[node->max_estimation] = node;
            else estimation_to_node[node->min_estimation] = node;

            node->parent->add_estimation(node->max_estimation);
            node->parent->add_estimation(node->min_estimation);

            leafs.push_back(node->parent);
        }
    }

    if (!estimation_to_node.contains(root->max_estimation)) {
        clear(root);
        return nullptr;
    }

    auto best_node = estimation_to_node[root->max_estimation];
    Card *result_card = nullptr;
    if (best_node != nullptr) {
        result_card = best_node->card;
    }

    clear(root);
    return result_card;
}

bool
UnoBot::empty() const {
    return hand.empty();
}

void
UnoBot::take_cards(size_t count) {
    for (int i = 0; i < count; ++i)
        hand.push_back(state->get_next_card());
}

bool
UnoBot::can_move(Card *card, GameState *p_state) {
    if (p_state == nullptr) p_state = state;
    auto top_card = p_state->get_top_card();

    return card->has_color(UNO::color_t::BLACK)
           || top_card->has_color(card->get_color())
           || top_card->has_type(card->get_type());
}


std::list<Card *> *
UnoBot::get_hand() {
    return &hand;
}

std::set<Card *>
UnoBot::get_hand_set() {
    std::set<Card *> s;
    for (Card *card : *get_hand()) {
        s.insert(card);
    }
    return s;
}

std::list<Card *>
UnoBot::get_opponent_cards() {
    std::list<Card *> r;
    auto hand_set = get_hand_set();
    auto all_cards = state->get_all_cards();
    auto current_deck = state->get_current_deck();
    auto discard_deck = state->get_discard_deck();

    for (Card *c : all_cards) {
        auto not_in_current = !current_deck.contains(c);
        auto not_in_discard = !discard_deck.contains(c);
        auto not_in_hand = !hand_set.contains(c);
        auto not_top_card = c != state->get_top_card();
        if (not_in_current && not_in_discard && not_in_hand && not_top_card) {
            r.push_back(c);
        }
    }
    return r;
}


Node *
UnoBot::create_new_node(Node *parent, GameState *p_state, Card *card, std::list<Card *> *l_hand) {
    auto curr_state = new GameState(*p_state);
    curr_state->deck = state->deck->make_copy();
    curr_state->set_top_card(card);

    Node *node = new Node(curr_state, parent->level + 1);
    node->card = card;
    node->parent = parent;
    node->hand = *l_hand;
    node->hand.remove(card);

    parent->add_children(node);
    return node;
}