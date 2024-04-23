#include <stdio.h>
#include <string.h>

// Struktura
struct Osoba {
    char oib[12];
    char ime[50];
    char prezime[50];
    char datum_rodjenja[11];
    char krvna_grupa[5];
    int broj_darivanja;
};

// Deklaracija funkcija
void kreirajDatoteku(char ime_datoteke[], int *brojac);
void obrisiDatoteku(char ime_datoteke[], int *brojac);
void dodajOsobu(char ime_datoteke[]);
void obrisiOsobu(char ime_datoteke[]);
void zabiljeziDarivanje(char ime_datoteke[]);
void ispisiDatoteku(char ime_datoteke[]);
void sortirajOsobe(char ime_datoteke[]);
void mjehuricastoSortiranje(struct Osoba osobe[], int n);
void zamijeni(struct Osoba *a, struct Osoba *b);

int main() {
    int opcija;
    int brojac = 0;
    char ime_datoteke[100] = "";

    do {
    	printf("=====================================================\n");
        printf("1. Kreiraj novu datoteku\n");
        printf("2. Obrisi datoteku\n");
        printf("3. Dodaj osobu u datoteku\n");
        printf("4. Obrisi osobu iz datoteke\n");
        printf("5. Zabiljezi darivanje krvi\n");
        printf("6. Ispisi sadrzaj datoteke\n");
        printf("7. Sortiraj osobe prema broju darivanja krvi\n");
        printf("9. Izlaz iz programa\n");
        printf("=====================================================\n");
        printf("Unesite opciju (1, 2, 3, 4, 5, 6, 7 ili 9): ");
        scanf("%d", &opcija);

        switch(opcija) {
            case 1:
                kreirajDatoteku(ime_datoteke, &brojac);
                break;
            case 2:
                obrisiDatoteku(ime_datoteke, &brojac);
                break;
            case 3:
                dodajOsobu(ime_datoteke);
                break;
            case 4:
                obrisiOsobu(ime_datoteke);
                break;
            case 5:
                zabiljeziDarivanje(ime_datoteke);
                break;
            case 6:
                ispisiDatoteku(ime_datoteke);
                break;
            case 7:
                sortirajOsobe(ime_datoteke);
                break;
            case 9:
                printf("Izlaz iz programa.\n");
                break;
            default:
                printf("Unesena opcija ne postoji. Molimo pokusajte ponovo.\n");
                break;
        }
        printf("\n\n\n");
    } while(opcija != 9);

    return 0;
}

void kreirajDatoteku(char ime_datoteke[], int *brojac){
	if(*brojac == 0){
		printf("Unesite ime datoteke: ");
    	scanf("%s", ime_datoteke);

    	// Provjera postoji li datoteka s tim imenom
    	FILE *provjera_datoteke = fopen(ime_datoteke, "r");
	    if (provjera_datoteke != NULL) {
	        printf("Datoteka s imenom '%s' vec postoji. Nije moguce kreirati novu datoteku.\n", ime_datoteke);
	        fclose(provjera_datoteke);
	        return;
	    }

	    // Ako datoteka ne postoji, kreira se nova
	    FILE *datoteka = fopen(ime_datoteke, "w");
	    if (datoteka == NULL) {
	        printf("Nije moguce kreirati datoteku.\n");
	        return;
	    }
	    fclose(datoteka);
	    printf("Datoteka '%s' je uspjesno kreirana.\n", ime_datoteke);
	    (*brojac)++;
	} else{
		printf("Nije moguce kreirati dvije datoteke. Potrebno je prvo obrisati postojecu.\n");
	}
}


void obrisiDatoteku(char ime_datoteke[], int *brojac) {
    if (ime_datoteke[0] == '\0') {
        printf("Datoteka nije kreirana. Nije moguce obrisati datoteku.\n");
        return;
    }
	
	// Provjera postoji li datoteka s tim imenom
    FILE *provjera_datoteke = fopen(ime_datoteke, "r");
    if (provjera_datoteke == NULL) {
        printf("Datoteka s imenom '%s' ne postoji.\n", ime_datoteke);
        return;
    }
    fclose(provjera_datoteke);

    // Brisanje datoteke
    if (remove(ime_datoteke) == 0) {
        printf("Datoteka '%s' je uspjesno obrisana.\n", ime_datoteke);
        *brojac = 0;
    } else {
        printf("Nije moguce obrisati datoteku '%s'.\n", ime_datoteke);
    }
}

