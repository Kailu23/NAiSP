#include "Hash.h"

void TestHashMap() {
    hashMap* map = (hashMap*)malloc(sizeof(hashMap));
    initializeHashMap(map);

    printf("%d %d\n", map->capacity, map->numberOfElements);

    map = insert(map, "Anjali");
    map = insert(map, "Anjali");
    map = insert(map, "Vartika");
    map = insert(map, "Manish");
    map = insert(map, "GeeksforGeeks");
    map = insert(map, "Mayank");

    printf("%s\n", search(map, "Anjali"));
    printf("%s\n", search(map, "Vartika"));
    printf("%s\n", search(map, "Manish"));
    printf("%s\n", search(map, "GeeksforGeeks"));
    printf("%s\n", search(map, "Mayank"));

    // Key is not inserted
    printf("%s\n", search(map, "randomKey"));

    printf("\nAfter deletion : \n");

    // Deletion of key
    printf("%s\n", search(map, "Anjali"));
    printf("\Deleting : \n");
    map = delete (map, "Anjali");
    printf("\Deleting : \n");
    map = delete (map, "Anjali");
    printf("%s\n", search(map, "Anjali"));

    printf("%d %d\n", map->capacity, map->numberOfElements);

}

int main() {

    TestHashMap();
	return 0;
}