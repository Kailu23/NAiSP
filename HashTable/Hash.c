#define _CRT_SECURE_NO_WARNINGS
#include "Hash.h"

#define __INTMAX16__ 32767
#define ASCII 63
#define PRIMENUMBER 31

void initializeHashMap(hashMap* map, int capacity) {
	map->capacity = capacity;
	map->numberOfElements = 0;

	map->array = (char**)calloc(map->capacity, sizeof(char*));
	return;
}

int hashFunction(hashMap* map, char* key) {
	int bucketIndex;
	int sum = 0, factor = PRIMENUMBER;
	for (int i = 0; i < strlen(key); i++) {
		sum = ((sum % map->capacity) + ((int)key[i] % ASCII) % map->capacity) % map->capacity;

		factor = (factor * PRIMENUMBER) % __INTMAX16__;
	}

	bucketIndex = sum;
	return bucketIndex;
}

hashMap* insert(hashMap* map, char* value) {
	if (value == NULL) {
		printf("Value is NULL\n");
		return map;
	}
	int bucketIndex = hashFunction(map, value);
	int tmp;
	float loadFactor;


	if (map->array[bucketIndex] == NULL) {
		map->array[bucketIndex] = value;
		printf("%s ubacen na mjesto array[%d]\n", value, bucketIndex);
		map->numberOfElements++;
	}
	else {
		tmp = bucketIndex + 1;
		while (map->array[tmp] != NULL) {
			tmp++;
		}

		if (tmp >= map->capacity) {
			tmp = 0;
			while (map->array[tmp] != NULL && tmp < bucketIndex) {
				if (map->array[tmp] == value) {
					printf("Vec postoji!\n");
				}
				tmp++;
			}

			if (tmp == bucketIndex) {
				printf("Nema slobodnog mjesta!\n");
				/*TODO : Rehashing*/
			}
			else {
				printf("%s ubacen na mjesto array[%d]\n", value, tmp);
				// ima mjesta za dodavanje
				map->array[tmp] = value;
				map->numberOfElements++;
			}
		}
		else {
			// ima mjesta za dodavanje
			printf("%s ubacen na mjesto array[%d]\n", value, tmp);
			map->array[tmp] = value;
			map->numberOfElements++;
		}
	}
	loadFactor = (float)map->numberOfElements / map->capacity;

	printf("Load factor je %3f\n", loadFactor);

	if (loadFactor >= 0.75) {
		printf("Rehashing...\n");
		map = rehash(map, 2.00);
	}
	return map;
}


hashMap* delete (hashMap* map, char* value) {
	int bucketIndex = hashFunction(map, value);
	float loadFactor;

	for (int i = 0; i < map->capacity; i++) {
		if (map->array[i] == value) {
			map->array[i] = NULL;
		}
	}
	
	loadFactor = (float)map->numberOfElements / map->capacity;
	printf("Load factor je %3f\n", loadFactor);
	if (loadFactor <= 0.25) {
		printf("Rehashing...\n");
		map = rehash(map, 0.50);
	}
	return map;
}

char* search(hashMap* map, char* value) {
	int bucketIndex = hashFunction(map, value);
	int tmp = 1;
	char* errorMessage = "Ne postoji!";

	if (map->array[bucketIndex] == value) {
		return value;
	}
	else {
		tmp += bucketIndex;
		while (map->array[tmp] != NULL && tmp < map->capacity) {
			if (map->array[tmp] == value) {
				return value;
			}
			tmp++;
		}
		if (tmp == map->capacity) {
			tmp = 0;
			while (map->array[tmp] != NULL && tmp < bucketIndex) {
				if (map->array[tmp] == value) {
					return value;
				}
				tmp++;
			}
			if (tmp >= bucketIndex) {
				return errorMessage;
			}
			else {
				if (map->array[tmp] == NULL) {
					return errorMessage;
				}
				else {
					return value;
				}
			}
		}
		else {
			return errorMessage;
		}
	}
}

hashMap* rehash(hashMap* map, float factor) {

	hashMap* newMap = (hashMap*)malloc(sizeof(hashMap));

	int newCapacity = map->capacity * factor;

	initializeHashMap(newMap, newCapacity);

	newMap->numberOfElements = map->numberOfElements;

	if (map->numberOfElements > newCapacity) {
		printf("Premala velicina hash tablice.\n");
		return map;
	}

	newMap->array = (char**)calloc(newMap->capacity, sizeof(char*));

	printf("Inserting...\n");

	for (int i = 0; i < map->capacity; i++) {
		if (map->array[i] != NULL) {
			insert(newMap, map->array[i]);
		}
	}

	printf("%d %d\n", newMap->capacity, newMap->numberOfElements);

	return newMap;


}