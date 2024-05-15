#include <stdio.h>
#include "../include/Habitat.h"

int main() {
    Habitat habitat = habitat_from_file("Veri.txt");
    
    if (habitat != NULL) {
        printf("Baslangic durumu:\n\n");
        habitat_yazdir(habitat);
        printf("Bir Tuş Bekleniyor...\n");
        getchar();
        system("cls"); // Windows için
        //system("clear"); // Linux için
        adim_gerceklestir(habitat);
        habitat_sil(habitat);
    }
    return 0;
}
