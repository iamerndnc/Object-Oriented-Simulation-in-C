#ifndef PIRE_H
#define PIRE_H

#include "Canli.h"

struct PIRE {
    Canli base;
};
typedef struct PIRE* Pire;

Pire new_Pire(int numara);

#endif