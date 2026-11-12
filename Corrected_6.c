//Union

#include <stdio.h>
#include <string.h>
#include <stddef.h>

// Union
typedef union {
    int i;
    float f;
    char str[20];
} UnionData;

// Structure
typedef struct {
    int i;
    float f;
    char str[20];
} StructData;

// Enum
typedef enum {
    VALUE_INT,
    VALUE_FLOAT,
    VALUE_TEXT
} ValueType;

// Tagged Union
typedef struct {
    UnionData data;
    ValueType type;
} TaggedValue;


// Functions to set values
void set_int(TaggedValue *v, int value) {
    v->data.i = value;
    v->type = VALUE_INT;
}

void set_float(TaggedValue *v, float value) {
    v->data.f = value;
    v->type = VALUE_FLOAT;
}

void set_text(TaggedValue *v, char value[]) {
    if (strlen(value) >= 20) {
        printf("String too long! Maximum 19 characters.\n");
        return;
    }

    strcpy(v->data.str, value);
    v->type = VALUE_TEXT;
}


// Display active value
void display_value(TaggedValue *v) {
    switch (v->type) {
        case VALUE_INT:
            printf("Integer: %d\n", v->data.i);
            break;

        case VALUE_FLOAT:
            printf("Float: %.2f\n", v->data.f);
            break;

        case VALUE_TEXT:
            printf("String: %s\n", v->data.str);
            break;

        default:
            printf("Invalid data type!\n");
    }
}


int main() {

    UnionData udata;
    StructData sdata;

    // Structure values
    sdata.i = 10;
    sdata.f = 220.5;
    strcpy(sdata.str, "Struct Programming");

    // Union values one at a time
    udata.i = 10;
    printf("Union Integer: %d\n", udata.i);

    strcpy(udata.str, "Union Programming");
    printf("Union String: %s\n", udata.str);

    udata.f = 220.5;
    printf("Union Float: %.2f\n", udata.f);


    // Union addresses
    printf("\n--- Union Addresses ---\n");
    printf("Integer: %p\n", (void *)&udata.i);
    printf("Float: %p\n", (void *)&udata.f);
    printf("String: %p\n", (void *)&udata.str);


    // Structure addresses
    printf("\n--- Structure Addresses ---\n");
    printf("Integer: %p\n", (void *)&sdata.i);
    printf("Float: %p\n", (void *)&sdata.f);
    printf("String: %p\n", (void *)&sdata.str);


    // Size comparison
    printf("\n--- Memory Size ---\n");
    printf("Union Size: %zu bytes\n", sizeof(UnionData));
    printf("Structure Size: %zu bytes\n", sizeof(StructData));

    printf("100 Union Records: %zu bytes\n",
           100 * sizeof(UnionData));

    printf("100 Structure Records: %zu bytes\n",
           100 * sizeof(StructData));


    // Structure offsets
    printf("\n--- Structure Offsets ---\n");
    printf("Integer: %zu\n", offsetof(StructData, i));
    printf("Float: %zu\n", offsetof(StructData, f));
    printf("String: %zu\n", offsetof(StructData, str));


    // Alignment
    printf("\n--- Memory Alignment ---\n");
    printf("Union Alignment: %zu\n", _Alignof(UnionData));
    printf("Structure Alignment: %zu\n", _Alignof(StructData));


    // Five tagged records
    printf("\n--- Tagged Union Records ---\n");

    TaggedValue records[5];

    set_int(&records[0], 10);
    set_float(&records[1], 220.5);
    set_text(&records[2], "Union Programming");
    set_int(&records[3], 50);
    set_text(&records[4], "Hello");

    for (int i = 0; i < 5; i++) {
        printf("\nRecord %d:\n", i + 1);
        display_value(&records[i]);
    }


    // Changing data types
    printf("\n--- Changing Data Type ---\n");

    TaggedValue test;

    set_int(&test, 100);
    display_value(&test);

    set_text(&test, "Hello");
    display_value(&test);

    set_float(&test, 45.5);
    display_value(&test);


    // Invalid string test
    printf("\n--- String Validation ---\n");
    set_text(&test, "12345678901234567890");


    // Invalid tag test
    printf("\n--- Invalid Tag Test ---\n");

    TaggedValue invalid;
    invalid.type = 99;
    display_value(&invalid);


    // Tagged record size
    printf("\nTagged Record Size: %zu bytes\n",
           sizeof(TaggedValue));

    return 0;
}
