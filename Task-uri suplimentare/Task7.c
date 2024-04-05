/* 
Se doreste gestiunea cladirilor din Bucuresti in funtie de anul construirii.
Acest lucru va ajuta la stabilire riscului seismic al acestora.

1. Sa se creeze o tabela de dispersie pentru stocarea cladirilor din Bucuresti
(structura Cladire contine ce atribute vreti voi dar va contine obligatoriu anul 
construirii si un id unic).campul folosit pentru clusterizare este anul construirii cladirii.

2. Implementati o functie care afiseaza cladirile dintr - un cluster
(construite intr - un an primit ca parametru).

3. Implementati o functie care sterge o cladire pentru care se primeste id - ul si anul construirii.
4. Implementati o functie care sterge o cladire pentru care se primeste doar id - ul cladirii.

5. Observatii diferenta dintre functia implementata la 4 si functia de la 5.

6. Implementati o functie care salveaza intr - un vector toate  cladirile 
dintr - un an primit ca parametru.Realizati deep copy, astfel incat elementele 
din vector sa fie diferentiate de cele din tabela de dispersie.Aveti grija la 
alocarea de spatiu, deoarece trebuie sa stabiliti pentru cate elemente veti aloca spatiu.

7. Implementati o functie care modifica anul construirii unei cladiri identificate prin ID.
Functia primeste ca parametri : id - ul cladirii, vechiul an de constructie si noul an 
de constructie.Aveti grija se modifica valoarea atributului folosit pentru clusterizare.
*/

#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define SIZE 5

typedef struct Cladire Cladire;
struct Cladire {
	int id;
	int anConstruire;
};

typedef struct Nod Nod;
struct Nod {
	Cladire info;
	Nod* next;
};

typedef struct HashTable HashTable;
struct HashTable {
	Nod** vector;
	int length;
};

Cladire initCladire(int id, int anConstruire) {
	Cladire cladire;
	cladire.id = id;
	cladire.anConstruire = anConstruire;

	return cladire;
}

HashTable initHashTable(int length) {
	HashTable hashTable;

	hashTable.length = length;
	hashTable.vector = (Nod**)malloc(sizeof(Nod*) * length);

	for (int i = 0; i < length; i++) {
		hashTable.vector[i] = NULL;
	}

	return hashTable;
}

int hashCode(int an) {
	int poz = 0;
	int aux = an;

	while (an) {
		poz += an % 10;
		an /= 10;
	}
	return (poz*aux + aux/10) % SIZE;
}

void insereazaCladire(HashTable h, Cladire c) {
	int poz = hashCode(c.anConstruire);

	Nod* nod_adaugat = (Nod*)malloc(sizeof(Nod));
	nod_adaugat->info = c;
	nod_adaugat->next = NULL;

	if (h.vector[poz] != NULL) {
		Nod* temp = h.vector[poz];
		
		while (temp->next) {
			temp = temp->next;
		}

		temp->next = nod_adaugat;
	}
	else {
		h.vector[poz] = nod_adaugat;
	}
}

void afiseazaCladire(Cladire c) {
	printf("Caldirea #%d a fost construita in anul %d.\n", c.id, c.anConstruire);
}

void afiseazaLista(Nod* nod) {
	while (nod) {
		afiseazaCladire(nod->info);
		nod = nod->next;
	}
}

void afiseazaHashTable(HashTable h) {
	for (int i = 0; i < h.length; i++) {
		if (h.vector[i] != NULL) {
			printf("Clusterul %d:\n", i);
			afiseazaLista(h.vector[i]);
		}
	}
}

void afiseazaCluster(HashTable h, int an) {
	int poz = hashCode(an);
	afiseazaLista(h.vector[poz]);
}

void stergeCladireCluster(Nod** nod, int id) {
	Nod* temp = *nod;
	Nod* temp2 = NULL;

	if (temp != NULL && temp->info.id == id) {
		*nod = temp->next;
		free(temp);
		return;
	}

	while (temp != NULL && temp->info.id != id) {
		temp2 = temp;
		temp = temp->next;
	}

	if (temp == NULL) {
		return;
	}

	temp2->next = temp->next;
	free(temp);
}


void stergeCladire(HashTable h, int id, int an) {
	int poz = hashCode(an);

	stergeCladireCluster(&h.vector[poz], id);
}

void stergeCladireDupaID(HashTable h, int id) {
	/* 
	Nu stim pe ce cluster trebuie realizata stergera
	Verificam pentru fiecare cluster
	*/

	for (int i = 0; i < h.length; i++) {
		if (h.vector[i] != NULL) {
			stergeCladireCluster(&h.vector[i], id);
		}
	}
}

Cladire* hashTableToVector(HashTable h, int an, int* dim) {
	int poz = hashCode(an);
	(*dim) = 0;

	Nod* temp = h.vector[poz];

	while (temp) {
		if (temp->info.anConstruire == an)
			(*dim)++;

		temp = temp->next;
	}

	Cladire* cladiri = (Cladire*)malloc(sizeof(Cladire) * (*dim));

	temp = h.vector[poz];
	int i = 0;

	while (temp) {
		if (temp->info.anConstruire == an)
			cladiri[i++] = initCladire(temp->info.id, temp->info.anConstruire);

		temp = temp->next;
	}

	return cladiri;
}

void modificaAnCladire(HashTable h, int id, int an, int an_nou) {
	stergeCladire(h, id, an);
	Cladire c;
	c.id = id;
	c.anConstruire = an_nou;
	insereazaCladire(h, c);
}

void main() {
	Cladire cladiri[20];
	HashTable h = initHashTable(SIZE);

	for (int i = 0; i < 20; i++) {
		cladiri[i] = initCladire(i, i + 1975);
	}

	for (int i = 0; i < 20; i++) {
		insereazaCladire(h, cladiri[i]);
	}

	printf("Afisare HashTable\n");
	afiseazaHashTable(h);

	printf("\n\nAfisare cluster corespunzator hash-ului pentru anul 1980\n");
	afiseazaCluster(h, 1980);

	stergeCladire(h, 15, 1990);
	printf("\n\nAfisare cluster dupa stergere\n");
	afiseazaCluster(h, 1990);

	stergeCladireDupaID(h, 8);
	printf("\n\nAfisare cluster dupa stergere\n");
	afiseazaCluster(h, 1979);

	int* dim = 0;
	Cladire* vectorCladiri = hashTableToVector(h, 1992, &dim);

	printf("\n\nAfisare vector cladiri anul 1992\n");
	for (int i = 0; i < dim; i++) {
		afiseazaCladire(vectorCladiri[i]);
	}

	printf("\n\nAfisare hashtable dupa modificarea anului cladirii #10 din 1985 in 2003\n");
	modificaAnCladire(h, 10, 1985, 2003);
	afiseazaHashTable(h);
}