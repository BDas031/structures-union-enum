
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Enum for data types
typedef enum {
    TYPE_EMPTY,
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_CHAR,
    TYPE_STRING
} DataType;


// Union to store different data types
typedef union {
    int int_value;
    float float_value;
    char char_value;
    char *string_value;
} Data;


// Structure containing data and its type
typedef struct {
    Data data;
    DataType type;
} Container;


// Function declarations
void container_init(Container *c);
void container_clear(Container *c);

int set_int(Container *c, int value);
int set_float(Container *c, float value);
int set_char(Container *c, char value);
int set_string(Container *c, const char *value);

int get_int(const Container *c, int *value);
int get_float(const Container *c, float *value);
int get_char(const Container *c, char *value);
int get_string(const Container *c, const char **value);

void container_print(const Container *c);
const char* container_type_name(const Container *c);

int container_copy(Container *destination, const Container *source);


// Initialize container
void container_init(Container *c) {
    if (c != NULL) {
        c->type = TYPE_EMPTY;
    }
}


// Clear container
void container_clear(Container *c) {
    if (c == NULL) return;

    if (c->type == TYPE_STRING) {
        free(c->data.string_value);
    }

    c->type = TYPE_EMPTY;
}


// Set integer
int set_int(Container *c, int value) {
    if (c == NULL) return 0;

    container_clear(c);

    c->data.int_value = value;
    c->type = TYPE_INT;

    return 1;
}


// Set float
int set_float(Container *c, float value) {
    if (c == NULL) return 0;

    container_clear(c);

    c->data.float_value = value;
    c->type = TYPE_FLOAT;

    return 1;
}


// Set character
int set_char(Container *c, char value) {
    if (c == NULL) return 0;

    container_clear(c);

    c->data.char_value = value;
    c->type = TYPE_CHAR;

    return 1;
}


// Set string
int set_string(Container *c, const char *value) {
    if (c == NULL || value == NULL) return 0;

    // Allocate memory for a new string
    char *new_string = malloc(strlen(value) + 1);

    if (new_string == NULL) {
        return 0;
    }

    // Copy string into allocated memory
    memcpy(new_string, value, strlen(value) + 1);

    // Clear previous value
    container_clear(c);

    c->data.string_value = new_string;
    c->type = TYPE_STRING;

    return 1;
}


// Get integer
int get_int(const Container *c, int *value) {
    if (c == NULL || value == NULL || c->type != TYPE_INT) {
        return 0;
    }

    *value = c->data.int_value;
    return 1;
}


// Get float
int get_float(const Container *c, float *value) {
    if (c == NULL || value == NULL || c->type != TYPE_FLOAT) {
        return 0;
    }

    *value = c->data.float_value;
    return 1;
}


// Get character
int get_char(const Container *c, char *value) {
    if (c == NULL || value == NULL || c->type != TYPE_CHAR) {
        return 0;
    }

    *value = c->data.char_value;
    return 1;
}


// Get string
int get_string(const Container *c, const char **value) {
    if (c == NULL || value == NULL || c->type != TYPE_STRING) {
        return 0;
    }

    *value = c->data.string_value;
    return 1;
}


// Get type name
const char* container_type_name(const Container *c) {
    if (c == NULL) return "Invalid";

    switch (c->type) {
        case TYPE_INT: return "Integer";
        case TYPE_FLOAT: return "Float";
        case TYPE_CHAR: return "Character";
        case TYPE_STRING: return "String";
        case TYPE_EMPTY: return "Empty";
        default: return "Invalid";
    }
}


// Display container value
void container_print(const Container *c) {
    if (c == NULL) {
        printf("Invalid container!\n");
        return;
    }

    switch (c->type) {
        case TYPE_INT:
            printf("%d", c->data.int_value);
            break;

        case TYPE_FLOAT:
            printf("%.2f", c->data.float_value);
            break;

        case TYPE_CHAR:
            printf("%c", c->data.char_value);
            break;

        case TYPE_STRING:
            printf("%s", c->data.string_value);
            break;

        case TYPE_EMPTY:
            printf("Empty container");
            break;

        default:
            printf("Invalid type");
    }
}


