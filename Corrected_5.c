
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float width;
    float height;
    float area;
} Rectangle;

void calculate_area(Rectangle *r) {
    if (r == NULL) {
        return;
    }

    r->area = r->width * r->height;
}

Rectangle* create_rectangle_array(int size) {
    if (size <= 0) {
        return NULL;
    }

    Rectangle *rectangles = malloc(size * sizeof(Rectangle));

    if (rectangles == NULL) {
        return NULL;
    }

    return rectangles;
}

void add_rectangle(Rectangle *rectangles, int size,
                   int index, float width, float height) {
    if (rectangles == NULL || index < 0 || index >= size) {
        return;
    }

    rectangles[index].width = width;
    rectangles[index].height = height;

    calculate_area(&rectangles[index]);
}

void display_rectangles(Rectangle *rectangles, int size) {
    if (rectangles == NULL || size <= 0) {
        return;
    }

    for (int i = 0; i < size; i++) {
        printf("Rectangle %d: Width = %.2f, Height = %.2f, Area = %.2f\n",
               i, rectangles[i].width,
               rectangles[i].height, rectangles[i].area);
    }
}

void free_rectangle_array(Rectangle *rectangles) {
    free(rectangles);
}

int main() {
    int number_of_rectangles = 2;

    Rectangle *rectangles = create_rectangle_array(number_of_rectangles);

    if (rectangles == NULL) {
        printf("Memory allocation failed or invalid size!\n");
        return 1;
    }

    add_rectangle(rectangles, number_of_rectangles, 0, 5.0, 4.0);
    add_rectangle(rectangles, number_of_rectangles, 1, 6.5, 3.5);

    display_rectangles(rectangles, number_of_rectangles);

    free_rectangle_array(rectangles);

    return 0;
}
