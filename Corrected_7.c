
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_DESCRIPTION 100

// Enum for commands
typedef enum {
    CMD_ADD,
    CMD_DELETE,
    CMD_VIEW,
    CMD_UPDATE,
    CMD_COMPLETE,
    CMD_FIND,
    CMD_HELP,
    CMD_EXIT,
    CMD_UNKNOWN
} CommandType;

// Enum for task status
typedef enum {
    PENDING,
    DONE
} TaskStatus;

// Structure for tasks
typedef struct {
    int id;
    char description[MAX_DESCRIPTION];
    TaskStatus status;
} Task;


// Function declarations
CommandType get_command_type(char command[]);
void add_task(Task **tasks, int *count, int *capacity);
void delete_task(Task tasks[], int *count);
void view_tasks(Task tasks[], int count);
void update_task(Task tasks[], int count);
void complete_task(Task tasks[], int count);
void find_task(Task tasks[], int count);
void show_help();
int find_index(Task tasks[], int count, int id);


// Convert command to uppercase and identify it
CommandType get_command_type(char command[]) {
    for (int i = 0; command[i] != '\0'; i++) {
        command[i] = toupper((unsigned char)command[i]);
    }

    if (strcmp(command, "ADD") == 0) return CMD_ADD;
    if (strcmp(command, "DELETE") == 0) return CMD_DELETE;
    if (strcmp(command, "VIEW") == 0) return CMD_VIEW;
    if (strcmp(command, "UPDATE") == 0) return CMD_UPDATE;
    if (strcmp(command, "COMPLETE") == 0) return CMD_COMPLETE;
    if (strcmp(command, "FIND") == 0) return CMD_FIND;
    if (strcmp(command, "HELP") == 0) return CMD_HELP;
    if (strcmp(command, "EXIT") == 0) return CMD_EXIT;

    return CMD_UNKNOWN;
}


// Find task using ID
int find_index(Task tasks[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (tasks[i].id == id) {
            return i;
        }
    }

    return -1;
}


// Add a task
void add_task(Task **tasks, int *count, int *capacity) {
    Task temp;
    char line[200];

    printf("Enter task ID: ");

    if (fgets(line, sizeof(line), stdin) == NULL) return;

    char extra;
    if (sscanf(line, "%d %c", &temp.id, &extra) != 1 ||
        temp.id <= 0) {
        printf("Invalid task ID!\n");
        return;
    }

    if (find_index(*tasks, *count, temp.id) != -1) {
        printf("Task ID already exists!\n");
        return;
    }

    printf("Enter task description: ");

    if (fgets(temp.description, sizeof(temp.description), stdin) == NULL)
        return;

    if (strchr(temp.description, '\n') == NULL) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);
        printf("Description is too long!\n");
        return;
    }

    temp.description[strcspn(temp.description, "\n")] = '\0';

    if (strlen(temp.description) == 0) {
        printf("Description cannot be empty!\n");
        return;
    }

    temp.status = PENDING;

    // Increase capacity when full
    if (*count == *capacity) {
        if (*capacity > 1000000 / 2) {
            printf("Maximum capacity reached!\n");
            return;
        }

        int new_capacity = *capacity * 2;

        Task *new_tasks = realloc(
            *tasks, new_capacity * sizeof(Task));

        if (new_tasks == NULL) {
            printf("Memory allocation failed!\n");
            return;
        }

        *tasks = new_tasks;
        *capacity = new_capacity;
    }

    (*tasks)[*count] = temp;
    (*count)++;

    printf("Task %d added successfully!\n", temp.id);
}


// Display all tasks
void view_tasks(Task tasks[], int count) {
    if (count == 0) {
        printf("No tasks available!\n");
        return;
    }

    printf("\n--- Task List ---\n");

    for (int i = 0; i < count; i++) {
        printf("\nID: %d\n", tasks[i].id);
        printf("Description: %s\n", tasks[i].description);

        if (tasks[i].status == PENDING)
            printf("Status: PENDING\n");
        else
            printf("Status: DONE\n");
    }
}


