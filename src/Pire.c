#include "../include/Pire.h"

Pire new_Pire(int numara) {
    Pire this = (Pire)malloc(sizeof(struct PIRE));
    this->base = new_Canli(numara, 'P');
    return this;
}
