#ifndef SL

#define SL "SkipList.h"
#include SL

#endif

#define N 8

int main() {
	int numbers[N] = {2,8,12,22,50,66,30,90};
	
	element* head = inicijalizacija();
	for (int i = 0; i < N - 1; i++) {
		ubaci(head, numbers[i]);
	}
	printSkipList(head);
	return 0;
}