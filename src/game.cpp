#include <stdlib.h>
#include <assert.h>

#include "game.h"

Game* GameCreate()
{
    Game* game = (Game*)calloc(1, sizeof(Game));
    if(!game) return NULL;

    game->money = 0;
    
    game->current_potion = 0;

    for(size_t i = 0; i < MAX_POTION; i++)
    {
        game->potion[i] = NULL;
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