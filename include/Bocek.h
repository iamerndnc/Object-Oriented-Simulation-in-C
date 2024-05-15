#ifndef BOCEK_H
#define BOCEK_H

#include "Canli.h"

struct BOCEK {
    Canli base;
};
typedef struct BOCEK* Bocek;

Bocek new_Bocek(int numara);

#endif