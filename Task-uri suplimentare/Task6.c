#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct Mall Mall;
typedef struct Nod Nod;
typedef struct NodSimplu NodSimplu;

struct Mall {
    char* nume;
    int* nrMagazineEtaj;
    int suprafata;
    int nrEtaje;
    int nrParcari;
};

struct Nod {
    struct Mall info;
    struct Nod* urm;
    struct Nod* prev;
};

struct NodSimplu {
    struct Mall info;
	struct NodSimplu* urm;
};


struct Mall* citesteMall(struct Mall* m) {
    m->nume = (char*)malloc(100 * sizeof(char));

    printf("Numele mall-ului: ");
    scanf("%s", m->nume);

    printf("Suprafata mall-ului: ");
    scanf("%d", &m->suprafata);

    printf("Numarul de etaje (inclusiv parter): ");
    scanf("%d", &m->nrEtaje);


    m->nrMagazineEtaj = (int*)malloc(m->nrEtaje * sizeof(int));

    for (int i = 0; i < m->nrEtaje; i++) {
        if (i == 0)
            printf("Numar magazine parter: ");
        else printf("Numar magazine etaj %d: ", i);

        scanf("%d", &m->nrMagazineEtaj[i]);
    }


    printf("Numarul de locuri de parcare: ");
    scanf("%d", &m->nrParcari);

    return m;
}


int getNrMagazineTotal(struct Mall* m) {
    int nrMagazine = 0;

    for (int i = 0; i < m->nrEtaje; i++) {
        nrMagazine += m->nrMagazineEtaj[i];
    }

    return nrMagazine;
}


void setNrParcari(struct Mall* m, int nrParcari) {
    if (nrParcari > 0)
        m->nrParcari = nrParcari;
    else printf("Numarul de locuri de parcare trebuie sa fie pozitiv!");
}

void displayMall(struct Mall* m) {
    printf("Nume mall: %s\n", m->nume);
    printf("Suprafata mall: %d\n", m->suprafata);
    printf("Numar etaje: %d\n", m->nrEtaje);

    for (int i = 0; i < m->nrEtaje; i++) {
        if (i == 0)
            printf("Numar magazine parter: %d\n", m->nrMagazineEtaj[i]);
        else printf("Numar magazine etaj %d: %d\n", i, m->nrMagazineEtaj[i]);
    }

    printf("Numar locuri de parcare: %d\n", m->nrParcari);
    printf("\n");
}

void freeMallMemory(struct Mall* m) {
    free(m->nume);
    free(m->nrMagazineEtaj);
}

void freeMallVectorMemory(struct Mall* m, int dim) {
    for (int i = 0; i < dim; i++) {
        freeMallMemory(&m[i]);
    }
    free(m);
}

void afiseazaVectorMalluri(struct Mall* m, int dimensiune) {
    for (int i = 0; i < dimensiune; i++) {
        displayMall(&m[i]);
    }
    printf("\n\n");
}

struct Mall* adaugaMallInVector(struct Mall* malluri, struct Mall mall, int* dimensiune) {
    struct Mall* copie = (struct Mall*)malloc(sizeof(struct Mall) * ((*dimensiune) + 1));

    for (int i = 0; i < (*dimensiune); i++) {
        copie[i] = malluri[i];
    }

    copie[(*dimensiune)] = mall;
    (*dimensiune)++;

    return copie;
}

struct Mall* citesteVectorMallDinFisier(const char* filename, int* dimensiune) {
    FILE* f;
    f = fopen(filename, "r");

    if (f) {
        struct Mall* malluri = NULL;
        (*dimensiune) = 0;
        char line[100];

        while (fgets(line, sizeof(line), f) != NULL) {
            struct Mall mall;
            char* data = strtok(line, "\n");
            mall.nume = (char*)malloc(sizeof(char) * (strlen(data) + 1));
            strcpy(mall.nume, data);

            fgets(line, sizeof(line), f);
            mall.suprafata = atoi(line);

            fgets(line, sizeof(line), f);
            mall.nrEtaje = atoi(line);

            mall.nrMagazineEtaj = (int*)malloc(mall.nrEtaje * sizeof(int));
            for (int i = 0; i < mall.nrEtaje; i++) {
                fgets(line, sizeof(line), f);
                mall.nrMagazineEtaj[i] = atoi(line);
            }

            fgets(line, sizeof(line), f);
            mall.nrParcari = atoi(line);
            
            malluri = adaugaMallInVector(malluri, mall, dimensiune);
        }

        fclose(f);
        return malluri;
    }
    else {
        printf("EROARE: Fisierul nu a putut fi deschis!\n");
        return NULL;
    }
}


