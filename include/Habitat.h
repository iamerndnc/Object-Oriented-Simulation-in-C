#ifndef HABITAT_H
#define HABITAT_H

#include "Canli.h"
#include "Bitki.h"
#include "Bocek.h"
#include "Pire.h"
#include "Sinek.h"

struct HABITAT {
    Canli** canlilar;
    int satir_sayisi;
    int sutun_sayisi;
    void (*habitat_yazdir)(struct HABITAT*);
    void (*canli_ekle)(struct HABITAT*, int, int, int);
    void (*habitat_sil)(struct HABITAT*);
    void (*adim_gerceklestir)(struct HABITAT*);
    void (*etkilesim_gerceklestir)(struct HABITAT*, int, int, int, int);
    void (*mevcut_sayi)(struct HABITAT*, int*, int*);
    void (*delete_Canli)(Canli);
    struct HABITAT* (*habitat_from_file)(const char*);

};
typedef struct HABITAT* Habitat;

Habitat new_Habitat(int satir_sayisi, int sutun_sayisi);
void habitat_yazdir(Habitat habitat);
void canli_ekle(Habitat habitat, int satir, int sutun, int numara);
Habitat habitat_from_file(const char* dosya_adi);
void habitat_sil(Habitat habitat);
void adim_gerceklestir(Habitat habitat);
void etkilesim_gerceklestir(Habitat habitat, int satir, int sutun, int mevcut_satir, int mevcut_sutun);
void mevcut_sayi(Habitat habitat, int* satir, int* sutun);
void delete_Canli(Canli canli);

#endif
