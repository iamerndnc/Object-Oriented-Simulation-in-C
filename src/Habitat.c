#include "../include/Habitat.h"

Habitat new_Habitat(int satir_sayisi, int sutun_sayisi) {
    Habitat this = (Habitat)malloc(sizeof(struct HABITAT));
    this->satir_sayisi = satir_sayisi;
    this->sutun_sayisi = sutun_sayisi;
    this->canlilar = (Canli**)malloc(satir_sayisi * sizeof(Canli*));
    for (int i = 0; i < satir_sayisi; i++) {
        this->canlilar[i] = (Canli*)malloc(sutun_sayisi * sizeof(Canli));
        for (int j = 0; j < sutun_sayisi; j++) {
            this->canlilar[i][j] = NULL;
        }
    }
    this->habitat_yazdir = &habitat_yazdir;
    this->canli_ekle = &canli_ekle;
    this->habitat_sil = &habitat_sil;
    this->habitat_from_file = &habitat_from_file;
    this->adim_gerceklestir = &adim_gerceklestir;
    this->etkilesim_gerceklestir = &etkilesim_gerceklestir;
    this->mevcut_sayi = &mevcut_sayi;
    this->delete_Canli = &delete_Canli;
    return this;
}

void canli_ekle(Habitat habitat, int satir, int sutun, int numara) {
    if (satir < 0 || satir >= habitat->satir_sayisi || sutun < 0 || sutun >= habitat->sutun_sayisi) {
        printf("Hata: Geçersiz konum\n");
        return;
    }
    
    char sembol;
    if (numara >= 1 && numara <= 9) {
        sembol = 'B';
    } else if (numara >= 10 && numara <= 20) {
        sembol = 'C';
    } else if (numara >= 21 && numara <= 50) {
        sembol = 'S';
    } else if (numara >= 51 && numara <= 99) {
        sembol = 'P';
    } else {
        printf("Hata: Geçersiz numara\n");
        exit(1);
    }
    
    Canli canli = new_Canli(numara, sembol);
    habitat->canlilar[satir][sutun] = canli;
}

