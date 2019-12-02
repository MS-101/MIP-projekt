#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void vypisSuboru(FILE **fr) {
    if (*fr == NULL) {
        if ((*fr = fopen("autobazar.txt", "r")) == NULL) {
            printf("Neotvoreny subor\n");
            return;
        }
    } else {
        rewind(*fr);
    }
    //str obsahuje 51 znakov, lebo 51. znak je '/0' ak do neho naèítam záznam s 50 znakmi.
    char str[51];
    double num;
    while(fgets(str, 51, *fr) != NULL) {
        if (str[strlen(str) - 1] == '\n') {
            str[strlen(str) - 1] = '\0';
        }
        printf("meno a priezvisko: %s\n", str);
        fgets(str, 8, *fr);
        fscanf(*fr, "\n");
        printf("SPZ: %s\n", str);
        fgets(str, 2, *fr);
        printf("typ auta: %s\n", str);
        fscanf(*fr, "%lf\n", &num);
        printf("cena: %.2f\n", num);
        fgets(str, 9, *fr);
        printf("datum: %d\n", str);
        printf("\n");
        fscanf(*fr, "\n");
    }
}

int pracovalRok(char *datum, char *aktualnyDatum) {
    int i;
    int rok, mesiac, den;
    int aktualnyRok, aktualnyMesiac, aktualnyDen;
    char rokStr[5], mesiacStr[3], denStr[3];
    char aktualnyRokStr[5], aktualnyMesiacStr[3], aktualnyDenStr[3];
    for (i = 0; i < 4; i++) {
        rokStr[i] = datum[i];
        aktualnyRokStr[i] = aktualnyDatum[i];
    }
    rokStr[4] = '\0';
    aktualnyRokStr[4] = '\0';
    for (i = 0; i < 2; i++) {
        mesiacStr[i] = datum[i+4];
        aktualnyMesiacStr[i] = aktualnyDatum[i+5];
    }
    mesiacStr[2] = '\0';
    aktualnyMesiacStr[2] = '\0';
    for (i = 0; i < 2; i++) {
        denStr[i] = datum[i+6];
        aktualnyDenStr[i] = aktualnyDatum[i+7];
    }
    denStr[2] = '\0';
    aktualnyDenStr[2] = '\0';
    rok = atoi(rokStr);
    aktualnyRok = atoi(aktualnyRokStr);
    mesiac = atoi(mesiacStr);
    aktualnyMesiac = atoi(aktualnyMesiacStr);
    den = atoi(denStr);
    aktualnyDen = atoi(aktualnyDenStr);
}

void odmena(FILE **fr) {
    if (*fr != NULL) {
        #define ODMENA_STARE 5.1
        #define ODMENA_NOVE 2.3

        char aktualnyDatum[9], datum[9], menoPriezvisko[51], spz[8];
        int typAuta;
        double cena, odmena;

        scanf("%s", aktualnyDatum);
        rewind(*fr);
        while(fgets(menoPriezvisko, 51, *fr) != NULL) {
            if (menoPriezvisko[strlen(menoPriezvisko) - 1] == '\n') {
                menoPriezvisko[strlen(menoPriezvisko) - 1] = '\0';
            }
            fgets(spz, 8, *fr);
            fscanf(*fr, "%d\n", &typAuta);
            fscanf(*fr, "%lf\n", &cena);
            fgets(datum, 9, *fr);
            fscanf(*fr, "\n");
            if (pracovalRok(datum, aktualnyDatum)) {
                if (typAuta == 1) {
                    odmena = cena / 100 * ODMENA_NOVE;
                } else {
                    odmena = cena / 100 * ODMENA_STARE;
                }
                printf("%s %s %.2f\n", menoPriezvisko, spz, odmena);
            }
        }
    }
}

int main() {
    FILE *fr = NULL;
    char **pole = NULL;
    int pocetZaznamov = 0;
    while (1)  {
        switch (getchar()) {
            case 'v':
                vypisSuboru(&fr);
                break;
            case 'o':
                odmena(&fr);
                break;
            case 'n':
                vytvorPole();
                break;
            case 's':
                vypisPola();
                break;
            case 'm':
                maxPocetnostPola();
                break;
            case 'p':
                palindromVPoli();
                break;
            case 'z':
                zistiPredaj();
                break;
            case 'k':
                if (fr != NULL) {
                    if (fclose(fr) == EOF) {
                        return 1;
                    }
                }
                if (pole != NULL) {
                    free(pole);
                }
                return 0;
                break;
        }
    }
}
