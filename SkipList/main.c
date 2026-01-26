#ifndef SL

#define SL "SkipList.h"
#include SL

#endif


int main() {
	int numbers[N] = {2, 8, 12, 22, 50, 66, 30, 90, 33, 45, 68, 70, 99, 1, 5, 23};
	
	lista* head = inicijalizacija();
	for (int i = 0; i < N; i++) {
		ubaci(head, numbers[i]);
	}
	printSkipList(head);

	MakePerfect(head);
	printSkipList(head);

	FreeMemory(head);

	return 0;
}