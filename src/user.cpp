#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "potion.h"
#include "user.h"
#include "game.h"
#include "colors.h"

#include "lib.h"

Game* game;

bool Init()
{
    printf(
        "______________________\n"
        "Welcome to Potion Lab!\n"
        "Enter help to get list of commands\n"
        "______________________\n"
    );

    game = GameCreate();
    if(!game) return false;
    
    return true;
}

bool Loop()
{
    char buffer[100] = {0};
    scanf("%99s", buffer);

    for(size_t i = 0 ; i < COMMANDS_COUNT; i++)
    {
        if(!strcmp(buffer, COMMANDS[i].command))
        {
            GameTick(game);
            return COMMANDS[i].func();
        }
    }

    printf("Command not exist\n");
    return true;
}


bool Exit()
{
    return false;
}

bool Add()
{
    if(!game->potion[game->current_potion])
    {
        printf("No potion on this maker\n");
        return true;
    }

    char buffer[100] = {0};
    scanf("%99[^\n]", buffer);

    for(size_t i = 0; i < INGRIDIENTS_COUNT; i++)
    {
        if(!lstrncmp(buffer + 1, INGRIDIENTS[i].name, strlen(INGRIDIENTS[i].name)))
        {
            for(size_t j = 0; j < INGRIDIENTS[i].attributes_count; j++)
            {
                PotionAddIngridientAttribute(game->potion[game->current_potion], INGRIDIENTS[i].attributes[j]); 
            }
            game->money -= (long)INGRIDIENTS[i].price;
            printf("Ingridient added. Money amount: %ld\n", game->money);
            return true;
        }
    }

    printf("Ingridient not found\n");

    return true;
}

bool Boil()
{
    if(!game->potion[game->current_potion])
    {
        printf("No potion on this maker\n");
        return true;
    }

    if(game->potion[game->current_potion]->attributes[ATTRIBUTE_WATER] > 0)
        game->potion[game->current_potion]->attributes[ATTRIBUTE_WATER]--;

    printf("Potion boiled\n");

    return true;
}

bool Wait()
{
    return true;
}

bool Stir()
{
    if(!game->potion[game->current_potion])
    {
        printf("No potion on pot!\n");
        return true;
    }

    for(size_t i = 0; i < 10; i++)
    {
        PotionTick(game->potion[game->current_potion]);
    }

    printf("Stired\n");
    return true;
}

bool Start()
{
    if(game->potion[game->current_potion])
    {
        printf("Current potion not finished!\n");
        return true;
    }
    else
    {
        game->potion[game->current_potion] = PotionCreate();
        printf("New potion created\n");
        return (game->potion[game->current_potion]);
    }
}

bool Change()
{
    size_t new_maker = 0;
    scanf("%lu", &new_maker);

    if(new_maker < MAX_POTION)
    {
        game->current_potion = new_maker;

        printf("Pot changed\n");
        return true;
    }

    printf("Incorrect number\n");
    return true;
}

bool Filter()
{
    if(!game->potion[game->current_potion])
    {
        printf("No potion on this pot\n");
        return true;
    }


    game->potion[game->current_potion]->ingridient_attributes_count = 0;
    free(game->potion[game->current_potion]->ingridient_attributes);
    game->potion[game->current_potion]->ingridient_attributes = 
                                    (Ingridient_attribute*)calloc(1, sizeof(Ingridient_attribute));

    printf("Potion filtered\n");

    return true;
}

bool Finish()
{
    if(!game->potion[game->current_potion])
    {
        printf("No potion on this pot\n");
        return true;
    }

    printf(
        "________________\n"
        "Potion finished!\n"
        "Condition:\n"
    );

    int healing = CalculateHealing(game->potion[game->current_potion]);
    int heating = CalculateHeating(game->potion[game->current_potion]);
    double concentration = CalculateConcentration(game->potion[game->current_potion]);
    double purity = CalculatePurity(game->potion[game->current_potion]);
    int stablility = CalculateStability(game->potion[game->current_potion]);

    if(healing > 0)
    {
        printf("Healing: %d\n", healing);
    }
    else if(healing < 0)
    {
        printf("Toxicity: %d\n", -healing);
    }

    if(heating > 0)
    {
        printf("Hotness: %d\n", heating);
    }
    else if(heating < 0)
    {
        printf("Coldness: %d\n", -heating);
    }

    printf("Concentration: %g\n", concentration);
    printf("Purity: %g\n", purity);
    printf("Stability: %d\n", stablility);

    printf(
        "________________\n"
    );

    PotionDestroy(game->potion[game->current_potion]);
    game->potion[game->current_potion] = NULL;

    return true;
}

bool Help()
{
    printf( 
        "______________________\n"
        "Commands:\n"
        "help               -- get list of instructions\n"
        "h ingridients      -- get list of ingridients\n"
        "h actions          -- get list of all actions\n"
        "exit               -- leave programm\n"
        "______________________\n"
        );
    return true;
}

bool H()
{
    char buffer[100] = {0};
    scanf("%99[^\n]", buffer);

    if(!strcmp(buffer + 1, "ingridients"))
    {
        printf(
            "____________\n"
            "Ingridients:\n"
            "Water              1$\n"
            "Glowcap mushroom   4$\n"
            "Whichmint          3$\n"
            "Sunspice           7$\n"
            "Ember moss         2$\n"
            "Wolf's horn        10$\n"
            "____________\n"
        );
    }
    else if(!strcmp(buffer + 1, "actions"))
    {
        printf(
            "____________\n"
            "Actions:\n"
            "change *0-4*       -- change potion maker\n"
            "start              -- start new potion\n"
            "add *ingridient*   -- add ingridiend to potion\n"
            "boil               -- boil potion\n"  
            "wait               -- wait for one tick\n"
            "stir               -- stir potion\n" 
            "filter             -- filter potion\n"
            "finish             -- finish potion and start new\n"
            "____________\n"
        );
    }
    else
    {
        printf("Table not found\n");
    }
    return true;    
}

