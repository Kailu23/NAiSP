#include "Hash.h"

void TestHashMap() {
    hashMap* map = (hashMap*)malloc(sizeof(hashMap));
    initializeHashMap(map, 100);

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

    //TestHashMap();

    hashMap* map = (hashMap*)malloc(sizeof(hashMap));
    initializeHashMap(map, 7);

    printf("Insertion:\n");
    map = insert(map, "A");
    map = insert(map, "AA");
    map = insert(map, "AB");
    map = insert(map, "B");
    map = insert(map, "BB");
    map = insert(map, "AAA");
    map = insert(map, "BA");

    printf("%s\n", search(map, "AAA"));
    map = delete(map, "AAA");
    printf("%s\n", search(map, "AAA"));

    return 0;
}