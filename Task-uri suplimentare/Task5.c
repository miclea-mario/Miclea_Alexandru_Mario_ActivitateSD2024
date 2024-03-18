#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

struct Mall {
    char* nume;
    int* nrMagazineEtaj;
    int suprafata;
    int nrEtaje;
    int nrParcari;
};

struct Nod {
    struct Mall* mall;
    struct Nod* urm;
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
    m->nume = NULL;
    m->nrMagazineEtaj = NULL;
}

void freeMallVectorMemory(struct Mall** m, int* dim) {
    for (int i = 0; i < (*dim); i++) {
        freeMallMemory(m[i]);
    }

    free(m);
    free(dim);
    dim = NULL;
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


void adaugaMallInLista(struct Nod** nod, struct Mall* mall) {
    struct Nod* nod_adaugat = malloc(sizeof(struct Nod));
    nod_adaugat->mall = mall;
    nod_adaugat->urm = NULL;

    if (*nod == NULL) {
        *nod = nod_adaugat;
    }
    else {
        struct Nod* t = *nod;
        while (t->urm != NULL) {
            t = t->urm;
        }

        t->urm = nod_adaugat;
    }
}

void afiseazaListaMall(struct Nod* nod) {
    while (nod) {
        displayMall(nod->mall);
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
    }

    freeMallMemory(temp->mall);
    free(temp);
}

void insereazaMallInListaSortat(struct Nod** nod, struct Mall* mall) {
	struct Nod* nod_adaugat = malloc(sizeof(struct Nod));
	nod_adaugat->mall = mall;
	nod_adaugat->urm = NULL;

	if (*nod == NULL) {
		*nod = nod_adaugat;
	}
	else {
		struct Nod* t = *nod;
		struct Nod* prev = NULL;
		while (t != NULL && t->mall->suprafata < mall->suprafata) {
			prev = t;
			t = t->urm;
		}

		if (prev == NULL) {
			nod_adaugat->urm = *nod;
			*nod = nod_adaugat;
		}
		else {
			prev->urm = nod_adaugat;
			nod_adaugat->urm = t;
		}
	}
}

// transforma lista in vector in functie de suprafata
struct Mall** listaToVector(struct Nod** nod, int* dim, int suprafata) {
    *dim = 0;
    struct Nod* prev = *nod;

    while (prev != NULL) {
        if (prev->mall->suprafata > suprafata) {
            (*dim)++;
        }
        prev = prev->urm;
    }

    struct Mall** malluri = (struct Mall**)malloc(sizeof(struct Mall*) * (*dim));
    prev = *nod;
    int k = 0;

    while (prev != NULL && k < (*dim)) {
        if (prev->mall->suprafata > suprafata) {
            struct Mall* mall = (struct Mall*)malloc(sizeof(struct Mall));
            mall->nume = (char*)malloc(sizeof(char) * (strlen(prev->mall->nume) + 1));
            strcpy(mall->nume, prev->mall->nume);
            mall->nrEtaje = prev->mall->nrEtaje;
            mall->nrParcari = prev->mall->nrParcari;
            mall->suprafata = prev->mall->suprafata;
            mall->nrMagazineEtaj = (int*)malloc(sizeof(int) * mall->nrEtaje);

            for (int i = 0; i < (mall->nrEtaje); i++) {
                mall->nrMagazineEtaj[i] = prev->mall->nrMagazineEtaj[i];
            }

            malluri[k++] = mall;
        }
        prev = prev->urm;
    }

    return malluri;
}

void interschimbaElementeLista(struct Nod** nod, int index1, int index2) {
    int count1 = 0, count2 = 0;

    struct Nod* prev1 = NULL;
    struct Nod* prev2 = NULL;

    struct Nod* el1 = NULL;
    struct Nod* el2 = NULL;

    struct Nod* temp = *nod;

    while (temp != NULL && (count1 < index1 || count2 < index2)) {
        if (count1 < index1) {
            prev1 = temp;
            el1 = temp;
            temp = temp->urm;
            count1++;
        }
        if (count2 < index2) {
            prev2 = temp;
            el2 = temp;
            temp = temp->urm;
            count2++;
        }
    }

    if (count1 == index1 && count2 == index2) {
        if (index2 - index1 == 1) {
            struct Nod* temp_next = el2->urm;
            el2->urm = temp_next->urm;
            temp_next->urm = el2;
            if (prev1 != NULL)
                prev1->urm = temp_next;
            else
                *nod = temp_next;
        }
        else {
            struct Nod* temp_next = el2->urm;
            el2->urm = el1->urm;
            el1->urm = temp_next;
            if (prev1 != NULL)
                prev1->urm = el2;
            else
                *nod = el2;
            if (prev2 != NULL)
                prev2->urm = el1;
            else
                *nod = el1;
        }
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
    m1->nrParcari = 300;
    m1->suprafata = 9500;
    m1->nrMagazineEtaj = (int*)malloc(sizeof(int) * m1->nrEtaje);
    for (int i = 0; i < (m1->nrEtaje); i++) {
        m1->nrMagazineEtaj[i] = 80;
    }

    insereazaMallInListaSortat(&nod, m1);
    printf("Lista dupa adaugarea mallului: \n");
    afiseazaListaMall(nod);

    int* dimVectorMalluri;
    struct Mall** vectorMalluri = listaToVector(&nod, &dimVectorMalluri, 8500);

    printf("Lista to Vector:\n");
    for(int i = 0; i<dimVectorMalluri; i++) {
        displayMall(vectorMalluri[i]);
    }

    interschimbaElementeLista(&nod, 1, 2);
    printf("Lista dupa interschimbare: \n");
    afiseazaListaMall(nod);

    freeMallVectorMemory(vectorMalluri, dimVectorMalluri);

    freeMallMemory(m1);
    freeMallVectorMemory(malluri, dimMalluri);
}