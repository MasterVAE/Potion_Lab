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
bool Close();
bool Orders();
bool Help();
bool H();

struct Command
{
    char command[100];
    char command_short[100];
    bool (*func)(void);
};

static Command COMMANDS[] = 
{
    {"exit", "exit",    Exit},
    {"add", "+",        Add},
    {"boil", "b",       Boil},
    {"wait", "w",       Wait},
    {"stir", "s",       Stir},
    {"start", "st",     Start},
    {"change", "->",    Change},
    {"finish", "=",     Finish},
    {"filter", "f",     Filter},
    {"close", "c",      Close},
    {"orders","o",      Orders},
    {"help", "help",    Help},
    {"h", "h",          H}
};

static const size_t COMMANDS_COUNT = sizeof(COMMANDS)/sizeof(COMMANDS[0]);



#endif //USER_H