void dodajOsobu(char ime_datoteke[]) {
    if (ime_datoteke[0] == '\0') {
        printf("Datoteka nije kreirana. Nije moguce dodati osobu u datoteku.\n");
        return;
    }
	struct Osoba nova_osoba;
	
    printf("Unesite OIB osobe: ");
    scanf("%s", nova_osoba.oib);
    
    FILE *datoteka = fopen(ime_datoteke, "r");
    if (datoteka == NULL) {
        printf("Nije moguce otvoriti datoteku.\n");
        return;
    }

    char linija[1000];
    while (fgets(linija, sizeof(linija), datoteka) != NULL) {
        char *oib = strtok(linija, ";");
        if (oib != NULL && strcmp(oib, nova_osoba.oib) == 0) {
            printf("Osoba s istim OIB-om vec postoji u datoteci.\n");
            fclose(datoteka);
            return;
        }
    }
    fclose(datoteka);
    
    printf("Unesite ime osobe: ");
    scanf("%s", nova_osoba.ime);
    printf("Unesite prezime osobe: ");
    scanf("%s", nova_osoba.prezime);
    printf("Unesite datum rodenja osobe (dd.mm.gggg): ");
    scanf("%s", nova_osoba.datum_rodjenja);
    printf("Unesite krvnu grupu osobe: ");
    scanf("%s", nova_osoba.krvna_grupa);
    printf("Unesite broj darivanja krvi osobe: ");
    scanf("%d", &nova_osoba.broj_darivanja);

    datoteka = fopen(ime_datoteke, "a");
    if (datoteka == NULL) {
        printf("Nije moguce otvoriti datoteku za pisanje.\n");
        return;
    }

    fprintf(datoteka, "%s;%s;%s;%s;%s;%d\n", nova_osoba.oib, nova_osoba.ime, nova_osoba.prezime, nova_osoba.datum_rodjenja, nova_osoba.krvna_grupa, nova_osoba.broj_darivanja);

    fclose(datoteka);
    printf("Osoba je uspjesno dodana u datoteku.\n");
}

void obrisiOsobu(char ime_datoteke[]) {
    FILE *datoteka = fopen(ime_datoteke, "r");
    if (datoteka == NULL) {
        printf("Datoteka nije kreirana. Nije moguce obrisati osobu.\n");
        return;
    }
    
    char trazeni_oib[12];
    printf("Unesite OIB osobe koju zelite izbrisati: ");
    scanf("%s", trazeni_oib);

    // Kreiranje privremene datoteke
    FILE *privremena_datoteka = fopen("privremena_datoteka.txt", "w");
    if (privremena_datoteka == NULL) {
        printf("Nije moguce kreirati privremenu datoteku.\n");
        fclose(datoteka);
        return;
    }
    
    char linija[1000];
    int obrisano = 0;
    
    while (fgets(linija, sizeof(linija), datoteka) != NULL) {
	    char kopija_linije[1000];
    	strcpy(kopija_linije, linija);
		
		char *atribut = strtok(kopija_linije, ";");
	
	    // Provjera je li OIB iz retka jednak traženom OIB-u
	    if (atribut != NULL && strcmp(atribut, trazeni_oib) == 0) {
	        obrisano = 1;
	    } else {
	        fprintf(privremena_datoteka, "%s", linija);
		}
	}

    fclose(datoteka);
    fclose(privremena_datoteka);
    
    // Brisanje originalne datoteke i preimenovanje privremene datoteke
    if (obrisano) {
        remove(ime_datoteke);
        rename("privremena_datoteka.txt", ime_datoteke);
        printf("Osoba je uspjesno obrisana iz datoteke.\n");
    } else {
        remove("privremena_datoteka.txt");
        printf("Osoba s unesenim OIB-om ne postoji u datoteci.\n");
    }
}

