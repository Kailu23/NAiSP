#include <stdio.h>
#include <stdlib.h>

#define MAX 4

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

int random(int max);

lista* inicijalizacija();

void ubaci(lista* lista, int x);

void delete(lista* list, int key);

element* search(lista* list, int key);

void printSkipList(lista* list);


//my custom functions

void fprintSkipList(lista* list);

void Insert(lista* lista, int x);

void RecalculateHeight(element* node, int x);

void FreeMemory(lista* lista);

