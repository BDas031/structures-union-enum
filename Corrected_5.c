#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_RECTANGLES 1000

typedef struct {
    int id;
    float width;
    float height;
    float area;
    float perimeter;
} Rectangle;

// Function declarations
Rectangle* create_rectangle_array(int capacity);
void calculate_geometry(Rectangle *r);
void add_rectangle(Rectangle **r, int *count, int *capacity);
void display_rectangles(Rectangle r[], int count);
void search_rectangle(Rectangle r[], int count);
void update_rectangle(Rectangle r[], int count);
void delete_rectangle(Rectangle r[], int *count);
void display_summary(Rectangle r[], int count);
void classify_rectangles(Rectangle r[], int count);
void sort_rectangles(Rectangle r[], int count);
void filter_rectangles(Rectangle r[], int count);
int find_rectangle(Rectangle r[], int count, int id);


// Main function
int main() {
    int capacity, count = 0, choice;

    printf("Enter initial capacity (1-1000): ");
    if (scanf("%d", &capacity) != 1 ||
        capacity < 1 || capacity > MAX_RECTANGLES) {
        printf("Invalid capacity!\n");
        return 1;
    }

    Rectangle *rectangles = create_rectangle_array(capacity);

    if (rectangles == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    while (1) {
        printf("\n===== RECTANGLE MANAGEMENT SYSTEM =====\n");
        printf("1. Add Rectangle\n");
        printf("2. Display Rectangles\n");
        printf("3. Search Rectangle\n");
        printf("4. Update Rectangle\n");
        printf("5. Delete Rectangle\n");
        printf("6. Area Summary\n");
        printf("7. Classify Rectangles\n");
        printf("8. Sort by Area\n");
        printf("9. Filter by Area\n");
        printf("10. Exit\n");

        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            break;
        }

        switch (choice) {
            case 1:
                add_rectangle(&rectangles, &count, &capacity);
                break;

            case 2:
                display_rectangles(rectangles, count);
                break;

            case 3:
                search_rectangle(rectangles, count);
                break;

            case 4:
                update_rectangle(rectangles, count);
                break;

            case 5:
                delete_rectangle(rectangles, &count);
                break;

            case 6:
                display_summary(rectangles, count);
                break;

            case 7:
                classify_rectangles(rectangles, count);
                break;

            case 8:
                sort_rectangles(rectangles, count);
                break;

            case 9:
                filter_rectangles(rectangles, count);
                break;

            case 10:
                free(rectangles);
                printf("Program ended.\n");
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }

    free(rectangles);
    return 0;
}


// Allocate memory
Rectangle* create_rectangle_array(int capacity) {
    return malloc(capacity * sizeof(Rectangle));
}


// Calculate area and perimeter
void calculate_geometry(Rectangle *r) {
    r->area = r->width * r->height;
    r->perimeter = 2 * (r->width + r->height);
}


// Find rectangle using ID
int find_rectangle(Rectangle r[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (r[i].id == id) {
            return i;
        }
    }

    return -1;
}


// Add rectangle
void add_rectangle(Rectangle **r, int *count, int *capacity) {
    Rectangle temp;

    printf("Enter rectangle ID: ");
    if (scanf("%d", &temp.id) != 1) {
        printf("Invalid input!\n");
        return;
    }

    if (temp.id <= 0 || find_rectangle(*r, *count, temp.id) != -1) {
        printf("Invalid or duplicate ID!\n");
        return;
    }

    printf("Enter width: ");
    if (scanf("%f", &temp.width) != 1) {
        printf("Invalid input!\n");
        return;
    }

    printf("Enter height: ");
    if (scanf("%f", &temp.height) != 1) {
        printf("Invalid input!\n");
        return;
    }

    if (!isfinite(temp.width) || !isfinite(temp.height) ||
        temp.width <= 0 || temp.height <= 0) {
        printf("Dimensions must be finite and positive!\n");
        return;
    }

    calculate_geometry(&temp);

    if (!isfinite(temp.area) || !isfinite(temp.perimeter)) {
        printf("Dimensions are too large!\n");
        return;
    }

    // Increase capacity when full
    if (*count == *capacity) {
        if (*capacity >= MAX_RECTANGLES) {
            printf("Maximum capacity reached!\n");
            return;
        }

        int new_capacity = *capacity * 2;

        if (new_capacity > MAX_RECTANGLES) {
            new_capacity = MAX_RECTANGLES;
        }

        Rectangle *new_array = realloc(
            *r, new_capacity * sizeof(Rectangle));

        if (new_array == NULL) {
            printf("Memory allocation failed!\n");
            return;
        }

        *r = new_array;
        *capacity = new_capacity;
    }

    (*r)[*count] = temp;
    (*count)++;

    printf("Rectangle added successfully!\n");
}


// Display all rectangles
void display_rectangles(Rectangle r[], int count) {
    if (count == 0) {
        printf("No rectangles available!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        printf("\nID: %d\n", r[i].id);
        printf("Width: %.2f\n", r[i].width);
        printf("Height: %.2f\n", r[i].height);
        printf("Area: %.2f\n", r[i].area);
        printf("Perimeter: %.2f\n", r[i].perimeter);
    }
}


// Search rectangle
void search_rectangle(Rectangle r[], int count) {
    int id;

    printf("Enter rectangle ID: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input!\n");
        return;
    }

    int index = find_rectangle(r, count, id);

    if (index == -1) {
        printf("Rectangle not found!\n");
        return;
    }

    printf("ID: %d\n", r[index].id);
    printf("Width: %.2f\n", r[index].width);
    printf("Height: %.2f\n", r[index].height);
    printf("Area: %.2f\n", r[index].area);
    printf("Perimeter: %.2f\n", r[index].perimeter);
}


// Update rectangle
void update_rectangle(Rectangle r[], int count) {
    int id;

    printf("Enter rectangle ID to update: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input!\n");
        return;
    }

    int index = find_rectangle(r, count, id);

    if (index == -1) {
        printf("Rectangle not found!\n");
        return;
    }

    Rectangle temp = r[index];

    printf("Enter new width: ");
    if (scanf("%f", &temp.width) != 1) {
        printf("Invalid input!\n");
        return;
    }

    printf("Enter new height: ");
    if (scanf("%f", &temp.height) != 1) {
        printf("Invalid input!\n");
        return;
    }

    if (!isfinite(temp.width) || !isfinite(temp.height) ||
        temp.width <= 0 || temp.height <= 0) {
        printf("Invalid dimensions!\n");
        return;
    }

    calculate_geometry(&temp);

    if (!isfinite(temp.area) || !isfinite(temp.perimeter)) {
        printf("Dimensions are too large!\n");
        return;
    }

    r[index] = temp;

    printf("Rectangle updated successfully!\n");
}


