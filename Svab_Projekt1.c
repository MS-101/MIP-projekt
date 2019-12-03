#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DLZKA_MENA 50
#define DLZKA_SPZ 7
#define ODMENA_STARE 5.1
#define ODMENA_NOVE 2.3
#define ROK 10000
#define POCET_UDAJOV_ZAZNAMU 5
#define POCET_CISIEL 10
#define POCET_PISMEN 26

typedef struct zaznam {
    char menoPriezvisko[DLZKA_MENA + 1];
    char spz[DLZKA_SPZ + 1];
    int typAuta;
    double cena;
    int datum;
} ZAZNAM;

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

int nacitajZaznamSuboru(FILE **vstupnySubor, ZAZNAM **aktualnyZaznam) {
    char menoPriezvisko[DLZKA_MENA + 1];
    char spz[DLZKA_SPZ + 1];
    int typAuta;
    double cena;
    int datum;

    //ak sa nepodarí načítať meno zo vstupného súboru, tak funkcia nahlási chybu
    if (fgets(menoPriezvisko, DLZKA_MENA + 1, *vstupnySubor) != NULL) {
        //načítanie hodnôt zo súboru do pomocných premenných
        fgets(spz, DLZKA_SPZ + 1, *vstupnySubor);
        fscanf(*vstupnySubor, "%d\n", &typAuta);
        fscanf(*vstupnySubor, "%lf\n", &cena);
        fscanf(*vstupnySubor, "%d\n", &datum);
        fscanf(*vstupnySubor, "\n");

        //odstránenie \n z konca stringov
        odstranNewLine(menoPriezvisko);
        odstranNewLine(spz);

        //prenos hodnôt z pomocných premenných na parameter funkcie
        strcpy((*aktualnyZaznam) -> menoPriezvisko, menoPriezvisko);
        strcpy((*aktualnyZaznam) -> spz, spz);
        (*aktualnyZaznam) -> typAuta = typAuta;
        (*aktualnyZaznam) -> cena = cena;
        (*aktualnyZaznam) -> datum = datum;

        return 0;
    } else {
        return 1;
    }
}

void vypisZaznamSuboru(ZAZNAM *aktualnyZaznam) {
    printf("meno a priezvisko: %s\n", aktualnyZaznam -> menoPriezvisko);
    printf("SPZ: %s\n", aktualnyZaznam -> spz);
    printf("typ auta: %d\n", aktualnyZaznam -> typAuta);
    printf("cena: %.2f\n", aktualnyZaznam -> cena);
    printf("datum: %d\n", aktualnyZaznam -> datum);
    printf("\n");
}

void vypisSuboru(FILE **vstupnySubor) {
    if (otvorSubor(vstupnySubor) == 1) {
        return;
    }

    ZAZNAM *aktualnyZaznam;
    aktualnyZaznam = (ZAZNAM*)malloc(sizeof(ZAZNAM));

    while(nacitajZaznamSuboru(vstupnySubor, &aktualnyZaznam) == 0) {
        vypisZaznamSuboru(aktualnyZaznam);
    }

    free(aktualnyZaznam);
}

void vypisOdmenu(ZAZNAM *aktualnyZaznam) {
    double odmena;

    if (aktualnyZaznam -> typAuta == 1) {
        odmena = aktualnyZaznam -> cena / 100 * ODMENA_NOVE;
    } else {
        odmena = aktualnyZaznam -> cena / 100 * ODMENA_STARE;
    }

    printf("%s %s %.2f\n", aktualnyZaznam -> menoPriezvisko, aktualnyZaznam -> spz, odmena);
}

void odmena(FILE **vstupnySubor) {
    if (*vstupnySubor != NULL) {
        int aktualnyDatum;
        ZAZNAM *aktualnyZaznam;
        aktualnyZaznam = (ZAZNAM*)malloc(sizeof(ZAZNAM));

        scanf("%d", &aktualnyDatum);

        rewind(*vstupnySubor);
        while(nacitajZaznamSuboru(vstupnySubor, &aktualnyZaznam) == 0) {
            if (aktualnyDatum - aktualnyZaznam -> datum >= ROK) {
                vypisOdmenu(aktualnyZaznam);
            }
        }

        free(aktualnyZaznam);
    }
}

int pocetZaznamovVSubore(FILE **vstupnySubor) {
    char menoPriezvisko[DLZKA_MENA + 1];
    char znak;
    int i;
    int pocetZaznamov = 0;

    rewind(*vstupnySubor);
    while (fgets(menoPriezvisko, DLZKA_MENA + 1, *vstupnySubor) != NULL) {
        pocetZaznamov++;
        for (i = 0; i < POCET_UDAJOV_ZAZNAMU; i++) {
            while (getc(*vstupnySubor) != '\n');
        }
    }

    return pocetZaznamov;
}

