#include <assert.h>
#include <math.h>

#include "potion.h"

Potion* PotionCreate()
{
    Potion* potion = (Potion*)calloc(1, sizeof(Potion));
    if(!potion) return NULL;

    for(size_t i = 0; i < ATTRIBUTES_COUNT; i++)
    {
        potion->attributes[i] = 0;
    }

    PotionAddAttribute(potion, ATTRIBUTE_WATER, 10);
    return potion;
}
void PotionDestroy(Potion* potion)
{
    if(!potion) return;

    free(potion->attributes);
    free(potion);
}

void PotionClear(Potion* potion)
{
    assert(potion);

    for(size_t i = 0; i < ATTRIBUTES_COUNT; i++)
    {
        potion->attributes[i] = 0;
    }

    PotionAddAttribute(potion, ATTRIBUTE_WATER, 10);
}

void PotionAddAttribute(Potion* potion, Attribute attribute, size_t count)
{
    assert(potion);

    potion->attributes[attribute] += count;
}


int CalculateHealing(Potion* potion)
{
    assert(potion);

    int healing = potion->attributes[ATTRIBUTE_LIFE] - potion->attributes[ATTRIBUTE_PAIN];
    healing *= 1 + potion->attributes[ATTRIBUTE_FORCE];

    return healing;
}

int CalculateHeating(Potion* potion)
{
    assert(potion);

    int heating = (int)potion->attributes[ATTRIBUTE_HEAT] - (int)potion->attributes[ATTRIBUTE_COLD];
    heating *= 1 + (int)potion->attributes[ATTRIBUTE_FORCE];

    return heating;
}

double CalculateConcentration(Potion* potion)
{
    assert(potion);

    double summ = 0;
    for(size_t i = 0; i < ATTRIBUTES_COUNT; i++)
    {
        summ += potion->attributes[i];
    }

    return (summ - (double)potion->attributes[ATTRIBUTE_WATER])/summ;
}

double CalculatePurity(Potion* potion)
{
    assert(potion);

    double purity = 1;

    if(potion->attributes[ATTRIBUTE_HEAT] + potion->attributes[ATTRIBUTE_COLD] > 0)
        purity *= ((double)potion->attributes[ATTRIBUTE_HEAT] - (double)potion->attributes[ATTRIBUTE_COLD])/((double)potion->attributes[ATTRIBUTE_HEAT] + (double)potion->attributes[ATTRIBUTE_COLD]);
    if(potion->attributes[ATTRIBUTE_LIFE] + potion->attributes[ATTRIBUTE_PAIN] > 0)    
        purity *= ((double)potion->attributes[ATTRIBUTE_LIFE] - (double)potion->attributes[ATTRIBUTE_PAIN])/((double)potion->attributes[ATTRIBUTE_LIFE] + (double)potion->attributes[ATTRIBUTE_PAIN]);

    return abs(purity);
}

int CalculateStability(Potion* potion)
{
    assert(potion);

    return (int)potion->attributes[ATTRIBUTE_CALMNESS];
}