void adaugaMallInLista(struct Nod** nod, Mall* mall) {
    struct Nod* nod_adaugat = malloc(sizeof(struct Nod));

    nod_adaugat->info.nume = (char*)malloc(sizeof(char) * (strlen(mall->nume) + 1));
    strcpy(nod_adaugat->info.nume, mall->nume);
    nod_adaugat->info.suprafata = mall->suprafata;
    nod_adaugat->info.nrParcari = mall->nrParcari;
    nod_adaugat->info.nrEtaje = mall->nrEtaje;
    nod_adaugat->info.nrMagazineEtaj = (int*)malloc(sizeof(int) * mall->nrEtaje);

    for (int i = 0; i < mall->nrEtaje; i++) {
        nod_adaugat->info.nrMagazineEtaj[i] = mall->nrMagazineEtaj[i];
    }

    nod_adaugat->urm = NULL;

    if (*nod == NULL) {
        nod_adaugat->prev = NULL;
        *nod = nod_adaugat;
    }
    else {
        struct Nod* t = *nod;
        while (t->urm != NULL) {
            t = t->urm;
        }
        
        t->urm = nod_adaugat;
        nod_adaugat->prev = t;
    }
}

void afiseazaListaMall(struct Nod* nod) {
    while (nod) {
        displayMall(&(nod->info));
        nod = nod->urm;
    }
}

void stergeNodDupaIndex(struct Nod** nod, int index) {
    if (*nod == NULL)
        return;

    struct Nod* temp = *nod;
    struct Nod* prev = NULL;

    int count = 0;

    while (temp != NULL && count < index) {
        prev = temp;
        temp = temp->urm;
        count++;
    }

    if (prev == NULL) {
        *nod = temp->urm;
    } else if (temp != NULL) {
        prev->urm = temp->urm;
        temp->prev = prev;
    }
    
    free(prev);
    free(temp);
}

void adaugaMallInListaSortat(Nod** nod, Mall* mall) {
    Nod* nod_adaugat = (Nod*)malloc(sizeof(Nod));
    nod_adaugat->info.nume = (char*)malloc(sizeof(char) * (strlen(mall->nume) + 1));
    strcpy(nod_adaugat->info.nume, mall->nume);
    nod_adaugat->info.suprafata = mall->suprafata;
    nod_adaugat->info.nrParcari = mall->nrParcari;
    nod_adaugat->info.nrEtaje = mall->nrEtaje;
    nod_adaugat->info.nrMagazineEtaj = (int*)malloc(sizeof(int) * mall->nrEtaje);
    for (int i = 0; i < mall->nrEtaje; i++) {
        nod_adaugat->info.nrMagazineEtaj[i] = mall->nrMagazineEtaj[i];
    }

    Nod* temp = *nod;
    Nod* prev = NULL;

    while(temp != NULL && temp->info.suprafata < mall->suprafata) {
		prev = temp;
		temp = temp->urm;
	}

    if (prev == NULL) {
		nod_adaugat->urm = *nod;
		nod_adaugat->prev = NULL;
		*nod = nod_adaugat;
	} else {
		prev->urm = nod_adaugat;
		nod_adaugat->prev = prev;
		nod_adaugat->urm = temp;
		if (temp != NULL) {
			temp->prev = nod_adaugat;
		}
	}

}

void sorteazaListaMallCrescator(Nod** nod) {
    Nod* temp = *nod;

    while (temp != NULL) {
        Nod* temp2 = temp->urm;
        while (temp2 != NULL) {
            if (temp->info.suprafata > temp2->info.suprafata) {
                Mall temp_mall = temp->info;
                temp->info = temp2->info;
                temp2->info = temp_mall;
            }
            temp2 = temp2->urm;
        }
        temp = temp->urm;
    }
}

