#include "../include/Bitki.h"

Bitki new_Bitki(int numara) {
    Bitki this = (Bitki)malloc(sizeof(struct BITKI));
    this->base = new_Canli(numara, 'B');
    return this;
}