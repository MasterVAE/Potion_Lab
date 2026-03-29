#ifndef POTION_H
#define POTION_H

#include <stdlib.h>
#include <ingridients.h>


struct Potion
{
    size_t attributes[ATTRIBUTES_COUNT];
};

Potion* PotionCreate();
void PotionDestroy(Potion* potion);
void PotionClear(Potion* potion);

void PotionAddAttribute(Potion* potion, Attribute attribute, size_t count);

int CalculateHealing(Potion* potion);
int CalculateHeating(Potion* potion);
double CalculateConcentration(Potion* potion);
double CalculatePurity(Potion* potion);
int CalculateStability(Potion* potion);

#endif //POTION_H