void vycistiPole(char ***poleSpz) {
    if (*poleSpz != NULL) {
        free(*poleSpz);
    }
}

void alokujPole(char ***poleSpz, int pocetZaznamov) {
    int i;

    *poleSpz = malloc(pocetZaznamov * sizeof(char**));
    for (i = 0; i < pocetZaznamov; i++) {
        (*poleSpz)[i] = malloc(8 * sizeof(char*));
    }
}

void vyplnPole(char ***poleSpz, int pocetZaznamov, FILE **vstupnySubor) {
    int i, j;

    //1. spz je 2. hodnota v súbore
    rewind(*vstupnySubor);
    while (getc(*vstupnySubor) != '\n');

    for (i = 0; i < pocetZaznamov; i++) {
        //zápis spz do pola SPZ
        fgets((*poleSpz)[i], DLZKA_SPZ + 1, *vstupnySubor);
        while (getc(*vstupnySubor) != '\n');
        (*poleSpz)[i][8] = '\0';

        //preskočenie riadkov na dalšiu spz
        if (i + 1 < pocetZaznamov) {
            for (j = 0; j < POCET_UDAJOV_ZAZNAMU; j++) {
                while (getc(*vstupnySubor) != '\n');
            }
        }
    }
}

void nacitajPole(FILE **vstupnySubor, char ***poleSpz, int *pocetZaznamov) {
    if (*vstupnySubor != NULL) {
        *pocetZaznamov = pocetZaznamovVSubore(vstupnySubor);

        vycistiPole(poleSpz);
        alokujPole(poleSpz, *pocetZaznamov);
        vyplnPole(poleSpz, *pocetZaznamov, vstupnySubor);
    }
}

void vypisPola(char **poleSpz, int pocetZaznamov) {
    if (poleSpz != NULL) {
        int i, j;
        for (i = 0; i < pocetZaznamov; i++) {
            //výpis prvých 2 znakov spz
            for (j = 0; j < 2; j++) {
                printf("%c", poleSpz[i][j]);
            }

            printf(" ");

            //výpis čísiel spz
            for (j = 0; j < 3; j++) {
                printf("%c", poleSpz[i][j + 2]);
            }

            printf(" ");

            //výpis posledných znakov spz
            for (j = 0; j < 2; j++) {
                printf("%c", poleSpz[i][j + 5]);
            }

            printf("\n");
        }
    } else {
        printf("Pole nie je vytvorene\n");
    }
}

void vynulujPoleCisiel(int **poleCisiel, int pocetPrvkov) {
    int i;

    for (i = 0; i < pocetPrvkov; i++) {
        poleCisiel[i] = 0;
    }
}

void spocitajZnakyPolaSpz(int *pocetnostiPismen, int *pocetnostiCisiel, char **poleSpz, int pocetZaznamov) {
    int i, j;

    for (i = 0; i < pocetZaznamov; i++) {
        for (j = 0; j < DLZKA_SPZ; j++) {
            //počítanie písmen
            if (poleSpz[i][j] >= 'A' && poleSpz[i][j] <= 'Z') {
                pocetnostiPismen[poleSpz[i][j] - 'A']++;
            //počítanie čísiel
            } else if (poleSpz[i][j] >= '0' && poleSpz[i][j] <= '9') {
                pocetnostiCisiel[poleSpz[i][j] - '0']++;
            }
        }
    }
}

void najdiNajpocetnejsiZnak(int *pocetnostiPismen, int *pocetnostiCisiel, char *maxChar, int *max) {
    int i, j;

    *max = pocetnostiPismen[0];
    *maxChar = 'A';

    //najdi najpocetnejsie pismeno
    for (i = 1; i < POCET_PISMEN; i++) {
        if (pocetnostiPismen[i] > *max) {
            *max = pocetnostiPismen[i];
            *maxChar = 'A' + i;
        }
    }

    //najdi najpocetnejsie cislo
    for (i = 0; i < POCET_CISIEL; i++) {
        if (pocetnostiCisiel[i] > *max) {
            *max = pocetnostiCisiel[i];
            *maxChar = '0' + i;
        }
    }
}

void maxPocetnostPola(char **poleSpz, int pocetZaznamov) {
    if (poleSpz != NULL) {
        int max;
        char maxChar;

        int pocetnostiPismen[POCET_PISMEN];
        int pocetnostiCisiel[POCET_CISIEL];

        vynulujPoleCisiel(&pocetnostiPismen, POCET_PISMEN);
        vynulujPoleCisiel(&pocetnostiCisiel, POCET_CISIEL);

        spocitajZnakyPolaSpz(pocetnostiPismen, pocetnostiCisiel, poleSpz, pocetZaznamov);

        najdiNajpocetnejsiZnak(pocetnostiPismen, pocetnostiCisiel, &maxChar, &max);

        printf("%c %d\n", maxChar, max);
    } else {
        printf("Pole nie je vytvorene\n");
    }
}