void sorteazaListaMallDescrescator(Nod** nod) {
    Nod* temp = *nod;

    while (temp != NULL) {
        Nod* temp2 = temp->urm;
        while (temp2 != NULL) {
            if (temp->info.suprafata < temp2->info.suprafata) {
                Mall temp_mall = temp->info;
                temp->info = temp2->info;
                temp2->info = temp_mall;
            }
            temp2 = temp2->urm;
        }
        temp = temp->urm;
    }
}

NodSimplu* listaDublaToSimpla(Nod* nod_vechi, int suprafata) {
    NodSimplu* nod_nou = NULL;

    while (nod_vechi) {
        if (nod_vechi->info.suprafata >= suprafata) {
            NodSimplu* nod_adaugat = (NodSimplu*)malloc(sizeof(NodSimplu));
			nod_adaugat->info.nume = (char*)malloc(sizeof(char) * (strlen(nod_vechi->info.nume) + 1));
			strcpy(nod_adaugat->info.nume, nod_vechi->info.nume);
			nod_adaugat->info.suprafata = nod_vechi->info.suprafata;
			nod_adaugat->info.nrParcari = nod_vechi->info.nrParcari;
			nod_adaugat->info.nrEtaje = nod_vechi->info.nrEtaje;
			nod_adaugat->info.nrMagazineEtaj = (int*)malloc(sizeof(int) * nod_vechi->info.nrEtaje);
			for (int i = 0; i < nod_vechi->info.nrEtaje; i++) {
				nod_adaugat->info.nrMagazineEtaj[i] = nod_vechi->info.nrMagazineEtaj[i];
			}

			nod_adaugat->urm = NULL;

			if (nod_nou == NULL) {
				nod_nou = nod_adaugat;
			}
			else {
				NodSimplu* t = nod_nou;
				while (t->urm != NULL) {
					t = t->urm;
				}

				t->urm = nod_adaugat;
			}
        }

        nod_vechi = nod_vechi->urm;
    }

    return nod_nou;
}

void interschimbaMalluriLista(Nod** nod, int poz1, int poz2) {
    Nod* temp = *nod;

    while (temp->urm) {
        if (poz1 == 0) {
			Nod* temp2 = *nod;
			for (int i = 0; i < poz2; i++) {
				temp2 = temp2->urm;
			}

			Mall temp_mall = temp->info;
			temp->info = temp2->info;
			temp2->info = temp_mall;
			break;
		}

		temp = temp->urm;
		poz1--;
    }
}

void main() {
    int* dimMalluri;
    struct Mall* malluri = NULL;
    malluri = citesteVectorMallDinFisier("vectormalluri.txt", &dimMalluri);

    struct Nod* nod = NULL;
    for (int i = 0; i < dimMalluri; i++) {
        adaugaMallInLista(&nod, &(malluri[i]));
    }

    printf("Lista inainte de modificari: \n");
    afiseazaListaMall(nod);

    stergeNodDupaIndex(&nod, 0);

    printf("Lista dupa stergerea primului mall: \n");
    afiseazaListaMall(nod);

    struct Mall* m1 = (struct Mall*)malloc(sizeof(struct Mall));
    m1->nume = (char*)malloc(sizeof(char) * (strlen("mall_craiova") + 1));
    strcpy(m1->nume, "mall_craiova");
    m1->nrEtaje = 2;
    m1->nrParcari = 2000;
    m1->suprafata = 9500;
    m1->nrMagazineEtaj = (int*)malloc(sizeof(int) * m1->nrEtaje);
    for (int i = 0; i < (m1->nrEtaje); i++) {
        m1->nrMagazineEtaj[i] = 80;
    }

    adaugaMallInListaSortat(&nod, m1);

    printf("Lista dupa adaugarea mallului: \n");
    afiseazaListaMall(nod);

    printf("Lista dupa sortare crescatoare: \n");
    sorteazaListaMallCrescator(&nod);
    afiseazaListaMall(nod);

    NodSimplu* nod_simplu = listaDublaToSimpla(nod, 7000);

    printf("Lista dupa interschimbarea primului cu al 2lea element: \n");
    interschimbaMalluriLista(&nod, 0, 1);
    afiseazaListaMall(nod);

    freeMallVectorMemory(malluri, dimMalluri);
}