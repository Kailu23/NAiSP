#ifndef SL

#define SL "SkipList.h"
#endif
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 4
#define N 16

struct _element {
	int x;
	int height;
	struct _element* next[MAX];
};

typedef struct _element element;

struct _lista {
	int height;
	element* header;
};
typedef struct _lista lista;

int randomm(int max);

lista* inicijalizacija();

void ubaci(lista* lista, int x);

void delete(lista* list, int key);

element* search(lista* list, int key);

void printSkipList(lista* list);

void fprintSkipList(lista* list, int size);

void FreeMemory(lista* lista);

int CalculateHeight(unsigned int number);

void MakePerfect(lista* lista);