// Copy container
int container_copy(Container *destination, const Container *source) {
    if (destination == NULL || source == NULL) return 0;

    // Self-copy
    if (destination == source) return 1;

    if (source->type == TYPE_STRING) {
        // Make an independent copy of the string
        char *new_string = malloc(
            strlen(source->data.string_value) + 1
        );

        if (new_string == NULL) return 0;

        memcpy(new_string, source->data.string_value,
               strlen(source->data.string_value) + 1);

        container_clear(destination);

        destination->data.string_value = new_string;
        destination->type = TYPE_STRING;
    }
    else if (source->type == TYPE_INT ||
             source->type == TYPE_FLOAT ||
             source->type == TYPE_CHAR ||
             source->type == TYPE_EMPTY) {

        Data temp = source->data;

        container_clear(destination);

        destination->data = temp;
        destination->type = source->type;
    }
    else {
        return 0;
    }

    return 1;
}


// Main function
int main() {

    // Create six containers
    Container records[6];

    for (int i = 0; i < 6; i++) {
        container_init(&records[i]);
    }

    Container copy;
    container_init(&copy);


    // Store different values
    set_int(&records[0], 10);
    set_float(&records[1], 3.14);
    set_char(&records[2], 'A');
    set_string(&records[3], "Hello");
    set_int(&records[4], 0);
    set_string(&records[5], "Data");


    // Display all records
    printf("--- Container Records ---\n");

    for (int i = 0; i < 6; i++) {
        printf("Record %d | Type: %s | Value: ",
               i + 1, container_type_name(&records[i]));

        container_print(&records[i]);
        printf("\n");
    }


    // Deep copy demonstration
    printf("\n--- Deep Copy Demonstration ---\n");

    container_copy(&copy, &records[5]);

    printf("Original: ");
    container_print(&records[5]);

    printf("\nCopied: ");
    container_print(&copy);


    // Change original string
    set_string(&records[5], "Changed");

    printf("\nAfter changing original:\n");

    printf("Original: ");
    container_print(&records[5]);

    printf("\nCopied: ");
    container_print(&copy);
    printf("\n");


    // Changing data types
    printf("\n--- Changing Data Types ---\n");

    set_int(&records[3], 100);
    container_print(&records[3]);

    printf("\n");

    set_string(&records[3], "Hello Again");
    container_print(&records[3]);

    printf("\n");

    set_float(&records[3], 45.5);
    container_print(&records[3]);

    printf("\n");


    // Test integer zero
    printf("\n--- Testing Integer Zero ---\n");

    int number;

    set_int(&records[4], 0);

    if (get_int(&records[4], &number)) {
        printf("Integer value: %d\n", number);
    }


    // Test wrong type getter
    printf("\n--- Wrong Type Test ---\n");

    float decimal;

    if (!get_float(&records[4], &decimal)) {
        printf("Cannot get float from an integer container!\n");
    }


    // Test empty string
    printf("\n--- Empty String Test ---\n");

    set_string(&records[2], "");
    container_print(&records[2]);
    printf("\n");


    // Test repeated clearing
    printf("\n--- Clear Test ---\n");

    container_clear(&records[2]);
    container_clear(&records[2]);

    container_print(&records[2]);
    printf("\n");


    // Test self-copy
    printf("\n--- Self Copy Test ---\n");

    container_copy(&records[0], &records[0]);
    container_print(&records[0]);
    printf("\n");


    // Display memory sizes
    printf("\n--- Memory Information ---\n");

    printf("Union Size: %zu bytes\n", sizeof(Data));
    printf("Container Size: %zu bytes\n", sizeof(Container));


    // Free all allocated memory
    for (int i = 0; i < 6; i++) {
        container_clear(&records[i]);
    }

    container_clear(&copy);

    printf("\nAll memory released successfully!\n");

    return 0;
}
