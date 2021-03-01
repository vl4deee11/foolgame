#include <map>
#include <set>
#include "Node.h"

float
heuristics_estimation(Node *node) {
    if (node->hand.empty()) return 10000.0;
    long diff_count = node->parent != nullptr ? -(node->hand.size() - node->parent->hand.size()) : node->hand.size();
    std::set<Card *> curr_desk = node->state.get_current_deck();
    std::map<UNO::color_t, float> color_freq;

    for (auto card : curr_desk) {
        if (color_freq.contains(card->get_color())) color_freq[card->get_color()]++;
        else color_freq[card->get_color()] = 1;
    }
    for (auto k : color_freq) {
        color_freq[k.first] /= curr_desk.size();
    }

    UNO::color_t card_color = node->card->get_color();
    int cards_count_with_color = 0;
    for (auto card : node->hand) {
        if (card->get_color() == card_color) ++cards_count_with_color;
    }

    int cards_count_with_color_for_opponent = 0;
    for (auto card : node->parent->hand) {
        if (card->get_color() == card_color) ++cards_count_with_color_for_opponent;
    }

    int diff_curr_color = cards_count_with_color - cards_count_with_color_for_opponent;
    float freq = color_freq[card_color];
    float freq_black = color_freq.contains(UNO::color_t::BLACK) ? color_freq[UNO::color_t::BLACK] : 0;
    if (diff_curr_color > 0) {
        return float(diff_curr_color) - (freq + freq_black) + float(diff_count);
    }

    return float(diff_curr_color) + (freq + freq_black) + float(diff_count);
}

