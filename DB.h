//
// Created by Peťa on 16.04.2022.
//

#include "malloc.h"
#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>


typedef struct {
    int pocetMest;
    tSeznamMest *seznam;
    double **vzdalenosti;
} tDatabaze;

/*• Alokuje	strukturu	tDatabaze	v	dynamické	paměti.
• Načte	seznam	měst	ze	souboru	a	uloží	je	do	lineárního	seznamu	(tDatabaze.seznam,	tDatabaze.pocetMest).
• Alokuje	matici	v	dynamické	paměti	a	načte	ze	souboru	vzdálenosti	mezi	jednotlivými	městy.*/
tDatabaze *NactiDatabazi(char *soubor) {
    tDatabaze *db = malloc(sizeof(tDatabaze));
    FILE *fpath;
    fpath = fopen(soubor, "r");
    int pocetMestNacteno = 0;
    db->seznam = NULL;
    char *breakChar = "-";


    //načte města do l. seznamu
    while (1) {
        char *nazevMestaNacteno[DELKA_MESTA];

        fgets(nazevMestaNacteno, DELKA_MESTA, fpath);


        if (strncmp(nazevMestaNacteno, breakChar, strlen(breakChar)) == 0) {
            break;
        }

        db->seznam = PridejNaKonec(db->seznam, VytvorMesto(nazevMestaNacteno));
        pocetMestNacteno++;

    }

    db->pocetMest = pocetMestNacteno;
    db->vzdalenosti = NULL;

    //alokuje matici vzdáleností
    db->vzdalenosti = (double **) malloc((pocetMestNacteno) * sizeof(double *));
    for (int i = 0; i < pocetMestNacteno; ++i) {
        db->vzdalenosti[i] = (double *) malloc((pocetMestNacteno) * sizeof(double));
    }

    //načte data ze souboru
    for (int i = 0; i < pocetMestNacteno; ++i) {
        for (int j = 0; j < pocetMestNacteno; ++j) {
            char nacteneCislo[255];
            fscanf(fpath, "%s", nacteneCislo);

            db->vzdalenosti[i][j] = atof(nacteneCislo);
        }
    }
    return db;
};

//Vypíše matici vzdáleností
void VypisMaticiVzdalenosti(tDatabaze *db) {
    printf("\n");
    for (int i = 0; i < db->pocetMest; ++i) {
        for (int j = 0; j < db->pocetMest; ++j) {
            printf(" %lg ", db->vzdalenosti[i][j]);
        }
        printf("\n");
    }
}


/*• Provede	kompletní	dealokaci	struktury	tDatabaze.
• Dealokuje	lineární	seznam.
• Dealokuje	matici.
• Dealokuje	samotnou	strukturu	tDatabaze.*/
void ZrusDatabazi(tDatabaze *db) {
    ZrusSeznam(db->seznam);
    for (int i = 0; i < db->pocetMest; ++i) {
        free(db->vzdalenosti[i]);
    }
    free(db);
}

/*• Vrací	 index	 města	 (použitý	 pro	 přístup	 do	 matice)	 dle	 pozice	 města	 v	 lineárním	 seznamu	 ve	 struktuře
tDatabaze.
• Pokud	město	neexistuje,	vrací	-1.*/
int DejIndexMesta(tDatabaze *db, char *mesto) {
    tSeznamMest *aktualni = db->seznam;
    for (int i = 0; i < db->pocetMest; ++i) {
        if (strncmp(aktualni->mesto, mesto, strlen(mesto)) == 0) {
            return i + 1;

        }
        aktualni = aktualni->dalsi;
    }
    return -1;
}

/*• Z	matice	vzdáleností	vrací	vzdálenost	mezi	uvedenými	městy.*/
double DejVzdalenostMeziMesty(tDatabaze *db, char *mesto1, char *mesto2) {
    int prvniMestoIndex = DejIndexMesta(db, mesto1);
    int druheMestoIndex = DejIndexMesta(db, mesto2);
    double vzdalenostMeziMesty = db->vzdalenosti[prvniMestoIndex - 1][druheMestoIndex - 1];
    return vzdalenostMeziMesty;
}

/*• Spočítá	celkovou	délku	cesty,	která	je	specifikována	lineárním	seznamem,	obr	2.
• Vrací	celkovou	vzdálenost	mezi	první	a	posledním	městem	v	seznamu*/
double SpocitejDelku(tDatabaze *db, tSeznamMest *seznam) {
    tSeznamMest *aktualniMesto = seznam;
    double celkovaVzdalenost = 0;
    for (int i = 0; i < DejVelikostSeznamu(seznam) - 1; ++i) {
        celkovaVzdalenost += DejVzdalenostMeziMesty(db, aktualniMesto->mesto, aktualniMesto->dalsi->mesto);
        aktualniMesto = aktualniMesto->dalsi;
    }
    return celkovaVzdalenost;

}

/*
• Vypisuje	do	konzole	vzdálenosti	jednotlivých	měst	od	počátku*/
void VypisVzdalenostiOdPocatku(tDatabaze *db, tSeznamMest *seznam) {
    if(DejVelikostSeznamu(seznam) == 0){
        printf("Seznam mest je prazdny.");
        return;
    }

    tSeznamMest *mestoAktualni = seznam;
    double vzdalenostMeziMesty = 0;
    printf("0km          %s",seznam->mesto);
    printf("\n");
    for (int i = 0; i < DejVelikostSeznamu(seznam) - 1; ++i) {
        vzdalenostMeziMesty += DejVzdalenostMeziMesty(db,mestoAktualni->mesto,mestoAktualni->dalsi->mesto);
        printf("%lf",vzdalenostMeziMesty);
        printf(" km          %s",mestoAktualni->dalsi->mesto);
        printf("\n");
        mestoAktualni = mestoAktualni->dalsi;

    }

}
