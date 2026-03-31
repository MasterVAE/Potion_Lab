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
        BOLD GREEN "Welcome to Potion Lab!\n"
        "Enter help to get list of commands\n" CLEAR
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
        if(!strcmp(buffer, COMMANDS[i].command) || !strcmp(buffer, COMMANDS[i].command_short))
        {
            GameTick(game);
            return COMMANDS[i].func();
        }
    }

    printf(RED "Command not exist\n" CLEAR);
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
        printf(RED "No potion on this maker\n" CLEAR);
        return true;
    }

    if(game->potion[game->current_potion]->finished)
    {
        printf(RED "Potion finished\n" CLEAR);
        return true;
    }

    char buffer[100] = {0};
    scanf("%99[^\n]", buffer);

    for(size_t i = 0; i < INGRIDIENTS_COUNT; i++)
    {
        if(!lstrncmp(buffer + 1, INGRIDIENTS[i].name, strlen(INGRIDIENTS[i].name)) ||
           !lstrncmp(buffer + 1, INGRIDIENTS[i].name_short, strlen(INGRIDIENTS[i].name_short)))
        {
            for(size_t j = 0; j < INGRIDIENTS[i].attributes_count; j++)
            {
                PotionAddIngridientAttribute(game->potion[game->current_potion], INGRIDIENTS[i].attributes[j]); 
            }
            game->money -= (long)INGRIDIENTS[i].price;
            printf("Ingridient added. Money amount: " YELLOW "%ld$\n" CLEAR, game->money);
            return true;
        }
    }

    printf(RED "Ingridient not found\n" CLEAR);

    return true;
}

bool Boil()
{
    if(!game->potion[game->current_potion])
    {
        printf(RED "No potion on this maker\n" CLEAR);
        return true;
    }

    if(game->potion[game->current_potion]->finished)
    {
        printf(RED "Potion finished\n" CLEAR);
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
        printf(RED "No potion on pot!\n" CLEAR);
        return true;
    }

    if(game->potion[game->current_potion]->finished)
    {
        printf(RED "Potion finished\n" CLEAR);
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
        PotionDestroy(game->potion[game->current_potion]);
    }

    game->potion[game->current_potion] = PotionCreate();
    printf("New potion created\n");
    return (game->potion[game->current_potion]);
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

    printf(RED "Incorrect number\n" CLEAR);
    return true;
}

bool Filter()
{
    if(!game->potion[game->current_potion])
    {
        printf(RED "No potion on this pot\n" CLEAR);
        return true;
    }

    if(game->potion[game->current_potion]->finished)
    {
        printf(RED "Potion finished\n" CLEAR);
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
        printf(RED "No potion on this pot\n" CLEAR);
        return true;
    }

    game->potion[game->current_potion]->finished = true;

    printf(
        "________________\n"
        BOLD GREEN "Potion finished!\n"
        "Condition:\n" CLEAR
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

    

    return true;
}

bool Help()
{
    printf( 
        "______________________\n"
        BOLD GREEN "Commands:\n" CLEAR
        "help               -- get list of instructions\n"
        "h ingridients/i    -- get list of ingridients\n"
        "h actions/a        -- get list of all actions\n"
        "orders/o           -- get list of current orders\n"
        "exit               -- leave programm\n"
        "______________________\n"
        );
    return true;
}

bool H()
{
    char buffer[100] = {0};
    scanf("%99[^\n]", buffer);

    if(!strcmp(buffer + 1, "ingridients") || !strcmp(buffer + 1, "i"))
    {
        printf(
            "____________\n"
            BOLD GREEN "Ingridients:\n" CLEAR
            "Water/wt            " YELLOW "1$\n" CLEAR
            "Glowcap mushroom/gm " YELLOW "4$\n" CLEAR
            "Whichmint/wm        " YELLOW "3$\n" CLEAR
            "Sunspice/ss         " YELLOW "7$\n" CLEAR
            "Ember moss/em       " YELLOW "2$\n" CLEAR
            "Wolf's horn/wh      " YELLOW "10$\n" CLEAR
            "____________\n"
        );
    }
    else if(!strcmp(buffer + 1, "actions") || !strcmp(buffer + 1, "a"))
    {
        printf(
            "____________\n"
            BOLD GREEN "Actions:\n" CLEAR
            "change/-> *0-4*    -- change potion maker\n"
            "start/st           -- start new potion\n"
            "add/+ *ingridient* -- add ingridiend to potion\n"
            "boil/b             -- boil potion\n"  
            "wait/w             -- wait for one tick\n"
            "stir/s             -- stir potion\n" 
            "filter/f           -- filter potion\n"
            "finish/=           -- finish potion and start new\n"
            "close/c *0-2*      -- close order\n"       
            "____________\n"
        );
    }
    else
    {
        printf("Table not found\n");
    }
    return true;    
}

bool Orders()
{
    printf(
        "____________________\n"
        BOLD GREEN "Orders:\n" CLEAR
        );
    for(size_t i = 0; i < MAX_ORDERS; i++)
    {
        printf(GREEN "Order %lu\n" CLEAR, i);
        Order* order = game->orders[i];

        if(order->healing > 0)  printf("Healing at least %d\n", order->healing);
        else if(order->healing < 0) printf("Toxicity at least %d\n", -order->healing);

        if(order->heating > 0)  printf("Hotness at least %d\n", order->heating);
        else if(order->heating < 0) printf("Coldness at least %d\n", -order->heating);

        printf("Purity at least %g\n", order->purity);

        if(order->concentration_more) printf("Concentration at least %g\n", order->concentration);
        else printf("Concentration no more %g\n", order->concentration);

        printf("Stability at least %d\n", order->stability);
    }
    printf("____________________\n");
    return true;
}

bool Close()
{
    size_t order_num = 0;
    scanf("%lu", &order_num);

    if(order_num > MAX_ORDERS)
    {
        printf(RED "No such order\n" CLEAR);
        return true;
    }  
    
    Order* order = game->orders[order_num];
    Potion* potion = game->potion[game->current_potion];

    int healing = CalculateHealing(potion);
    int heating = CalculateHeating(potion);
    double concentration = CalculateConcentration(potion);
    double purity = CalculatePurity(potion);
    int stablility = CalculateStability(potion);

    if(order->healing > 0 && order->healing > healing)
    {
        printf("Not enough healing\n");
        return true;
    }

    if(order->healing < 0 && order->healing < healing)
    {
        printf("Not enough toxicity\n");
        return true;
    }

    if(order->heating > 0 && order->heating > heating)
    {
        printf("Not enough hotness\n");
        return true;
    }

    if(order->heating < 0 && order->heating < heating)
    {
        printf("Not enough coldness\n");
        return true;
    }

    if(order->purity > purity)
    {
        printf("Not enough purity\n");
        return true;
    }

    if(order->concentration_more)
    {
        if(order->concentration > concentration)
        {
            printf("Not enough concentration\n");
            return true;
        }
    }
    else
    {
        if(order->concentration < concentration)
        {
            printf("Too much concentration\n");
            return true;
        }
    }

    if(order->stability > stablility)
    {
        printf("Not enough stability\n");
        return true;
    }

    printf(GREEN "Order closed!\n" CLEAR);
    game->money += 100;

    OrderDestroy(order);
    game->orders[order_num] = OrderCreate();
    return true;
}

