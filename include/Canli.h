#ifndef CANLI_H
#define CANLI_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef enum { false, true } boolean;

struct CANLI {
    int numara;
    char sembol;
    void (*yazdir)(struct CANLI*);
};
typedef struct CANLI* Canli;

Canli new_Canli(int numara, char sembol);
void yazdir_Canli(Canli canli);

#endif