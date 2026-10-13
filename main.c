#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// Definiram strukturu
typedef struct {
    char name[20];
    char lastName[30];
    int bodovi;
} stud;

int main() {
    char buffer[50];
    int brojac = 0;

    // Otvaram datoteku
    FILE* fp = fopen("popis.txt", "r");
    if (fp == NULL) {
        printf("Greska pri otvaranju datoteke!\n");
        return -1;
    }

    // 1. Prvo brojim redove u datoteci
    while (!feof(fp)) {
        if (fgets(buffer, 50, fp) != NULL) {
            brojac++;
        }
    }

    // Dinamička alokacija memorije za studente
    stud* Studenti = NULL;
    Studenti = (stud*)malloc(sizeof(stud) * brojac);

    if (!Studenti) {
        printf("Greska pri alokaciji memorije!\n");
        return -2;
    }

    // Vraćam pokazivač na početak datoteke kako bi procitala podatke
    rewind(fp);

    // Učitavanje studenata i pronalaženje maksimalnog broja bodova
    int max_bodovi = 0;
    int i = 0;

    while (!feof(fp) && i < brojac) {
        if (fscanf(fp, "%s %s %d", Studenti[i].name, Studenti[i].lastName, &Studenti[i].bodovi) == 3) {
            if (Studenti[i].bodovi > max_bodovi) {
                max_bodovi = Studenti[i].bodovi;
            }
            i++;
        }
    }

    // Zatvaram datoteku
    fclose(fp);
    
    //Ispis rezultata
    printf("\n--- REZULTATI ---\n");
    for (int j = 0; j < brojac; j++) {
        float relativan_br_bodova = 0.0;
        if (max_bodovi > 0) {
            relativan_br_bodova = ((float)Studenti[j].bodovi / max_bodovi) * 100.0;
        }

        printf("%s %s - Bodovi: %d | Relativno: %.2f%%\n",
            Studenti[j].name, Studenti[j].lastName, Studenti[j].bodovi, relativan_br_bodova);
    }

    //Oslobađanje alocirane memorije
    free(Studenti);

    return 0;
}


