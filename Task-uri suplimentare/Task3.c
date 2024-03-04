#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct Mall {
    char* nume;
    int* nrMagazineEtaj;
    int suprafata;
    int nrEtaje;
    int nrParcari;
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

}

void freeMallMemory(struct Mall* m) {
    free(m->nume);
    free(m->nrMagazineEtaj);
    m->nume = NULL;
}

struct Mall* copiazaVectorMalluri(struct Mall* m, int dimensiune, int* newDim) {
    *newDim = 0;

    for (int i = 0; i < dimensiune; i++) {
        if (m[i].nrParcari > 450)
            newDim++;
    }
    struct Mall* copie = (struct Mall*)malloc(*newDim * (sizeof(struct Mall) + 1));

    int j = 0;
    for (int i = 0;i < dimensiune; i++) {
        if (m[i].nrParcari > 450) {
            copie[j] = m[i];
            j++;
        }
    }

    return copie;
}

struct Mall* mutaVectorMalluri(struct Mall* m, int* dimensiune, int* newDim) {
    *newDim = 0;

    for (int i = 0; i < *dimensiune; i++) {
        if (m[i].suprafata > 2500)
            (*newDim)++;
    }

    struct Mall* copie = (struct Mall*)malloc(*newDim * sizeof(struct Mall));

    int j = 0;
    for (int i = 0; i < *dimensiune; i++) {
        if (m[i].suprafata > 2500) {
            copie[j] = m[i];
            j++;
        }
    }

    j = 0;
    for (int i = 0; i < *dimensiune; i++) {
        if (m[i].suprafata <= 2500) {
            m[j] = m[i];
            j++;
        }
    }
    *dimensiune = j;

    return copie;
}

struct Mall* concateneazaVectorMalluri(struct Mall* m1, int dimensiune1, struct Mall* m2, int dimensiune2, int* newDim) {
    *newDim = dimensiune1 + dimensiune2;
    struct Mall* copie = (struct Mall*)malloc(*newDim * sizeof(struct Mall));

    for (int i = 0; i < dimensiune1; i++) {
        copie[i] = m1[i];
    }

    for (int i = 0; i < dimensiune2; i++) {
        copie[i + dimensiune1] = m2[i];
    }

    return copie;
}

void afiseazaVectorMalluri(struct Mall* m, int dimensiune) {
    for (int i = 0; i < dimensiune; i++) {
        displayMall(&m[i]);
    }
    printf("\n\n");
}

void scrieMall(struct Mall* m, const char* filename) {
    FILE* f;
    f = fopen(filename, "w");

    if (f) {
        fprintf(f, "%s\n", m->nume);
        fprintf(f, "%d\n", m->suprafata);
        fprintf(f, "%d\n", m->nrEtaje);
        for (int i = 0; i < m->nrEtaje; i++) {
            fprintf(f, "%d\n", m->nrMagazineEtaj[i]);
        }
        fprintf(f, "%d\n", m->nrParcari);

        fclose(f);
    }
    else printf("EROARE: Fisierul nu a putut fi deschis!\n");
}

void scrieVectorMall(struct Mall* m, int dimensiune, const char* filename) {
    FILE* f;
    f = fopen(filename, "w");

    if (f) {
        fprintf(f, "%d\n", dimensiune);
        for (int i = 0; i < dimensiune; i++) {
            fprintf(f, "%s\n", m[i].nume);
            fprintf(f, "%d\n", m[i].suprafata);
            fprintf(f, "%d\n", m[i].nrEtaje);
            for (int j = 0; j < m[i].nrEtaje; j++) {
                fprintf(f, "%d\n", m[i].nrMagazineEtaj[j]);
            }
            fprintf(f, "%d\n", m[i].nrParcari);
        }

        fclose(f);
    }
    else printf("EROARE: Fisierul nu a putut fi deschis!\n");
}

struct Mall* citesteVectorMall(const char* filename, int* dimensiune) {
	FILE* f;
	f = fopen(filename, "r");

	if (f) {
		fscanf(f, "%d", dimensiune);
		struct Mall* malluri = (struct Mall*)malloc(*dimensiune * sizeof(struct Mall));

		for (int i = 0; i < *dimensiune; i++) {
			malluri[i].nume = (char*)malloc(100 * sizeof(char));
			fscanf(f, "%s", malluri[i].nume);
			fscanf(f, "%d", &malluri[i].suprafata);
			fscanf(f, "%d", &malluri[i].nrEtaje);
			malluri[i].nrMagazineEtaj = (int*)malloc(malluri[i].nrEtaje * sizeof(int));
			for (int j = 0; j < malluri[i].nrEtaje; j++) {
				fscanf(f, "%d", &malluri[i].nrMagazineEtaj[j]);
			}
			fscanf(f, "%d", &malluri[i].nrParcari);
		}

		fclose(f);
		return malluri;
	}
	else {
		printf("EROARE: Fisierul nu a putut fi deschis!\n");
		return NULL;
	}
}


void main() {
    struct Mall m1;
    citesteMall(&m1);
    
   
    scrieMall(&m1, "mall.txt");
    
    printf("Numar magazine total: %d\n", getNrMagazineTotal(&m1));
    displayMall(&m1);

    int dimMalluri1 = 1;
    struct Mall* malluri1 = (struct Mall*)malloc(dimMalluri1 * (sizeof(struct Mall) + 1));

    printf("\nCitire Vector Malluri:\n");
    for (int i = 0; i < dimMalluri1; i++) {
        printf("Mall %i: \n", i);
        citesteMall(&malluri1[i]);
    }

    scrieVectorMall(malluri1, dimMalluri1, "vectormalluri1.txt");
    int* dimMalluri5;
    struct Mall* malluri5 = citesteVectorMall("vectormalluri1.txt", &dimMalluri5);
    afiseazaVectorMalluri(malluri5, dimMalluri5);

    int* dimMalluri2;
    struct Mall* malluri2 = copiazaVectorMalluri(malluri1, dimMalluri1, &dimMalluri2);

    int* dimMalluri3;
    struct Mall* malluri3 = mutaVectorMalluri(malluri1, &dimMalluri1, &dimMalluri3);

    int* dimMalluri4;
    struct Mall* malluri4 = concateneazaVectorMalluri(malluri1, dimMalluri1, malluri2, dimMalluri2, &dimMalluri4);

    afiseazaVectorMalluri(malluri1, dimMalluri1);
    afiseazaVectorMalluri(malluri2, dimMalluri2);
    afiseazaVectorMalluri(malluri3, dimMalluri3);
    afiseazaVectorMalluri(malluri4, dimMalluri4);

    freeMallMemory(&m1);

    for (int i = 0; i < dimMalluri1; i++) {
        freeMallMemory(&malluri1[i]);
    }

    for (int i = 0; i < dimMalluri2; i++) {
        freeMallMemory(&malluri2[i]);
    }

    for (int i = 0; i < dimMalluri3; i++) {
        freeMallMemory(&malluri3[i]);
    }

    for (int i = 0; i < dimMalluri4; i++) {
        freeMallMemory(&malluri4[i]);
    }

    for (int i = 0; i < dimMalluri5; i++) {
        freeMallMemory(&malluri5[i]);
    }

}