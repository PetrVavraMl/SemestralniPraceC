#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

//#pragma warning(disable : 4996)
//#define _CRT_SECURE_NO_WARNINGS

#define DELKA_MESTA 60
typedef struct SeznamMest {
    char mesto[DELKA_MESTA];
    struct SeznamMest *dalsi;
} tSeznamMest;

tSeznamMest *prvni;
int velikost = 1;

//• Alokuje a vytvoří strukturu tSeznamMest v dynamické paměti. Funkce vrací ukazatel na první záznam.
tSeznamMest *VytvorMesto(char *mesto) {
    tSeznamMest *noveMesto = malloc(sizeof(tSeznamMest));
    strcpy(noveMesto->mesto, mesto);
    noveMesto->dalsi = NULL;
    return noveMesto;
}
//vrací velikost lineárního seznamu
int DejVelikostSeznamu(tSeznamMest *seznam) {
    tSeznamMest *aktualni = seznam;
    int pocetMestAktualni = 0;
    while (aktualni != NULL) {
        aktualni = aktualni->dalsi;
        pocetMestAktualni++;
    }
    return pocetMestAktualni;
}

//• Přidá nový prvek na konec seznamu. Funkce vrací ukazatel na první záznam.
tSeznamMest *PridejNaKonec(tSeznamMest *seznam, tSeznamMest *novy) {
    if(seznam == NULL){
        velikost++;
        return novy;
    }

    tSeznamMest *prvekAktualni = seznam;
    prvni = seznam;
    while (prvekAktualni->dalsi != NULL) {
        prvekAktualni = prvekAktualni->dalsi;
    }
    prvekAktualni->dalsi = novy;
    velikost++;
    return prvni;
}

//• Přidá nový prvek na požadovanou pozici do seznamu(dle parametru index - číslováno od nuly).Umí vložit prvek i
//  do prázdného seznamu. Testuje existenci požadované pozice.Funkce vrací ukazatel na první záznam.
tSeznamMest *PridejNaIndex(tSeznamMest *seznam, int index, tSeznamMest *novy) {

    //pokud je index menší než nula nebo větší než velikost seznamu
    if (index < 0 || index >= velikost){
        printf("Index neni v rozsahu seznamu.");
        return seznam;
    }
    //pokud je index první prvek
    if (index == 0){
        novy->dalsi = seznam;
        velikost++;
        return novy;
    }
    //pokud je index posledním prvkem
    if (index == velikost - 1) {
        PridejNaKonec(seznam,novy);
        return seznam;
    }
    //pokud je index > 0 a < velikost - 1
    tSeznamMest *aktualni = seznam;
    for (int i = 0; i < index - 1; i++) {
        aktualni = aktualni->dalsi;
    }
    tSeznamMest *odkazZaVlozenym = aktualni->dalsi;
    aktualni->dalsi = novy;
    novy->dalsi = odkazZaVlozenym;
    velikost++;
    return seznam;

}

//• Odebere prvek, určený indexem, ze seznamu. Funkce vrací ukazatel na první záznam.
tSeznamMest *OdeberPrvek(tSeznamMest *seznam, int index) {
    tSeznamMest *prvekAktualni = seznam;
    prvni = seznam;
    //pokud je index menší než nula nebo větší než velikost seznamu
    if (index < 0 || index >= DejVelikostSeznamu(seznam)){
        printf("Index neni v rozsahu seznamu.");
        return seznam;
    }

    for (int i = 0; i < index - 1; i++) {
        if (prvekAktualni->dalsi != NULL) {
            prvekAktualni = prvekAktualni->dalsi;
        } else {
            printf("Zadany index neexistuje!");
            return prvni;
        }
    }
    //pokud je index první prvek
    if (index == 0){
        tSeznamMest* odkazNaDalsi = seznam->dalsi;
        velikost--;
        free(seznam);
        return odkazNaDalsi;
    }
    //pokud je index posledním prvkem
    if (index == DejVelikostSeznamu(seznam) - 1) {
        free(prvekAktualni->dalsi);
        velikost--;
        prvekAktualni->dalsi = NULL;
        return seznam;
    }
    tSeznamMest* odkazDalsi = prvekAktualni->dalsi;
    prvekAktualni->dalsi = prvekAktualni->dalsi->dalsi;
    free(odkazDalsi);
    velikost--;
    return seznam;

}

//• Vypíše prvky seznamu do konzole.
void VypisSeznam(tSeznamMest *seznam) {

    tSeznamMest *aktualni = seznam;
    while (aktualni != NULL) {
        printf("\n");
        printf("%s", aktualni->mesto);
        aktualni = aktualni->dalsi;
    }

    int velikostSeznamu = DejVelikostSeznamu(seznam);
    printf("\n Velikost seznamu: %d", velikostSeznamu);
}

//• Provede	dealokaci	všech	prvků	lineárního	seznamu
void ZrusSeznam(tSeznamMest *seznam) {
    tSeznamMest *aktualni = seznam;
    for (int i = DejVelikostSeznamu(seznam)-1; i >= 0; --i) {
        OdeberPrvek(seznam,i);
    }
}


