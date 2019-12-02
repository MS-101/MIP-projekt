#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DLZKA_MENA 50
#define DLZKA_SPZ 7
#define ODMENA_STARE 5.1
#define ODMENA_NOVE 2.3

int otvorSubor(FILE **vstupnySubor) {
    //ak sa súbor ešte nebol otvorený, tak sa ho pokúsi otvoriť
    if (*vstupnySubor == NULL) {
        if ((*vstupnySubor = fopen("autobazar.txt", "r")) == NULL) {
            printf("Neotvoreny subor\n");
            return 1;
        }
    //ak súbor už bol otvorený, tak vráť ukazovateľ v súbore na začiatok
    } else {
        rewind(*vstupnySubor);
    }

    return 0;
}

void odstranNewLine(char *buf) {
    int bufLen;
    bufLen = strlen(buf);

    if (bufLen > 0 && buf[bufLen - 1]  == '\n') {
        buf[bufLen - 1] = '\0';
    }
}

void vypisZaznamSuboru(FILE **vstupnySubor, char *menoPriezvisko) {
    char spz[DLZKA_SPZ + 1];
    int typAuta;
    double cena;
    int datum;

    //načítanie hodnôt zo súboru
    fgets(spz, DLZKA_SPZ + 1, *vstupnySubor);
    fscanf(*vstupnySubor, "%d\n", &typAuta);
    fscanf(*vstupnySubor, "%lf\n", &cena);
    fscanf(*vstupnySubor, "%d\n", &datum);
    fscanf(*vstupnySubor, "\n");

    //odstránenie \n z konca stringov
    odstranNewLine(menoPriezvisko);
    odstranNewLine(spz);

    //výpis načítaných hodnôt do konzoly
    printf("meno a priezvisko: %s\n", menoPriezvisko);
    printf("SPZ: %s\n", spz);
    printf("typ auta: %d\n", typAuta);
    printf("cena: %.2f\n", cena);
    printf("datum: %d\n", datum);
    printf("\n");
}

void vypisSuboru(FILE **vstupnySubor) {
    if (otvorSubor(vstupnySubor) == 1) {
        return;
    }

    char menoPriezvisko[DLZKA_MENA + 1];
    while(fgets(menoPriezvisko, DLZKA_MENA + 1, *vstupnySubor) != NULL) {
        vypisZaznamSuboru(vstupnySubor, menoPriezvisko);
    }
}

