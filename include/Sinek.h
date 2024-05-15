#ifndef SINEK_H
#define SINEK_H

#include "Canli.h"

struct SINEK {
    Canli base;
};
typedef struct SINEK* Sinek;

Sinek new_Sinek(int numara);

#endif