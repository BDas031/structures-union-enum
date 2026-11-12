
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int roll;
    char name[50];
    int age;
    float gpa;
} Student;

// Function declarations
Student* create_student_list(int capacity);
void add_student(Student **students, int *count, int *capacity);
void display_students(Student students[], int count);
void search_student(Student students[], int count);
void update_student(Student students[], int count);
void delete_student(Student students[], int *count);
void display_summary(Student students[], int count);
void sort_students(Student students[], int count);

int main() {
    int capacity, count = 0, choice;

    printf("Enter initial capacity: ");
    scanf("%d", &capacity);

    if (capacity <= 0) {
        printf("Invalid capacity!\n");
        return 1;
    }

    Student *students = create_student_list(capacity);

    if (students == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    while (1) {
        printf("\n===== STUDENT RECORD SYSTEM =====\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. GPA Summary\n");
        printf("7. Sort by GPA\n");
        printf("8. Exit\n");

        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            break;
        }

        switch (choice) {
            case 1:
                add_student(&students, &count, &capacity);
                break;

            case 2:
                display_students(students, count);
                break;

            case 3:
                search_student(students, count);
                break;

            case 4:
                update_student(students, count);
                break;

            case 5:
                delete_student(students, &count);
                break;

            case 6:
                display_summary(students, count);
                break;

            case 7:
                sort_students(students, count);
                break;

            case 8:
                free(students);
                printf("Program ended.\n");
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }

    free(students);
    return 0;
}


// Allocate memory
Student* create_student_list(int capacity) {
    return malloc(capacity * sizeof(Student));
}


// Add student
void add_student(Student **students, int *count, int *capacity) {
    Student s;

    printf("Enter roll number: ");
    scanf("%d", &s.roll);

    for (int i = 0; i < *count; i++) {
        if ((*students)[i].roll == s.roll) {
            printf("Roll number already exists!\n");
            return;
        }
    }

    printf("Enter name: ");
    scanf(" %49[^\n]", s.name);

    printf("Enter age: ");
    scanf("%d", &s.age);

    printf("Enter GPA: ");
    scanf("%f", &s.gpa);

    if (s.roll <= 0 || s.age < 16 || s.age > 100 ||
        s.gpa < 0 || s.gpa > 4) {
        printf("Invalid student details!\n");
        return;
    }

    if (*count == *capacity) {
        if (*capacity > 2147483647 / 2) {
            printf("Maximum capacity reached!\n");
            return;
        }

        int new_capacity = *capacity * 2;

        if ((size_t)new_capacity > (size_t)-1 / sizeof(Student)) {
            printf("Capacity too large!\n");
            return;
        }

        Student *temp = realloc(*students,
                                new_capacity * sizeof(Student));

        if (temp == NULL) {
            printf("Memory allocation failed!\n");
            return;
        }

        *students = temp;
        *capacity = new_capacity;
    }

    (*students)[*count] = s;
    (*count)++;

    printf("Student added successfully!\n");
}


// Display students
void display_students(Student students[], int count) {
    if (count == 0) {
        printf("No student records available.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        printf("\nRoll: %d\n", students[i].roll);
        printf("Name: %s\n", students[i].name);
        printf("Age: %d\n", students[i].age);
        printf("GPA: %.2f\n", students[i].gpa);
    }
}


// Search student
void search_student(Student students[], int count) {
    int roll;

    printf("Enter roll number: ");
    scanf("%d", &roll);

    for (int i = 0; i < count; i++) {
        if (students[i].roll == roll) {
            printf("Name: %s\n", students[i].name);
            printf("Age: %d\n", students[i].age);
            printf("GPA: %.2f\n", students[i].gpa);
            return;
        }
    }

    printf("Student not found!\n");
}


// Update student
void update_student(Student students[], int count) {
    int roll;

    printf("Enter roll number: ");
    scanf("%d", &roll);

    for (int i = 0; i < count; i++) {
        if (students[i].roll == roll) {
            Student s = students[i];

            printf("Enter new roll number: ");
            scanf("%d", &s.roll);

            for (int j = 0; j < count; j++) {
                if (j != i && students[j].roll == s.roll) {
                    printf("Roll number already exists!\n");
                    return;
                }
            }

            printf("Enter new name: ");
            scanf(" %49[^\n]", s.name);

            printf("Enter new age: ");
            scanf("%d", &s.age);

            printf("Enter new GPA: ");
            scanf("%f", &s.gpa);

            if (s.roll <= 0 || s.age < 16 || s.age > 100 ||
                s.gpa < 0 || s.gpa > 4) {
                printf("Invalid details!\n");
                return;
            }

            students[i] = s;
            printf("Student updated successfully!\n");
            return;
        }
    }

    printf("Student not found!\n");
}


// Delete student
void delete_student(Student students[], int *count) {
    int roll;

    printf("Enter roll number: ");
    scanf("%d", &roll);

    for (int i = 0; i < *count; i++) {
        if (students[i].roll == roll) {
            for (int j = i; j < *count - 1; j++) {
                students[j] = students[j + 1];
            }

            (*count)--;
            printf("Student deleted successfully!\n");
            return;
        }
    }

    printf("Student not found!\n");
}


// GPA summary
void display_summary(Student students[], int count) {
    if (count == 0) {
        printf("No records available for analysis.\n");
        return;
    }

    int highest = 0, lowest = 0;
    float total = 0;

    for (int i = 0; i < count; i++) {
        total += students[i].gpa;

        if (students[i].gpa > students[highest].gpa)
            highest = i;

        if (students[i].gpa < students[lowest].gpa)
            lowest = i;
    }

    printf("Highest GPA: %s (%.2f)\n",
           students[highest].name, students[highest].gpa);

    printf("Lowest GPA: %s (%.2f)\n",
           students[lowest].name, students[lowest].gpa);

    printf("Average GPA: %.2f\n", total / count);
}


// Sort by GPA in descending order
// For equal GPA, smaller roll number comes first
void sort_students(Student students[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (students[j].gpa < students[j + 1].gpa ||
               (students[j].gpa == students[j + 1].gpa &&
                students[j].roll > students[j + 1].roll)) {

                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    printf("Students sorted successfully!\n");
    display_students(students, count);
}
