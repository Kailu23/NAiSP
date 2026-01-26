#define _CRT_SECURE_NO_WARNINGS
#include "SkipList.h"
#include <math.h>


char init = 0;

int randomm(int max) {
	int result = 1;
	while (result < max && (rand() > RAND_MAX / 2)) {
		++result;
	}
	return result;
}

lista* inicijalizacija() {
	if (!init) {
		srand((unsigned int)time(NULL)); init = 1;
	}
	lista* head = (lista*)calloc(1, sizeof(lista));
	if (!head) return NULL;
	head->height = MAX;
	head->header = (element*)calloc(1, sizeof(element));
	for (int i = 0; i < MAX; i++) {
		head->header->next[i] = NULL;
	}
	head->header->x = -1;
	return head;
}

void ubaci(lista* lista, int x) {
	element* prev[MAX];
	element* curr = lista->header;
	int level = lista->height - 1;
	while (curr != NULL && level >= 0) {
		prev[level] = curr; 
		if (curr->next[level] == NULL) {
			--level;
		}
		else {
			if (curr->next[level]->x == x) {
				//pronasao vrijednost - nema akcije
				curr->next[level]->x = x; return;
			}
			else if (curr->next[level]->x > x) {
				//spustamo se na razinu ispod
				--level;
			}
			else {
				//pomjeramo se u desno
				curr = curr->next[level];
			}

		}

	}
	//ubacujemo novi element - nije pronadjeno nista 
	element* new_entry = malloc(sizeof(element));
	int h = randomm(lista->height);
	new_entry->height = h;
	new_entry->x = x;
	int i;
	//inicijalizacija pokazivaca iznad izracunate razine
	for (i = MAX - 1; i > new_entry->height; --i) {
		new_entry->next[i] = NULL;
	}
	// Tie in other pointers
	for (i = new_entry->height - 1; i >= 0; --i) {
		new_entry->next[i] = prev[i]->next[i];
		prev[i]->next[i] = new_entry;
	}
}

void delete(lista* list, int key) {
	element* current = list->header;
	element* prev[MAX];
	int flag = 0;
	for (int i = 0; i < MAX; i++) {
		prev[i] = NULL;
	}
	for (int i = list->height - 1; i >= 0; i--) {
		while (current->next[i] != NULL && current->next[i]->x < key) {
			current = current->next[i];
		}
		if (current->next[i] != NULL) {
			if (current->next[i]->x == key) {
				flag = 1;
				prev[i] = current;
			}
			else {
				prev[i] = NULL;
			}

		}

	}
	if (flag == 1) {
		element* tmp = malloc(sizeof(element));
		for (int i = 0; i < MAX; i++) {
			if (i == 0) {
				tmp = prev[i]->next[i];
				prev[i]->next[i] = prev[i]->next[i]->next[i];
			}
			else {
				if (prev[i] != NULL) {
					prev[i]->next[i] = prev[i]->next[i]->next[i];
				}

			}

		}
		free(tmp);
	}
	else {
		printf("Element nije pronadjen!\n");
	}
}

element* search(lista* list, int key) {
	element* current = list->header;
	int promjene;
	for (int i = list->height - 1; i >= 0; i--) {
		while (current->next[i] != NULL && current->next[i]->x < key) {
			current = current->next[i];
		}
		if (current->next[i] != NULL) {
			if (current->next[i]->x == key) {
				current = current->next[i]; promjene = i;
				printf("Pronadjen...height=%d\n", i);
				break;
			}

		}

	}
	if (current != NULL && current->x == key) {
		return current;
	}
	return NULL;
}

void printSkipList(lista* list) {
	FILE* ptr;
	ptr = fopen("output.txt", "a");
	printf("Skip List:\n");
	for (int i = 0; i < list->height; i++) {
		element* current = list->header->next[i];
		printf("Level %d: ", i);
		while (current != NULL) {
			printf("%d ", current->x); 
			current = current->next[i];
		}
		printf("\n");
	}
}

void fprintSkipList(lista* list, int size) {
	FILE* ptr;
	ptr = fopen("output.txt", "a");
	fprintf(ptr, "Skip List:\n");
	for (int i = 0; i < list->height; i++) {

		fprintf(ptr, "Level %d: ", i);

		for (int j = 0; j < 2 * i; j++) {
			fprintf(ptr, " ");
		}
		element* current = list->header->next[i];
		for (int k = 0; k < 2 * (list->height - i) && current != NULL; k++) {
			fprintf(ptr, "%d ", current->x);
			if (current->next[i] == NULL) {
				fprintf(ptr, "* ");
				break;
			}
			else {
				current = current->next[i];
			}
		}

		fprintf(ptr, "\n");
	}
	fclose(ptr);
}

int CalculateHeight(unsigned int index) {
	int i = 1;
	while (index % (int)pow(2, i) == 0) {
		i++;
	}
	return i;
}

void MakePerfect(lista* lista) {
	if (!lista || !lista->header) return;

	element* nodes[N];
	unsigned int index;
	int count = 0;

	element* current = lista->header->next[0];
	while (current != NULL && count < N) {
		nodes[count++] = current;
		current = current->next[0];
	}

	if (count == 0) return;

	for (int i = 0; i < count; i++) {
		index = i + 1;
		nodes[i]->height = CalculateHeight(index);
	}

	for (int i = 0; i < count; i++) {
		for (int lvl = 0; lvl < MAX; lvl++) {
			nodes[i]->next[lvl] = NULL;
		}
	}
	for (int lvl = 0; lvl < MAX; lvl++) {
		lista->header->next[lvl] = NULL;
	}

	int height;
	for (int level = 0; level < lista->height; level++) {
		element* previous = lista->header;
		for (int i = 0; i < count; i++) {
			index = i + 1;
			height = nodes[i]->height;
			if (height > level && index % (1u << level) == 0) {
				previous->next[level] = nodes[i];
				previous = nodes[i];
			}
		}
		if (previous != NULL) {
			previous->next[level] = NULL;
		}
	}
}

void FreeMemory(lista* lista) {
	element* tmp;
	while (lista->header != NULL) {
		tmp = lista->header;
		lista->header = lista->header->next[0];
		free(tmp);
	}
	free(lista);
}