int jePalindrom(char *buf) {
    int i;
    int bufLen;

    bufLen = strlen(buf);

    for (i = 0; i < (bufLen / 2); i++) {
        if (buf[i] != buf[bufLen - 1 - i]) {
            return 0;
        }
    }

    return 1;
}

void palindromVPoli(char **poleSpz, int pocetZaznamov) {
    if (poleSpz != NULL) {
        int i;

        for (i = 0; i < pocetZaznamov; i++) {
            if (jePalindrom(poleSpz[i]) == 1) {
                printf("%c%c\n", poleSpz[i][0], poleSpz[i][1]);
            }
        }
    } else {
        printf("Pole nie je vytvorene\n");
    }
}

void vypisNajziskovejsieOkresy(int pocetNajziskovejsich, char najziskovejsieOkresy[pocetNajziskovejsich][3], int maxPredaneAuta) {
    int i;

    for (i = 0; i < pocetNajziskovejsich; i++) {
        printf("%s %d\n", najziskovejsieOkresy[i], maxPredaneAuta);
    }
}

void zistiNajziskovejsieOkresy(char **poleSpz, int pocetZaznamov, int *pocetNajziskovejsich, char (*najziskovejsieOkresy)[pocetZaznamov][3], int *maxPredaneAuta) {
    int i, j;
    int predaneAuta;

    for (i = 0; i < pocetZaznamov; i++) {
        predaneAuta = 1;
        for (j = i+1; j < pocetZaznamov; j++) {
            if (poleSpz[i][0] == poleSpz[j][0] && poleSpz[i][1] == poleSpz[j][1]) {
                predaneAuta++;
            }
        }

        if (predaneAuta > *maxPredaneAuta) {
            *maxPredaneAuta = predaneAuta;
            *pocetNajziskovejsich = 1;
            (*najziskovejsieOkresy)[*pocetNajziskovejsich - 1][0] = poleSpz[i][0];
            (*najziskovejsieOkresy)[*pocetNajziskovejsich - 1][1] = poleSpz[i][1];
            (*najziskovejsieOkresy)[*pocetNajziskovejsich - 1][2] = '\0';
        } else if (predaneAuta == *maxPredaneAuta) {
            (*pocetNajziskovejsich)++;
            (*najziskovejsieOkresy)[*pocetNajziskovejsich - 1][0] = poleSpz[i][0];
            (*najziskovejsieOkresy)[*pocetNajziskovejsich - 1][1] = poleSpz[i][1];
            (*najziskovejsieOkresy)[*pocetNajziskovejsich - 1][2] = '\0';
        }
    }
}

void zistiPredaj(char **poleSpz, int pocetZaznamov) {
    if (poleSpz != NULL) {
        int pocetNajziskovejsich, maxPredaneAuta = 0;
        char najziskovejsieOkresy[pocetZaznamov][3];

        zistiNajziskovejsieOkresy(poleSpz, pocetZaznamov, &pocetNajziskovejsich, &najziskovejsieOkresy, &maxPredaneAuta);
        vypisNajziskovejsieOkresy(pocetNajziskovejsich, najziskovejsieOkresy, maxPredaneAuta);
    }
}

int koniecProgramu(FILE **vstupnySubor, char ***poleSpz){
    if (*vstupnySubor != NULL) {
        if (fclose(*vstupnySubor) == EOF) {
            return 1;
        }
    }
    if (*poleSpz != NULL) {
        free(*poleSpz);
    }
    return 0;
}

int main() {
    FILE *vstupnySubor = NULL;
    char **poleSpz = NULL;
    int pocetZaznamov = 0;
    while (1)  {
        switch (getchar()) {
            case 'v':
                vypisSuboru(&vstupnySubor);
                break;
            case 'o':
                odmena(&vstupnySubor);
                break;
            case 'n':
                nacitajPole(&vstupnySubor, &poleSpz, &pocetZaznamov);
                break;
            case 's':
                vypisPola(poleSpz, pocetZaznamov);
                break;
            case 'm':
                maxPocetnostPola(poleSpz, pocetZaznamov);
                break;
            case 'p':
                palindromVPoli(poleSpz, pocetZaznamov);
                break;
            case 'z':
                zistiPredaj(poleSpz, pocetZaznamov);
                break;
            case 'k':
                return koniecProgramu(&vstupnySubor, &poleSpz);
                break;
        }
    }
}
