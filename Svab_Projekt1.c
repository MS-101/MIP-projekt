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
                odmena();
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
