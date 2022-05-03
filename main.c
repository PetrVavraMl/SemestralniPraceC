#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>
#include "seznamMest.h"
#include "DB.h"

#define _CRTDBG_MAP_ALLOC

#include <crtdbg.h>

void empty_stdin(void) {
    int c = getchar();

    while (c != '\n' && c != EOF)
        c = getchar();
}

int main() {
    tDatabaze *db = NactiDatabazi("C:\\Temp\\mesta.txt");
    tSeznamMest *seznamMestMain;
    int programBezi = 1;
    int volba = 0;
    while (programBezi) {
        printf("\n1 - Vypis vsechny mesta \n"
               "2 - Pridej mesto\n"
               "3 - Pridej mesto na index\n"
               "4 - Odeber mesto\n"
               "5 - Zrus seznam\n"
               "6 - Vypis mesta v aktualnim seznamu\n"
               "7 - Vypis delku cesty vsech mest\n"
               "8 - Vypis dilci vzdalenosti\n"
               "9 - Ukoncit program\n");

        printf("Zadejte cislo: \n");
        scanf("%d", &volba);
        switch (volba) {
            case 1:
                VypisSeznam(db->seznam);
                break;
            case 2:
                printf("Zadejte nazev mesta pro pridani(nazvy podporovanych mest lze vypsat prikazem cislo 1.): \n");
                char nazevMestaNove[DELKA_MESTA];
                scanf("%s", nazevMestaNove);
                tSeznamMest *mestoNove = VytvorMesto(nazevMestaNove);
                seznamMestMain = PridejNaKonec(seznamMestMain, mestoNove);
                break;
            case 3:
                printf("Zadejte nazev mesta pro pridani(nazvy podporovanych mest lze vypsat prikazem cislo 1.): \n");
                char nazevMestaNove2[DELKA_MESTA];
                scanf("%s", nazevMestaNove);
                tSeznamMest *mestoNoveIndex = VytvorMesto(nazevMestaNove);
                int indexMestaNove;
                printf("Zadejte index: \n");
                scanf("%d", &indexMestaNove);
                seznamMestMain = PridejNaIndex(seznamMestMain, indexMestaNove, mestoNoveIndex);
                break;
            case 4:;
                int indexMestaOdebrani;
                printf("Zadejte index mesta pro odebrani: \n");
                scanf("%d", &indexMestaOdebrani);
                seznamMestMain = OdeberPrvek(seznamMestMain, indexMestaOdebrani);
                break;
            case 5:
                ZrusSeznam(seznamMestMain);
                printf("\nSeznam byl zrusen.\n");
                break;
            case 6:
                printf("Seznam mest: \n");
                VypisSeznam(seznamMestMain);
                break;
            case 7:;
                double celkovaVzdalenost = SpocitejDelku(db, seznamMestMain);
                printf("Celkova vzdalenost vsech mest je : %lf", celkovaVzdalenost);
                printf("\n");
                break;
            case 8:
                VypisVzdalenostiOdPocatku(db, seznamMestMain);
                break;
            case 9:
                programBezi = 0;
                printf("Program byl ukoncen.");
                break;
            default:
                printf("\nNeznamy prikaz.\n");
                empty_stdin();
                break;
        }
    }

    if (_CrtDumpMemoryLeaks() != 0) {
        printf("\nNebyla provedena dealokace");
    } else {
        printf("\nDealokace provedla v poradku.");
    }
    return 0;
}
