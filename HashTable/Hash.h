#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>


typedef struct _hashMap {
	int numberOfElements, capacity;

	char** array;
} hashMap;


void initializeHashMap(hashMap* map);

int hashFunction(hashMap* map, char* key);

hashMap* insert(hashMap* map, char* value);

hashMap* delete(hashMap* map, char* value);

char* search(hashMap* map, char* value);

hashMap* rehash(hashMap* map, float factor);

