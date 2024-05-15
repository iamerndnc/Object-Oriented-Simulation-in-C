#include "../include/Bocek.h"

Bocek new_Bocek(int numara) {
    Bocek this = (Bocek)malloc(sizeof(struct BOCEK));
    this->base = new_Canli(numara, 'C');
    return this;
}
