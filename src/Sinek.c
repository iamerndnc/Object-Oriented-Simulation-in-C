#include "../include/Sinek.h"

Sinek new_Sinek(int numara) {
    Sinek this = (Sinek)malloc(sizeof(struct SINEK));
    this->base = new_Canli(numara, 'S');
    return this;
}
