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

void scrieVectorMallInFisier(struct Mall* m, int dimensiune, const char* filename) {
    FILE* f;
    f = fopen(filename, "w");

    if (f) {
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

struct Mall** copieazaVectorInMatrice(struct Mall* vector, int* liniiMatrice, int* colMatrice, int* dimVector) {
    struct Mall** copie = (struct Mall**)malloc(sizeof(struct Mall*) * 4);

    /* 
    asezam elementele din vector in functie de suprafata
    linia #0: suprafata < 1500
    linia #1: 1500 <= suprafata < 4500
    linia #2: 4500 <= suprafata < 7500
    linia #3: suprafata >= 7500
    */
    (*liniiMatrice) = 4;
    int nrElementeLinie[] = { 0, 0, 0, 0 };

    // calculam nr de elemente pentru fiecare linie
    for (int i = 0; i < (*dimVector); i++) {
        int linieElement = 0;
        if (vector[i].suprafata >= 1500 && vector[i].suprafata < 4500)
            linieElement = 1;
        else if (vector[i].suprafata >= 4500 && vector[i].suprafata < 7500)
            linieElement = 2;
        else linieElement = 3;

        nrElementeLinie[linieElement]++;
    }

    (*colMatrice) = 0;

    for (int i = 0; i < (*liniiMatrice); i++) {
        if (nrElementeLinie[i] > (*colMatrice)) {
            (*colMatrice) = nrElementeLinie[i];
        }
    }

    for (int i = 0; i < (*liniiMatrice); i++) {
        copie[i] = (struct Mall*)malloc(sizeof(struct Mall) * (*colMatrice));
    }

    int tempNrElementeLinie[] = { 0, 0, 0, 0 };

    // copiem elementele vectorului pe pozitia corespunzatoare
    for (int i = 0; i < (*dimVector); i++) {
        int linieElement = 0;
        if (vector[i].suprafata >= 1500 && vector[i].suprafata < 4500)
            linieElement = 1;
        else if (vector[i].suprafata >= 4500 && vector[i].suprafata < 7500)
            linieElement = 2;
        else linieElement = 3;


        copie[linieElement][tempNrElementeLinie[linieElement]].nume = (char*)malloc(sizeof(char) * (strlen(vector[i].nume) + 1));
        strcpy(copie[linieElement][tempNrElementeLinie[linieElement]].nume, vector[i].nume);

        copie[linieElement][tempNrElementeLinie[linieElement]].nrEtaje = vector[i].nrEtaje;
        copie[linieElement][tempNrElementeLinie[linieElement]].nrParcari = vector[i].nrParcari;
        copie[linieElement][tempNrElementeLinie[linieElement]].suprafata = vector[i].suprafata;

        copie[linieElement][tempNrElementeLinie[linieElement]].nrMagazineEtaj = (int*)malloc(sizeof(int) * vector[i].nrEtaje);

        // copiem nr de magazine pe etaj
        for (int j = 0; j < vector[i].nrEtaje; j++) {
            copie[linieElement][tempNrElementeLinie[linieElement]].nrMagazineEtaj[j] = vector[i].nrMagazineEtaj[j];
        }

        tempNrElementeLinie[linieElement]++;
    }

    // restul pozitiilor care nu s-au ocupat le initializam cu valori implicite
    for (int i = 0; i < (*liniiMatrice); i++) {
        for (int j = tempNrElementeLinie[i]; j < (*colMatrice); j++) {
            copie[i][j].nume = NULL;
            copie[i][j].nrEtaje = -1;
            copie[i][j].nrMagazineEtaj = NULL;
            copie[i][j].nrParcari = -1;
            copie[i][j].suprafata = -1;
        }
    }

    return copie;
}

struct Mall** sorteazaMatriceDupaLinii(struct Mall** matriceMall, int liniiMatrice, int colMatrice) {
	struct Mall** copie = (struct Mall**)malloc(sizeof(struct Mall*) * liniiMatrice);

	for (int i = 0; i < liniiMatrice; i++) {
		copie[i] = (struct Mall*)malloc(sizeof(struct Mall) * colMatrice);
	}

	for (int i = 0; i < liniiMatrice; i++) {
		for (int j = 0; j < colMatrice; j++) {
			copie[i][j] = matriceMall[i][j];
		}
	}

    for (int i = 0; i < liniiMatrice - 1; i++) {
		    for (int j = i + 1; j < liniiMatrice; j++) {
			    int nrElementeI = 0;
			    int nrElementeJ = 0;

			    for (int k = 0; k < colMatrice; k++) {
				    if (copie[i][k].nume) {
					    nrElementeI++;
				    }

				    if (copie[j][k].nume) {
					    nrElementeJ++;
				    }
			    }

			    if (nrElementeI < nrElementeJ) {
				    struct Mall* temp = copie[i];
				    copie[i] = copie[j];
				    copie[j] = temp;
			    }
		    }
	}

	return copie;
}

void afiseazaMatrice(struct Mall** matriceMall, int liniiMatrice, int colMatrice) {
    printf("Linii %d, coloane %d\n", liniiMatrice, colMatrice);
    for (int i = 0; i < liniiMatrice; i++) {
        for (int j = 0; j < colMatrice; j++) {
            if (matriceMall[i][j].nume) {
                printf("Elementul %d %d\n", i, j);
                displayMall(&matriceMall[i][j]);
            }
        }
        printf("\n");
    }
}

void main() {
    int* dimMalluri;
    struct Mall* malluri = NULL;
    malluri = citesteVectorMallDinFisier("vectormalluri.txt", &dimMalluri);
    int* liniiMatrice;
    int* colMatrice;
    struct Mall** matriceMalluri = copieazaVectorInMatrice(malluri, &liniiMatrice, &colMatrice, &dimMalluri);
    printf("Matrice inainte de sortate:\n");
    afiseazaMatrice(matriceMalluri, liniiMatrice, colMatrice);

    matriceMalluri = sorteazaMatriceDupaLinii(matriceMalluri, liniiMatrice, colMatrice);
    printf("Matrice dupa sortare:\n");
    afiseazaMatrice(matriceMalluri, liniiMatrice, colMatrice);

    afiseazaVectorMalluri(malluri, &dimMalluri);
    for (int i = 0; i < liniiMatrice; i++) {
        freeMallVectorMemory(matriceMalluri[i], colMatrice);
    }

    freeMallVectorMemory(malluri, dimMalluri);
}