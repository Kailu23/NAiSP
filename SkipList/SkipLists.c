#include <stdlib.h>

#define MAX 32

int init = 0;

struct _element {
	int x;
	int height;
	struct _element* next[MAX];
}element1;

typedef struct _element element;

struct _lista {
	int height;
	element* header;
};
typedef struct _lista lista;

int random(int max) {
	int result = 1;
	while (result < max && (rand() > RAND_MAX / 2)) {
		++result;
	}
	return result;
}

struct element* inicijalizacija() {
	if (!init) {
		srand((unsigned int)time(NULL)); init = 1; 
	}
	lista* head = calloc(1, sizeof(lista)); 
	if (!head) return NULL;
	head->height = MAX;
	head->header = calloc(1, sizeof(element));
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
		prev[level] = curr; if (curr->next[level] == NULL) {
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
	element *new_entry = malloc(sizeof(element)); 
	int h = random(lista->height); 
	new_entry->height = h; 
	new_entry->x=x;
	int i;
	//inicijalizacija pokazivaca iznad izracunate razine
	for (i = MAX - 1; i > new_entry->height; -- i) {
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
	printf("Skip List:\n");
	for (int i = 0; i < list->height; i++) {
		element* current = list->header->next[i]; 
		printf("Level %d: ", i); 
		while (current != NULL) {
			printf("%d ", current->x); current = current->next[i]; 
		}
		printf("\n"); 
	}
}