void odmena(FILE **vstupnySubor) {
    if (*vstupnySubor != NULL) {
        int aktualnyDatum, datumZamestnania;
        char menoPriezvisko[DLZKA_MENA + 1];
        char spz[DLZKA_SPZ + 1];
        int typAuta;
        double cena, odmena;

        scanf("%d", &aktualnyDatum);

        rewind(*vstupnySubor);
        while(fgets(menoPriezvisko, 51, *vstupnySubor) != NULL) {
            fscanf(*vstupnySubor, "%d\n", &typAuta);
            fscanf(*vstupnySubor, "%lf\n", &cena);
            fgets(spz, 8, *vstupnySubor);
            fscanf(*vstupnySubor, "%d\n", &datumZamestnania);
            fscanf(*vstupnySubor, "\n");

            //odstránenie \n z konca stringov
            odstranNewLine(menoPriezvisko);
            odstranNewLine(spz);

            if (aktualnyDatum - datumZamestnania >= 10000) {
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

void vytvorPole(FILE **fr, char ***pole, int *pocetZaznamov) {
    if (*fr != NULL) {
        if (*pole != NULL) {
            free(*pole);
        }
        rewind(*fr);
        char str[51];
        *pocetZaznamov = 0;
        int i, y;
        while (fgets(str, 51, *fr) != NULL) {
            (*pocetZaznamov)++;
            for (i = 0; i < 5; i++) {
                fgets(str, 51, *fr);
            }
        }
        *pole = malloc(*pocetZaznamov * sizeof(char**));
        for (i = 0; i < *pocetZaznamov; i++) {
            (*pole)[i] = malloc(8 * sizeof(char*));
        }
        for (i = 0; i < *pocetZaznamov; i++) {
            char spz[8];
            fscanf(*fr, "%s\n", spz);
            spz[8] = '\0';
            for (y = 0; y < 8; y++) {
                (*pole)[i][y] = spz[y];
            }
            for (y = 0; y < 5; y++) {
                fgets(str, 51, *fr);
            }
        }
    }
}

void vypisPola(char **pole, int pocetZaznamov) {
    if (pole != NULL) {
        int i, y;
        for (i = 0; i < pocetZaznamov; i++) {
            for (y = 0; y < 2; y++) {
                printf("%c", pole[i][y]);
            }
            printf(" ");
            for (y = 0; y < 3; y++) {
                printf("%c", pole[i][y + 2]);
            }
            printf(" ");
            for (y = 0; y < 2; y++) {
                printf("%c", pole[i][y + 5]);
            }
            printf("\n");
        }
    } else {
        printf("Pole nie je vytvorene\n");
    }
}

void maxPocetnostPola(char **pole, int pocetZaznamov) {
    if (pole != NULL) {
        int i, y;
        int pocetnostiPismen[26];
        for (i = 0; i < 26; i++) {
            pocetnostiPismen[i] = 0;
        }
        int pocetnostiCisiel[10];
        for (i = 0; i < 10; i++) {
            pocetnostiCisiel[i] = 0;
        }
        for (i = 0; i < pocetZaznamov; i++) {
            for (y = 0; y < 7; y++) {
                if (pole[i][y] >= 'A' && pole[i][y] <= 'Z') {
                    pocetnostiPismen[pole[i][y] - 'A']++;
                } else if (pole[i][y] >= '0' && pole[i][y] <= '9') {
                    pocetnostiCisiel[pole[i][y] - '0']++;
                }
            }
        }
        int max = pocetnostiPismen[0];
        char maxChar = 'A';
        for (i = 1; i < 26; i++) {
            if (pocetnostiPismen[i] > max) {
                max = pocetnostiPismen[i];
                maxChar = 'A' + i;
            }
        }
        for (i = 0; i < 10; i++) {
            if (pocetnostiCisiel[i] > max) {
                max = pocetnostiCisiel[i];
                maxChar = '0' + i;
            }
        }
        printf("%c %d\n", maxChar, max);
    } else {
        printf("Pole nie je vytvorene\n");
    }
}

void palindromVPoli(char **pole, int pocetZaznamov) {
    if (pole != NULL) {
        int i, y;
        int jePalindrom;
        for (i = 0; i < pocetZaznamov; i++) {
            jePalindrom = 1;
            for (y = 0; y < 3; y++) {
                if (pole[i][y] != pole[i][6 - y]) {
                    jePalindrom = 0;
                    break;
                }
            }
            if (jePalindrom == 1) {
                printf("%c%c\n", pole[i][0], pole[i][1]);
            }
        }
    } else {
        printf("Pole nie je vytvorene\n");
    }
}

void zistiPredaj(char ** pole, int pocetZaznamov) {
    if (pole != NULL) {
        int i, y;
        int pocetnost, indexMax, maxPocetnost = 0;
        char maxPredaj[pocetZaznamov][3];
        for (i = 0; i < pocetZaznamov; i++) {
            pocetnost = 1;
            for (y = i+1; y < pocetZaznamov; y++) {
                if (pole[i][0] == pole[y][0] && pole[i][1] == pole[y][1]) {
                    pocetnost++;
                }
            }
            if (pocetnost > maxPocetnost) {
                maxPocetnost = pocetnost;
                indexMax = 0;
                maxPredaj[indexMax][0] = pole[i][0];
                maxPredaj[indexMax][1] = pole[i][1];
                maxPredaj[indexMax][2] = '\0';
            } else if (pocetnost == maxPocetnost) {
                indexMax++;
                maxPredaj[indexMax][0] = pole[i][0];
                maxPredaj[indexMax][1] = pole[i][1];
                maxPredaj[indexMax][2] = '\0';
            }
        }
        for (i = 0; i <= indexMax; i++) {
            printf("%s %d\n", maxPredaj[i], maxPocetnost);
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
                vytvorPole(&fr, &pole, &pocetZaznamov);
                break;
            case 's':
                vypisPola(pole, pocetZaznamov);
                break;
            case 'm':
                maxPocetnostPola(pole, pocetZaznamov);
                break;
            case 'p':
                palindromVPoli(pole, pocetZaznamov);
                break;
            case 'z':
                zistiPredaj(pole, pocetZaznamov);
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