// Search task
void find_task(Task tasks[], int count) {
    int id;

    printf("Enter task ID: ");

    if (scanf("%d", &id) != 1) {
        printf("Invalid ID!\n");
        while (getchar() != '\n');
        return;
    }

    while (getchar() != '\n');

    int index = find_index(tasks, count, id);

    if (index == -1) {
        printf("Task not found!\n");
        return;
    }

    printf("ID: %d\n", tasks[index].id);
    printf("Description: %s\n", tasks[index].description);
    printf("Status: %s\n",
           tasks[index].status == DONE ? "DONE" : "PENDING");
}


// Update task description
void update_task(Task tasks[], int count) {
    int id;
    char description[MAX_DESCRIPTION];

    printf("Enter task ID: ");

    if (scanf("%d", &id) != 1) {
        printf("Invalid ID!\n");
        while (getchar() != '\n');
        return;
    }

    while (getchar() != '\n');

    int index = find_index(tasks, count, id);

    if (index == -1) {
        printf("Task not found!\n");
        return;
    }

    printf("Enter new description: ");

    if (fgets(description, sizeof(description), stdin) == NULL)
        return;

    if (strchr(description, '\n') == NULL) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);
        printf("Description is too long!\n");
        return;
    }

    description[strcspn(description, "\n")] = '\0';

    if (strlen(description) == 0) {
        printf("Description cannot be empty!\n");
        return;
    }

    strcpy(tasks[index].description, description);

    printf("Task %d updated successfully!\n", id);
}


// Complete task
void complete_task(Task tasks[], int count) {
    int id;

    printf("Enter task ID: ");

    if (scanf("%d", &id) != 1) {
        printf("Invalid ID!\n");
        while (getchar() != '\n');
        return;
    }

    while (getchar() != '\n');

    int index = find_index(tasks, count, id);

    if (index == -1) {
        printf("Task not found!\n");
        return;
    }

    tasks[index].status = DONE;

    printf("Task %d marked as DONE!\n", id);
}


// Delete task
void delete_task(Task tasks[], int *count) {
    int id;

    printf("Enter task ID: ");

    if (scanf("%d", &id) != 1) {
        printf("Invalid ID!\n");
        while (getchar() != '\n');
        return;
    }

    while (getchar() != '\n');

    int index = find_index(tasks, *count, id);

    if (index == -1) {
        printf("Task not found!\n");
        return;
    }

    for (int i = index; i < *count - 1; i++) {
        tasks[i] = tasks[i + 1];
    }

    (*count)--;

    printf("Task %d deleted successfully!\n", id);
}


// Display help
void show_help() {
    printf("\n--- Available Commands ---\n");
    printf("ADD      - Add a new task\n");
    printf("DELETE   - Delete a task\n");
    printf("VIEW     - Display all tasks\n");
    printf("UPDATE   - Update task description\n");
    printf("COMPLETE - Mark a task as done\n");
    printf("FIND     - Search for a task\n");
    printf("HELP     - Display commands\n");
    printf("EXIT     - Exit the program\n");
}


// Main function
int main() {
    int count = 0;
    int capacity = 2;

    char command[100];

    Task *tasks = malloc(capacity * sizeof(Task));

    if (tasks == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    while (1) {
        printf("\nEnter command (ADD, DELETE, VIEW, UPDATE, COMPLETE, FIND, HELP, EXIT): ");

        if (fgets(command, sizeof(command), stdin) == NULL) {
            printf("\nInput ended!\n");
            break;
        }

        if (strchr(command, '\n') == NULL) {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF);
            printf("Command is too long!\n");
            continue;
        }

        command[strcspn(command, "\n")] = '\0';

        CommandType cmd = get_command_type(command);

        switch (cmd) {
            case CMD_ADD:
                add_task(&tasks, &count, &capacity);
                break;

            case CMD_DELETE:
                delete_task(tasks, &count);
                break;

            case CMD_VIEW:
                view_tasks(tasks, count);
                break;

            case CMD_UPDATE:
                update_task(tasks, count);
                break;

            case CMD_COMPLETE:
                complete_task(tasks, count);
                break;

            case CMD_FIND:
                find_task(tasks, count);
                break;

            case CMD_HELP:
                show_help();
                break;

            case CMD_EXIT:
                printf("Exiting program...\n");
                free(tasks);
                return 0;

            default:
                printf("Unknown command!\n");
        }
    }

    free(tasks);
    return 0;
}
