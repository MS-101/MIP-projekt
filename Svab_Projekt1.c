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
    if (aktualnyRok - rok > 1) {
        return 1;
    } else if (aktualnyRok - rok == 1) {
        if (aktualnyMesiac > mesiac) {
            return 1;
        } else if (aktualnyMesiac = mesiac) {
            if (aktualnyDen >= den) {
                return 1;
            } else {
                return 0;
            }
        } else {
            return 0;
        }
    } else {
        return 0;
    }
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