void habitat_yazdir(Habitat habitat) {
    for (int i = 0; i < habitat->satir_sayisi; i++) {
        for (int j = 0; j < habitat->sutun_sayisi; j++) {
            if (habitat->canlilar[i][j]->sembol != 'X') {
                habitat->canlilar[i][j]->yazdir(habitat->canlilar[i][j]);
            } else {
                printf("X ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

Habitat habitat_from_file(const char* dosya_adi) {
    FILE *dosya = fopen(dosya_adi, "r");
    if (dosya == NULL) {
        printf("Hata: Dosya açılamadı\n");
        return NULL;
    }
    int satir_sayisi = 0;
    int sutun_sayisi = 0;
    int karakter;
    int satir_basi = 1;
    int satirSonu = 0;

    while ((karakter = fgetc(dosya)) != EOF) {
        if (karakter == '\n') {
            satir_sayisi++;
            satir_basi = 1;
            satirSonu = 1;
        } else if (karakter != ' ' && karakter != '\r' && satir_basi) {
            satir_basi = 0;
        }

        if (karakter == ' ' && !satirSonu) {
            sutun_sayisi++;
        }
    }
    satir_sayisi++;
    sutun_sayisi++;

    rewind(dosya);

    Habitat habitat = new_Habitat(satir_sayisi, sutun_sayisi);

    int satir = 0;
    int sutun = 0;
    int numara;
    while (fscanf(dosya, "%d", &numara) != EOF) {
        canli_ekle(habitat, satir, sutun, numara);
        sutun++;
        if (sutun == sutun_sayisi) {
            satir++;
            sutun = 0;
        }
    }

    fclose(dosya);
    return habitat;
}

void delete_Canli(Canli canli) {
    if (canli != NULL) {
        free(canli);
    }
}

void habitat_sil(Habitat habitat) {
    if (habitat == NULL) {
        printf("Hata: Habitat NULL\n");
        return;
    }

    for (int i = 0; i < habitat->satir_sayisi; i++) {
        for (int j = 0; j < habitat->sutun_sayisi; j++) {
            if (habitat->canlilar[i][j] != NULL) {
                delete_Canli(habitat->canlilar[i][j]);
            }
        }
        free(habitat->canlilar[i]);
    }
    free(habitat->canlilar);

    free(habitat);
}

void mevcut_sayi(Habitat habitat, int* satir, int* sutun) {
    for(int i = 0; i < habitat->satir_sayisi; i++) {
        for(int j = 0; j < habitat->sutun_sayisi; j++) {
            if(habitat->canlilar[i][j]->sembol != 'X') {
                *satir = i;
                *sutun = j;
                return;
            }
        }
    }
}

void adim_gerceklestir(Habitat habitat) {
    int mevcut_satir = 0;
    int mevcut_sutun = 0;
    for (int i = 0; i < habitat->satir_sayisi; i++) {
        for (int j = 0; j < habitat->sutun_sayisi; j++) {
            if (habitat->canlilar[i][j] != NULL) {
                mevcut_sayi(habitat, &mevcut_satir, &mevcut_sutun);
                etkilesim_gerceklestir(habitat, i, j, mevcut_satir, mevcut_sutun);
                habitat_yazdir(habitat);
                //system("clear"); // Linux için
                system("cls"); // Windows için
            }
        }
    }
    mevcut_sayi(habitat, &mevcut_satir, &mevcut_sutun);
    habitat_yazdir(habitat);
    printf("Kazanan: %c :  (%d,%d)", habitat->canlilar[mevcut_satir][mevcut_sutun]->sembol, mevcut_satir, mevcut_sutun);
}

void etkilesim_gerceklestir(Habitat habitat, int satir, int sutun, int mevcut_satir, int mevcut_sutun) {
    Canli canli = habitat->canlilar[mevcut_satir][mevcut_sutun];
    if(canli == NULL)
        return;
    char sembol = canli->sembol;
    if(sembol == 'X')
        return;
    
    // Bitki → Pire
    if (sembol == 'B' && sutun <= habitat->sutun_sayisi &&
        satir <= habitat->satir_sayisi  && habitat->canlilar[satir][sutun] != NULL && habitat->canlilar[satir][sutun]->sembol == 'P' && habitat->canlilar[mevcut_satir][mevcut_sutun] != NULL  && mevcut_sutun <= habitat->sutun_sayisi &&
        mevcut_satir <= habitat->satir_sayisi) {
        habitat->canlilar[satir][sutun]->sembol = 'X';
    }
    // Böcek → Bitki
    else if (sembol == 'C' && sutun <= habitat->sutun_sayisi &&
             satir <= habitat->satir_sayisi  && habitat->canlilar[satir][sutun] != NULL && habitat->canlilar[satir][sutun]->sembol == 'B' && habitat->canlilar[mevcut_satir][mevcut_sutun] != NULL && mevcut_sutun <= habitat->sutun_sayisi &&
        mevcut_satir <= habitat->satir_sayisi) {
        habitat->canlilar[satir][sutun]->sembol = 'X';
    }
    // Sinek → Pire
    else if (sembol == 'S' && sutun <= habitat->sutun_sayisi &&
             satir <= habitat->satir_sayisi  && habitat->canlilar[satir][sutun] != NULL && habitat->canlilar[satir][sutun]->sembol == 'P' && habitat->canlilar[mevcut_satir][mevcut_sutun] != NULL && mevcut_sutun <= habitat->sutun_sayisi &&
        mevcut_satir <= habitat->satir_sayisi) {
        habitat->canlilar[satir][sutun]->sembol = 'X';
    }
    // Bitki → Sinek
    else if (sembol == 'B' && sutun <= habitat->sutun_sayisi &&
             satir <= habitat->satir_sayisi  && habitat->canlilar[satir][sutun] != NULL && habitat->canlilar[satir][sutun]->sembol == 'S' && habitat->canlilar[mevcut_satir][mevcut_sutun] != NULL && mevcut_sutun <= habitat->sutun_sayisi &&
        mevcut_satir <= habitat->satir_sayisi) {
        habitat->canlilar[satir][sutun]->sembol = 'X';
    }
    // Sinek → Böcek
    else if (sembol == 'S' && sutun <= habitat->sutun_sayisi &&
             satir <= habitat->satir_sayisi  && habitat->canlilar[satir][sutun] != NULL && habitat->canlilar[satir][sutun]->sembol == 'C' && habitat->canlilar[mevcut_satir][mevcut_sutun] != NULL && mevcut_sutun <= habitat->sutun_sayisi &&
        mevcut_satir <= habitat->satir_sayisi) {
        habitat->canlilar[satir][sutun]->sembol = 'X';
    }
    // Böcek → Pire
    else if (sembol == 'C' && sutun <= habitat->sutun_sayisi &&
             satir <= habitat->satir_sayisi  && habitat->canlilar[satir][sutun] != NULL && habitat->canlilar[satir][sutun]->sembol == 'P' && habitat->canlilar[mevcut_satir][mevcut_sutun] != NULL && mevcut_sutun <= habitat->sutun_sayisi &&
        mevcut_satir <= habitat->satir_sayisi) {
        habitat->canlilar[satir][sutun]->sembol = 'X';      
    }


    // 2. Adım Tam tersten bakmamız gerekiyor.
    // Pire → Bitki
    if (sembol == 'P' && sutun <= habitat->sutun_sayisi &&
        satir <= habitat->satir_sayisi && habitat->canlilar[satir][sutun] != NULL && habitat->canlilar[satir][sutun]->sembol == 'B' && habitat->canlilar[mevcut_satir][mevcut_sutun] != NULL && mevcut_sutun <= habitat->sutun_sayisi &&
        mevcut_satir <= habitat->satir_sayisi) {
        habitat->canlilar[mevcut_satir][mevcut_sutun]->sembol = 'X';
    }
    // Bitki → Böcek
    else if (sembol == 'B' && sutun <= habitat->sutun_sayisi &&
             satir <= habitat->satir_sayisi  && habitat->canlilar[satir][sutun] != NULL && habitat->canlilar[satir][sutun]->sembol == 'C' && habitat->canlilar[mevcut_satir][mevcut_sutun] != NULL && mevcut_sutun <= habitat->sutun_sayisi &&
        mevcut_satir <= habitat->satir_sayisi) {
        habitat->canlilar[mevcut_satir][mevcut_sutun]->sembol = 'X';
    }
    // Pire → Sinek
    else if (sembol == 'P' && sutun <= habitat->sutun_sayisi &&
            satir <= habitat->satir_sayisi  &&  habitat->canlilar[satir][sutun] != NULL && habitat->canlilar[satir][sutun]->sembol == 'S' && habitat->canlilar[mevcut_satir][mevcut_sutun] != NULL && mevcut_sutun <= habitat->sutun_sayisi &&
        mevcut_satir <= habitat->satir_sayisi) {
        habitat->canlilar[mevcut_satir][mevcut_sutun]->sembol = 'X';
    }
    // Sinek → Bitki
    else if (habitat->canlilar[mevcut_satir][mevcut_sutun]->sembol == 'S' && sutun <= habitat->sutun_sayisi &&
            satir <= habitat->satir_sayisi  &&  habitat->canlilar[satir][sutun] != NULL && habitat->canlilar[satir][sutun]->sembol == 'B' && habitat->canlilar[mevcut_satir][mevcut_sutun] != NULL && mevcut_sutun <= habitat->sutun_sayisi &&
        mevcut_satir <= habitat->satir_sayisi) {
        habitat->canlilar[mevcut_satir][mevcut_sutun]->sembol = 'X';
    }
    // Böcek → Sinek
    else if (sembol == 'C' && sutun <= habitat->sutun_sayisi &&
             satir <= habitat->satir_sayisi  && habitat->canlilar[satir][sutun] != NULL && habitat->canlilar[satir][sutun]->sembol == 'S' && habitat->canlilar[mevcut_satir][mevcut_sutun] != NULL && mevcut_sutun <= habitat->sutun_sayisi &&
        mevcut_satir <= habitat->satir_sayisi) {
        habitat->canlilar[mevcut_satir][mevcut_sutun]->sembol = 'X';
    }
    // Pire → Böcek
    else if (sembol == 'P' && sutun <= habitat->sutun_sayisi &&
             satir <= habitat->satir_sayisi  && habitat->canlilar[satir][sutun] != NULL && habitat->canlilar[satir][sutun]->sembol == 'C' && habitat->canlilar[mevcut_satir][mevcut_sutun] != NULL && mevcut_sutun <= habitat->sutun_sayisi &&
        mevcut_satir <= habitat->satir_sayisi) {
        habitat->canlilar[mevcut_satir][mevcut_sutun]->sembol = 'X';
    }

    // 3. Adım Aynı türler arasında karşılaştırma yapmamız gerekiyor.
    // Böcek → Böcek
    if (sembol == 'C' && sutun <= habitat->sutun_sayisi &&
             satir <= habitat->satir_sayisi  && habitat->canlilar[satir][sutun] != NULL && habitat->canlilar[satir][sutun]->sembol == 'C' && habitat->canlilar[mevcut_satir][mevcut_sutun] != NULL && mevcut_sutun <= habitat->sutun_sayisi &&
        mevcut_satir <= habitat->satir_sayisi) {
        if(satir == mevcut_satir && sutun == mevcut_sutun)
            return;
        if(habitat->canlilar[satir][sutun]->numara < canli->numara)
            habitat->canlilar[satir][sutun]->sembol = 'X';
        else if (habitat->canlilar[satir][sutun]->numara > canli->numara)
            habitat->canlilar[mevcut_satir][mevcut_sutun]->sembol = 'X';
        else
        {
            if(satir > mevcut_satir)
                habitat->canlilar[satir][sutun]->sembol = 'X';
            else if(satir < mevcut_satir)
                habitat->canlilar[mevcut_satir][mevcut_sutun]->sembol = 'X';
            else
            {
                if(sutun > mevcut_sutun)
                    habitat->canlilar[satir][sutun]->sembol = 'X';
                else
                    habitat->canlilar[mevcut_satir][mevcut_sutun]->sembol = 'X';
            }
        }
    }
    // Bitki → Bitki
    else if (sembol == 'B' && sutun <= habitat->sutun_sayisi &&
             satir <= habitat->satir_sayisi  && habitat->canlilar[satir][sutun] != NULL && habitat->canlilar[satir][sutun]->sembol == 'B' && habitat->canlilar[mevcut_satir][mevcut_sutun] != NULL && mevcut_sutun <= habitat->sutun_sayisi &&
        mevcut_satir <= habitat->satir_sayisi) {
        if(satir == mevcut_satir && sutun == mevcut_sutun)
            return;
        if(habitat->canlilar[satir][sutun]->numara < canli->numara)
            habitat->canlilar[satir][sutun]->sembol = 'X';
        else if (habitat->canlilar[satir][sutun]->numara > canli->numara)
            habitat->canlilar[mevcut_satir][mevcut_sutun]->sembol = 'X';
        else
        {
            if(satir > mevcut_satir)
                habitat->canlilar[satir][sutun]->sembol = 'X';
            else if(satir < mevcut_satir)
                habitat->canlilar[mevcut_satir][mevcut_sutun]->sembol = 'X';
            else
            {
                if(sutun > mevcut_sutun)
                    habitat->canlilar[satir][sutun]->sembol = 'X';
                else
                    habitat->canlilar[mevcut_satir][mevcut_sutun]->sembol = 'X';
            }
        }
    }
    // Sinek → Sinek
    else if (sembol == 'S' && sutun < habitat->sutun_sayisi &&
             satir < habitat->satir_sayisi  && habitat->canlilar[satir][sutun] != NULL && habitat->canlilar[satir][sutun]->sembol == 'S' && habitat->canlilar[mevcut_satir][mevcut_sutun] != NULL && mevcut_sutun <= habitat->sutun_sayisi &&
        mevcut_satir <= habitat->satir_sayisi) {
        if(satir == mevcut_satir && sutun == mevcut_sutun)
            return;
        if(habitat->canlilar[satir][sutun]->numara < canli->numara)
            habitat->canlilar[satir][sutun]->sembol = 'X';
        else if (habitat->canlilar[satir][sutun]->numara > canli->numara)
            habitat->canlilar[mevcut_satir][mevcut_sutun]->sembol = 'X';
        else
        {
            if(satir > mevcut_satir)
                habitat->canlilar[satir][sutun]->sembol = 'X';
            else if(satir < mevcut_satir)
                habitat->canlilar[mevcut_satir][mevcut_sutun]->sembol = 'X';
            else
            {
                if(sutun > mevcut_sutun)
                    habitat->canlilar[satir][sutun]->sembol = 'X';
                else
                    habitat->canlilar[mevcut_satir][mevcut_sutun]->sembol = 'X';
            }
        }
    }
    // Pire → Pire
    else if (sembol == 'P' && sutun <= habitat->sutun_sayisi &&
                satir <= habitat->satir_sayisi &&  habitat->canlilar[satir][sutun] != NULL && habitat->canlilar[satir][sutun]->sembol == 'P' && habitat->canlilar[mevcut_satir][mevcut_sutun] != NULL && mevcut_sutun <= habitat->sutun_sayisi &&
        mevcut_satir <= habitat->satir_sayisi) {
        if(satir == mevcut_satir && sutun == mevcut_sutun)
            return;
        if(habitat->canlilar[satir][sutun]->numara < canli->numara)
            habitat->canlilar[satir][sutun]->sembol = 'X';
        else if (habitat->canlilar[satir][sutun]->numara > canli->numara)
            habitat->canlilar[mevcut_satir][mevcut_sutun]->sembol = 'X';
        else
        {
            if(satir > mevcut_satir)
                habitat->canlilar[satir][sutun]->sembol = 'X';
            else if(satir < mevcut_satir)
                habitat->canlilar[mevcut_satir][mevcut_sutun]->sembol = 'X';
            else
            {
                if(sutun > mevcut_sutun)
                    habitat->canlilar[satir][sutun]->sembol = 'X';
                else
                    habitat->canlilar[mevcut_satir][mevcut_sutun]->sembol = 'X';
            }
        }
    }
}
