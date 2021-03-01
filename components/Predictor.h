#ifndef FOOLGAME_PREDICTOR_H
#define FOOLGAME_PREDICTOR_H

#include "Card.h"


class UnoBot;


class Predictor {
public:
    explicit
    Predictor(UnoBot *);

    Card *
    predict_best_move();

private:
    UnoBot * bot;
};


#endif //FOOLGAME_PREDICTOR_H