void zabiljeziDarivanje(char ime_datoteke[]) {
    FILE *datoteka = fopen(ime_datoteke, "r");
    if (datoteka == NULL) {
        printf("Datoteka nije kreirana. Nije moguce zabiljeziti darivanje.\n");
        return;
    }
    
    char trazeni_oib[12];
    printf("Unesite OIB osobe za koju zelite zabiljeziti darivanje krvi: ");
    scanf("%s", trazeni_oib);

    // Kreiranje privremene datoteke
    FILE *privremena_datoteka = fopen("privremena_datoteka.txt", "w");
    if (privremena_datoteka == NULL) {
        printf("Nije moguce kreirati privremenu datoteku.\n");
        fclose(datoteka);
        return;
    }
    
    char linija[1000];
    int zabiljezeno = 0;
    struct Osoba osobe[1000];
	int n = 0;
    
    while (fgets(linija, sizeof(linija), datoteka) != NULL) {
    	sscanf(linija, "%[^;];%[^;];%[^;];%[^;];%[^;];%d",
           osobe[n].oib, osobe[n].ime, osobe[n].prezime,
           osobe[n].datum_rodjenja, osobe[n].krvna_grupa,
           &osobe[n].broj_darivanja);
    	n++;
	}
	
	int i;
	for (i = 0; i < n; i++) {
	    if (strcmp(osobe[i].oib, trazeni_oib) == 0) {
	        zabiljezeno = 1;
	        osobe[i].broj_darivanja++;
	    }
	}
	
	int j;
	for (j = 0; j < n; j++) {
	    fprintf(privremena_datoteka, "%s;%s;%s;%s;%s;%d\n", osobe[j].oib, osobe[j].ime, osobe[j].prezime,
	            osobe[j].datum_rodjenja, osobe[j].krvna_grupa, osobe[j].broj_darivanja);
	}

    fclose(datoteka);
    fclose(privremena_datoteka);
    
    // Brisanje originalne datoteke i preimenovanje privremene datoteke
    if (zabiljezeno) {
        remove(ime_datoteke);
        rename("privremena_datoteka.txt", ime_datoteke);
        printf("Osobi je uspjesno zabiljezeno darivanje krvi.\n");
    } else {
        remove("privremena_datoteka.txt");
        printf("Osoba s unesenim OIB-om ne postoji u datoteci.\n");
    }
}

void ispisiDatoteku(char ime_datoteke[]) {
    FILE *datoteka = fopen(ime_datoteke, "r");
    if (datoteka == NULL) {
        printf("Datoteka nije kreirana. Nije moguce ispisati sadrzaj datoteke.\n", ime_datoteke);
        return;
    }

    printf("SADRZAJ DATOTEKE '%s':\n", ime_datoteke);

    // Citanje i ispisivanje sadržaja datoteke red po red
   	char linija[1000];
    while (fgets(linija, sizeof(linija), datoteka) != NULL) {
        char atributi[6][100];

        char *atribut = strtok(linija, ";");
        int i = 0;
        while (atribut != NULL && i < 6) {
            strcpy(atributi[i], atribut);
            atribut = strtok(NULL, ";");
            i++;
        }

        printf("OIB: %s\n", atributi[0]);
        printf("Ime: %s\n", atributi[1]);
        printf("Prezime: %s\n", atributi[2]);
        printf("Datum rodjenja: %s\n", atributi[3]);
        printf("Krvna grupa: %s\n", atributi[4]);
        printf("Broj darivanja: %s", atributi[5]);
        printf("----------------------------------\n");
    }

    fclose(datoteka);
}

void sortirajOsobe(char ime_datoteke[]) {
    FILE *datoteka = fopen(ime_datoteke, "r");
    if (datoteka == NULL) {
        printf("Datoteka nije kreirana. Nije moguce ispisati sadrzaj datoteke.\n");
        return;
    }

    // Ucitavanje osoba iz datoteke
    struct Osoba osobe[1000];
    int n = 0;
    char linija[1000];
    while (fgets(linija, sizeof(linija), datoteka) != NULL) {
        sscanf(linija, "%[^;];%[^;];%[^;];%[^;];%[^;];%d",
               osobe[n].oib, osobe[n].ime, osobe[n].prezime,
               osobe[n].datum_rodjenja, osobe[n].krvna_grupa,
               &osobe[n].broj_darivanja);
        n++;
    }
    fclose(datoteka);

    // Sortiranje osoba prema broju darivanja krvi
    mjehuricastoSortiranje(osobe, n);

    // Ispis sortiranih osoba
    printf("SORTIRANE OSOBE PREMA BROJU DARIVANJA KRVI U DATOTECI '%s':\n", ime_datoteke);
    int i;
	for (i = 0; i < n; i++) {
        printf("Ime: %s\n", osobe[i].ime);
        printf("Prezime: %s\n", osobe[i].prezime);
        printf("Broj darivanja: %d\n", osobe[i].broj_darivanja);
        printf("----------------------------------\n");
    }
}

void mjehuricastoSortiranje(struct Osoba osobe[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (osobe[j].broj_darivanja < osobe[j + 1].broj_darivanja) {
                zamijeni(&osobe[j], &osobe[j + 1]);
            }
        }
    }
}

void zamijeni(struct Osoba *a, struct Osoba *b) {
    struct Osoba temp = *a;
    *a = *b;
    *b = temp;
}
