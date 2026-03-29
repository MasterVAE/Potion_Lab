#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "potion.h"
#include "user.h"

#include "lib.h"

size_t CURRENT_POTION = 0;
static const size_t MAX_POTION = 5;

Potion* potion[] = {NULL};


bool Init()
{
    printf(
        "______________________\n"
        "Welcome to Potion Lab!\n"
        "Enter help to get list of commands\n"
        "______________________\n"
    );
    
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
            return COMMANDS[i].func();
        }
    }

    return true;
}


bool Exit()
{
    return false;
}

bool Add()
{

    if(!potion[CURRENT_POTION])
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
                PotionAddAttribute(potion[CURRENT_POTION], INGRIDIENTS[i].attributes[j], 1); 
            }
            printf("Ingridient added\n");
            return true;
        }
    }

    printf("Ingridient not found\n");

    return true;
}

bool Start()
{
    if(potion[CURRENT_POTION])
    {
        printf("Current potion not finished!\n");
        return true;
    }
    else
    {
        potion[CURRENT_POTION] = PotionCreate();
        printf("New potion created\n");
        return (potion[CURRENT_POTION]);
    }
}
bool Change()
{
    size_t new_maker = 0;
    scanf("%lu", &new_maker);

    if(new_maker < MAX_POTION)
    {
        CURRENT_POTION = new_maker;

        printf("Maker changed\n");
        return true;
    }

    printf("Incorrect number\n");
    return true;
}

bool Finish()
{
    if(!potion[CURRENT_POTION])
    {
        printf("No potion on this potion maker\n");
        return true;
    }

    printf(
        "________________\n"
        "Potion finished!\n"
        "Condition:\n"
    );

    int healing = CalculateHealing(potion[CURRENT_POTION]);
    int heating = CalculateHeating(potion[CURRENT_POTION]);
    double concentration = CalculateConcentration(potion[CURRENT_POTION]);
    double purity = CalculatePurity(potion[CURRENT_POTION]);
    int stablility = CalculateStability(potion[CURRENT_POTION]);

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

    potion[CURRENT_POTION] = NULL;

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
            "Water\n"
            "Glowcap mushroom\n"
            "Whichmint\n"
            "Sunspice\n"
            "Ember moss\n"
            "Wolf's horn\n"
            "____________\n"
        );
    }
    else if(!strcmp(buffer + 1, "actions"))
    {
        printf(
            "____________\n"
            "Actions:\n"
            "change *number*    -- change potion maker\n"
            "start              -- start new potion\n"
            "add *ingridient*   -- add ingridiend to potion\n"
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