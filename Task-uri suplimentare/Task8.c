#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#define MAX_GRAD 10

typedef struct Pacient Pacient;
struct Pacient {
	char* nume;
	int grad;
	int varsta;
};

typedef struct Heap Heap;
struct Heap {
	Pacient* items;
	int length;
};

Heap initHeap() {
	Heap h;

	h.items = NULL;
	h.length = 0;

	return h;
}

Pacient initPacient(const char* nume, int grad, int varsta) {
	Pacient p;
	p.nume = (char*)malloc(strlen(nume) + 1);
	strcpy(p.nume, nume);

	if (grad > MAX_GRAD)
		p.grad = MAX_GRAD;
	else if (grad < 1){
		p.grad = 1;
	}
	else {
		p.grad = grad;
	}

	p.varsta = varsta;

	return p;
}

void freeHeap(Heap h) {
	for (int i = 0; i < h.length; i++) {
		free(h.items[i].nume);
	}

	free(h.items);
	h.length = 0;
}

Heap insertPacient(Heap heap, Pacient p) {
	Heap newHeap;
	newHeap.length = heap.length + 1;
	newHeap.items = (Pacient*)malloc(sizeof(Pacient) * newHeap.length);

	for (int i = 0; i < heap.length; i++) {
		newHeap.items[i] = heap.items[i];
	}

	newHeap.items[heap.length] = p;

	int currentChildPosition = heap.length;

	while (currentChildPosition > 0) {
		int currentParentPosition = (currentChildPosition - 1) / 2;

		if (newHeap.items[currentChildPosition].grad > newHeap.items[currentParentPosition].grad) {
			Pacient aux = newHeap.items[currentChildPosition];
			newHeap.items[currentChildPosition] = newHeap.items[currentParentPosition];
			newHeap.items[currentParentPosition] = aux;

			currentChildPosition = currentParentPosition;
		}
		else {
			break;
		}
	}

	return newHeap;
}


void displayPacient(Pacient* p) {
	if (p) {
		printf("Pacientul %s are %d ani si gradul %d\n", p->nume, p->varsta, p->grad);
	}
}

void displayHeap(Heap heap, int index, int depth) {
	if (index < heap.length) {
		displayHeap(heap, 2 * index + 2, depth + 1);

		for (int i = 0; i < depth; i++) {
			printf("    ");
		}

		printf("|-- ");
		printf("Pacientul %s are %d ani si gradul %d\n", heap.items[index].nume, heap.items[index].varsta, heap.items[index].grad);

		displayHeap(heap, 2 * index + 1, depth + 1);
	}
}

void main() {
	Pacient p1 = initPacient("Ion", 5, 30);
	Pacient p2 = initPacient("Marcel", 8, 60);
	Pacient p3 = initPacient("Maria", 10, 54);
	Pacient p4 = initPacient("Lucian", 3, 16);
	Pacient p5 = initPacient("Gigi", 7, 28);
	Pacient p6 = initPacient("Alex", 9, 30);

	Heap heap = initHeap();
	heap = insertPacient(heap, p1);
	heap = insertPacient(heap, p2);
	heap = insertPacient(heap, p3);
	heap = insertPacient(heap, p4);
	heap = insertPacient(heap, p5);
	heap = insertPacient(heap, p6);

	displayHeap(heap, 0, 0);

	freeHeap(heap);
}