#include <stdio.h>
#include <malloc.h>

typedef struct Biblioteca Biblioteca;
typedef struct Nod Nod;

struct Biblioteca {
    char* nume;
    int nrCarti;
    int nrCititori;
};

struct Nod {
    Biblioteca info;
    Nod* next;
};

Biblioteca initializare(const char* nume, int nrCarti, int nrCititori) {
    Biblioteca biblioteca;
    biblioteca.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
    strcpy(biblioteca.nume, nume);

    biblioteca.nrCarti = nrCarti;
    biblioteca.nrCititori = nrCititori;

    return biblioteca;
}

Nod* inserareInceput(Nod* cap, Biblioteca b) {
    Nod* nod = (Nod*)malloc(sizeof(Nod));
    nod->info = initializare(b.nume, b.nrCarti, b.nrCititori);
    nod->next = cap;

    return nod;
}

void afisareLista(Nod* cap) {
    while (cap != NULL) {
        // procesare
        printf("Biblioteca %s are %d carti si %d cititori.\n", cap->info.nume, cap->info.nrCarti, cap->info.nrCititori);
        cap = cap->next;
    }
}

void inserareSfarsit(Nod** cap, Biblioteca biblioteca) {
    Nod* sfarsit = (Nod*)malloc(sizeof(Nod));
    sfarsit->info = initializare(biblioteca.nume, biblioteca.nrCititori, biblioteca.nrCititori);
    sfarsit->next = NULL;

    if ((*cap) != NULL) {
        Nod* copie = (*cap);

        while (copie->next != NULL)
            copie = copie->next;

        copie->next = sfarsit;
    }
}

void main() {
    Nod* cap = NULL;
    Biblioteca b1 = initializare("Mihai Eminescu", 10, 12);
    Biblioteca b2 = initializare("Ion Creanga", 10, 12);
    Biblioteca b3 = initializare("Ion Creanga", 10, 12);

    cap = inserareInceput(cap, b1);
    cap = inserareInceput(cap, b2);
    cap = inserareInceput(cap, b3);
    afisareLista(cap);
}