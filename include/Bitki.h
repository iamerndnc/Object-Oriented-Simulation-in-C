#ifndef BITKI_H
#define BITKI_H

#include "Canli.h"

struct BITKI {
    Canli base;
};
typedef struct BITKI* Bitki;

Bitki new_Bitki(int numara);

#endif