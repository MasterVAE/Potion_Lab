#ifndef INGRIDIENTS_H
#define INGRIDIENTS_H

#include <stdlib.h>

enum Attribute
{
    ATTRIBUTE_WATER,
    ATTRIBUTE_FORCE,
    ATTRIBUTE_LIFE,
    ATTRIBUTE_PAIN,
    ATTRIBUTE_HEAT,
    ATTRIBUTE_COLD,
    ATTRIBUTE_CALMNESS,
    ATTRIBUTES_COUNT
};

struct Ingridient_attribute
{
    Attribute attribute;
    size_t ticks_amount;
};

struct Ingridient
{
    char name[100];

    size_t price;
    size_t attributes_count;
    Ingridient_attribute attributes[10];
};

static const Ingridient INGRIDIENTS[]
{
    {"water",               1, 5,   {
                                    {ATTRIBUTE_WATER, 0}, 
                                    {ATTRIBUTE_WATER, 0},
                                    {ATTRIBUTE_WATER, 0},
                                    {ATTRIBUTE_WATER, 0},
                                    {ATTRIBUTE_WATER, 0}
                                    }},
    {"glowcap mushroom",    4, 4,   {
                                    {ATTRIBUTE_PAIN, 10}, 
                                    {ATTRIBUTE_PAIN, 30},
                                    {ATTRIBUTE_COLD, 5},
                                    {ATTRIBUTE_CALMNESS, 60}
                                    }},
    {"whichmint",           3, 3,   {
                                    {ATTRIBUTE_CALMNESS, 5},
                                    {ATTRIBUTE_CALMNESS, 10},
                                    {ATTRIBUTE_COLD, 2}
                                    }},
    {"sunspice",            7, 5,   {
                                    {ATTRIBUTE_HEAT, 10},
                                    {ATTRIBUTE_HEAT, 10},
                                    {ATTRIBUTE_HEAT, 10},
                                    {ATTRIBUTE_LIFE, 50},
                                    {ATTRIBUTE_CALMNESS, 40}
                                    }},
    {"ember moss",          2, 2,   {
                                    {ATTRIBUTE_COLD, 50},
                                    {ATTRIBUTE_COLD, 50}
                                    }},
    {"wolf's horn",         10, 4,  {
                                    {ATTRIBUTE_FORCE, 5},
                                    {ATTRIBUTE_FORCE, 5},
                                    {ATTRIBUTE_LIFE, 10},
                                    {ATTRIBUTE_PAIN, 15}
                                    }}
};

static const size_t INGRIDIENTS_COUNT = sizeof(INGRIDIENTS)/sizeof(INGRIDIENTS[0]);

#endif // INGRIDIENTS_H