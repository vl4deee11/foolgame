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

    std::map<int, Node *> points_to_node;
    while (!leafs.empty()) {
        Node *node = leafs.front();
        leafs.pop_front();
        if (node->parent != nullptr) {
            if (node->children.empty()) {
                // TODO: call a heuristic function here
                auto p = (node->level & 1) != 0 ? rand() : -rand();
                points_to_node[p] = node;
                node->parent->add_point(p);
            } else if ((node->level & 1) != 0) {
                auto max = std::max_element(node->points.begin(), node->points.end());
                points_to_node[*max] = node;
                node->parent->add_point(*max);
            } else {
                auto min = std::min_element(node->points.begin(), node->points.end());
                points_to_node[*min] = node;
                node->parent->add_point(*min);
            }
            leafs.push_back(node->parent);
        }
    }

    if (root->points.empty()) {
        clear(root);
        return nullptr;
    }

    auto max = std::max_element(root->points.begin(), root->points.end());
    auto best_node = points_to_node[*max];
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
UnoBot::can_move(Card *card) {
    auto top_card = state->get_top_card();

    return card->has_color(UNO::color_t::BLACK)
           || top_card->has_color(card->get_color())
           || top_card->has_type(card->get_type());
}

bool
UnoBot::can_move(Card *card, GameState *p_state) {
    auto top_card = p_state->get_top_card();

    // TODO:handle black cards
    if (card->get_color() == UNO::color_t::BLACK) return false;

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
    node->hand = std::list<Card *>(*l_hand);
    node->hand.remove_if([card](auto n_card) { return n_card == card; });

    parent->add_children(node);
    return node;
}