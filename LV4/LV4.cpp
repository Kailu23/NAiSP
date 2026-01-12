#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 500000
#define MAX 24

char init = 0;

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

int random(int max) {
	int result = 1;
	while (result < max && (rand() > RAND_MAX / 2)) {
		++result;
	}
	return result;
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
	element* new_entry = (element*)malloc(sizeof(element));
	int h = random(lista->height);
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

void TestSkipList() {
	time_t start, end;
	struct timespec ts1, ts2;
	double delta;

	start = clock();
	lista* head = inicijalizacija();

	for (int i = 0; i < N; i++) {
		ubaci(head, i);
	}

	end = clock();

	delta = (end - start) * 1000 / CLOCKS_PER_SEC;

	printf("Time taken to form skip list: %.2f ms\n", delta);

	start = clock();

	element* target = search(head, N);

	end = clock();

	delta = (end - start) * 1000 / CLOCKS_PER_SEC;

	printf("Time taken to search skip list: %.2f ms\n", delta);

	if (target == NULL) {
		printf("Value doesn't exist in skip list!\n");
	}
	else {
		printf("Value is %d\n", target->x);
	}
}

//Linked list

typedef struct Node {
	int x;
	struct Node* next;
} Node;

void InsertInList(Node* head, int value) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->x = value;
	if (head == NULL) {
		head = newNode;
		return;
	}
	newNode->next = head;
	head = newNode;
}

Node* SequentialSearchLinkedList(Node* head, int target) {
	Node* current = head;
	while (current != NULL) {
		if (current->x == target) return current; //Element found
		current = current->next;
	}
	return NULL; // Element not found
}

void TestLinkedList() {
	time_t start, end;
	double delta;

	start = clock();

	Node* head = NULL;

	for (int i = 0; i < N; i++) {
		InsertInList(head, i);
	}

	end = clock();

	delta = (end - start) * 1000 / CLOCKS_PER_SEC;

	printf("Time taken to form linked list: %.2f ms\n", delta);

	start = clock();

	Node* target = SequentialSearchLinkedList(head, N);

	end = clock();
	
	delta = (end - start) * 1000 / CLOCKS_PER_SEC;

	printf("Time taken to search linked list: %.2f ms\n", delta);
	if (target == NULL) {
		printf("Value doesn't exist in linked list!\n");
	}
	else {
		printf("Value is %d\n", target->x);
	}

}

int main(int argc, char* argv[]) {

	TestLinkedList();
	
	TestSkipList();

	return 0;
}