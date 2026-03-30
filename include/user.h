#ifndef USER_H
#define USER_H

#include <stdlib.h>

bool Init();
bool Loop();

bool Exit();
bool Add();
bool Boil();
bool Wait();
bool Stir();
bool Start();
bool Change();
bool Filter();
bool Finish();
bool Help();
bool H();

struct Command
{
    char command[100];
    bool (*func)(void);
};

static Command COMMANDS[] = 
{
    {"exit",    Exit},
    {"add",     Add},
    {"boil",    Boil},
    {"wait",    Wait},
    {"stir",    Stir},
    {"start",   Start},
    {"change",  Change},
    {"finish",  Finish},
    {"filter",  Filter},
    {"help",    Help},
    {"h",       H}
};

static const size_t COMMANDS_COUNT = sizeof(COMMANDS)/sizeof(COMMANDS[0]);



#endif //USER_H