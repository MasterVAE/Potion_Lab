#ifndef GAME_H
#define GAME_H

#include <stdlib.h>

#include "potion.h"

static const size_t MAX_POTION = 5;

struct Game
{
    long money;
    
    size_t current_potion;
    Potion* potion[MAX_POTION];
};

Game* GameCreate();
void GameDestroy(Game* game);

void GameTick(Game* game);

#endif //GAME_H