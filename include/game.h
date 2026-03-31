#ifndef GAME_H
#define GAME_H

#include <stdlib.h>

#include "potion.h"

static const size_t MAX_POTION = 5;
static const size_t MAX_ORDERS = 3;

struct Order
{
    int healing;
    int heating;
    double purity;
    int stability;
    double concentration;
    bool concentration_more;
};

struct Game
{
    long money;
    
    size_t current_potion;
    Potion* potion[MAX_POTION];

    Order* orders[MAX_ORDERS];
};

Game* GameCreate();
void GameDestroy(Game* game);

Order* OrderCreate();
void OrderDestroy(Order* order);

void GameTick(Game* game);

#endif //GAME_H