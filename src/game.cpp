#include <stdlib.h>
#include <assert.h>

#include "game.h"

Game* GameCreate()
{
    Game* game = (Game*)calloc(1, sizeof(Game));
    if(!game) return NULL;

    game->money = 1000;
    
    game->current_potion = 0;

    for(size_t i = 0; i < MAX_POTION; i++)
    {
        game->potion[i] = NULL;
    }

    for(size_t i = 0; i < MAX_ORDERS; i++)
    {
        Order* order = OrderCreate();
        if(!order) return NULL;

        game->orders[i] = order;
    }

    return game;
}

void GameDestroy(Game* game)
{
    if(!game) return;

    free(game);
}

void GameTick(Game* game)
{
    for(size_t i = 0; i < MAX_POTION; i++)
    {
        PotionTick(game->potion[i]);
    }

    assert(game);
}

Order* OrderCreate()
{
    Order* order = (Order*)calloc(1, sizeof(Order));
    if(!order)  return NULL;

    order->healing = rand() % (30 + 1) - 15;
    order->heating = rand() % (30 + 1) - 15;
    order->stability = rand() % (15 + 1);
    order->purity = (double)(rand() % (1000 + 1))/1000;
    order->concentration = (double)(rand() % (1000 + 1))/1000;
    order->concentration_more = rand() % 2;
    
    return order;
}

void OrderDestroy(Order* order)
{
    if(!order) return;

    free(order);
}