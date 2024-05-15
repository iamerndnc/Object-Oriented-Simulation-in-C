#include "../include/Canli.h"

Canli new_Canli(int numara, char sembol) {
    Canli this = (Canli)malloc(sizeof(struct CANLI));
    this->numara = numara;
    this->sembol = sembol;
    this->yazdir = &yazdir_Canli;
    return this;
}

void yazdir_Canli(Canli canli) {
    printf("%c ", canli->sembol);
}