// Delete rectangle
void delete_rectangle(Rectangle r[], int *count) {
    int id;

    printf("Enter rectangle ID to delete: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input!\n");
        return;
    }

    int index = find_rectangle(r, *count, id);

    if (index == -1) {
        printf("Rectangle not found!\n");
        return;
    }

    for (int i = index; i < *count - 1; i++) {
        r[i] = r[i + 1];
    }

    (*count)--;

    printf("Rectangle deleted successfully!\n");
}


// Display area summary
void display_summary(Rectangle r[], int count) {
    if (count == 0) {
        printf("No rectangles available for analysis!\n");
        return;
    }

    int largest = 0, smallest = 0;
    double total = 0;

    for (int i = 0; i < count; i++) {
        total += r[i].area;

        if (r[i].area > r[largest].area)
            largest = i;

        if (r[i].area < r[smallest].area)
            smallest = i;
    }

    printf("Largest Area: ID %d (%.2f)\n",
           r[largest].id, r[largest].area);

    printf("Smallest Area: ID %d (%.2f)\n",
           r[smallest].id, r[smallest].area);

    printf("Total Area: %.2f\n", total);
    printf("Average Area: %.2f\n", total / count);
}


// Classify square and non-square rectangles
// Tolerance: 0.0001 times the larger dimension
void classify_rectangles(Rectangle r[], int count) {
    if (count == 0) {
        printf("No rectangles available!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        float difference = fabsf(r[i].width - r[i].height);
        float tolerance = 0.0001f *
            fmaxf(r[i].width, r[i].height);

        if (difference <= tolerance) {
            printf("ID %d: Square\n", r[i].id);
        } else {
            printf("ID %d: Non-square\n", r[i].id);
        }
    }
}


// Sort rectangles by ascending area
// Equal areas are sorted by ascending ID
void sort_rectangles(Rectangle r[], int count) {
    if (count == 0) {
        printf("No rectangles available!\n");
        return;
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (r[j].area > r[j + 1].area ||
               (r[j].area == r[j + 1].area &&
                r[j].id > r[j + 1].id)) {

                Rectangle temp = r[j];
                r[j] = r[j + 1];
                r[j + 1] = temp;
            }
        }
    }

    printf("Rectangles sorted successfully!\n");
    display_rectangles(r, count);
}


// Filter rectangles by area
void filter_rectangles(Rectangle r[], int count) {
    float threshold;
    int found = 0;

    printf("Enter area threshold: ");

    if (scanf("%f", &threshold) != 1 ||
        !isfinite(threshold) || threshold < 0) {
        printf("Invalid threshold!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        if (r[i].area > threshold) {
            printf("\nID: %d\n", r[i].id);
            printf("Area: %.2f\n", r[i].area);
            found = 1;
        }
    }

    if (!found) {
        printf("No rectangles found above this area.\n");
    }
}
