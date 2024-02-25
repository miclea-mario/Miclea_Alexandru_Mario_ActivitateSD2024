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



int main() {

    struct Mall m1;

    citesteMall(&m1);

    printf("Numar magazine total: %d\n", getNrMagazineTotal(&m1));
    displayMall(&m1);

    free(m1.nume);
    free(m1.nrMagazineEtaj);

    return 0;

}