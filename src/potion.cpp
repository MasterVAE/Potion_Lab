#include <assert.h>
#include <math.h>

#include "potion.h"

Potion* PotionCreate()
{
    Potion* potion = (Potion*)calloc(1, sizeof(Potion));
    if(!potion) return NULL;

    potion->ingridient_attributes_count = 0;
    potion->ingridient_attributes = (Ingridient_attribute*)calloc(1, sizeof(Ingridient_attribute));
    if(!potion->ingridient_attributes)
    {
        free(potion);
        return NULL;
    }

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

    free(potion->ingridient_attributes);
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

void PotionAddIngridientAttribute(Potion* potion, Ingridient_attribute ingridient_attribute)
{
    assert(potion);

    potion->ingridient_attributes_count++;
    potion->ingridient_attributes = (Ingridient_attribute*)realloc(potion->ingridient_attributes, 
                                potion->ingridient_attributes_count * sizeof(Ingridient_attribute));
            
    potion->ingridient_attributes[potion->ingridient_attributes_count - 1] = ingridient_attribute;
}

void PotionAddAttribute(Potion* potion, Attribute attribute, size_t count)
{
    assert(potion);

    potion->attributes[attribute] += count;
}


int CalculateHealing(Potion* potion)
{
    assert(potion);

    int healing = (int)potion->attributes[ATTRIBUTE_LIFE] - (int)potion->attributes[ATTRIBUTE_PAIN];
    healing *= 1 + (int)potion->attributes[ATTRIBUTE_FORCE];

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
        summ += (double)potion->attributes[i];
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


void PotionTick(Potion* potion)
{
    if(!potion) return;

    for(size_t i = 0; i < potion->ingridient_attributes_count; i++)
    {
        if(potion->ingridient_attributes[i].ticks_amount > 0)
        {
            potion->ingridient_attributes[i].ticks_amount--;

            if(potion->ingridient_attributes[i].ticks_amount == 0)
            {
                PotionAddAttribute(potion, potion->ingridient_attributes[i].attribute, 1);
            }
        }
    }
}