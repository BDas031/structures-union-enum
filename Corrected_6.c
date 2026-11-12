
// Unions
#include <stdio.h>
#include <string.h>

typedef union {
    int i;
    float f;
    char str[20];
} UnionData;

typedef struct {
    int i;
    float f;
    char str[20];
} StructData;

int main() {

    UnionData udata;
    StructData sdata;

    // Assigning values to structure
    sdata.i = 10;
    strcpy(sdata.str, "Struct Programming");
    sdata.f = 220.5;

    // Assigning values to union
    udata.i = 10;
    printf("udata.i: %d\n", udata.i);

    strcpy(udata.str, "Union Programming");
    printf("udata.str: %s\n", udata.str);

    udata.f = 220.5;
    printf("udata.f: %.2f\n\n", udata.f);

    // Value after overwriting
    printf("After overwriting:\n");
    printf("udata.f: %.2f\n\n", udata.f);

    // Memory Addresses - Union
    printf("udata.i: %p\n", (void *)&udata.i);
    printf("udata.str: %p\n", (void *)&udata.str);
    printf("udata.f: %p\n\n", (void *)&udata.f);

    // Memory Addresses - Structure
    printf("sdata.i: %p\n", (void *)&sdata.i);
    printf("sdata.str: %p\n", (void *)&sdata.str);
    printf("sdata.f: %p\n\n", (void *)&sdata.f);

    printf("Size of the Union - %zu\n", sizeof(UnionData));
    printf("Size of the Structure - %zu\n", sizeof(StructData));

    return 0;
}
