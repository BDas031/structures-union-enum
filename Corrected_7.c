
#include <stdio.h>
#include <string.h>

// Enum for command types
typedef enum {
    CMD_ADD,
    CMD_DELETE,
    CMD_VIEW,
    CMD_EXIT,
    CMD_UNKNOWN
} CommandType;

// Function to convert string to CommandType
CommandType get_command_type(const char *commandStr) {
    if (commandStr == NULL) return CMD_UNKNOWN;

    if (strcmp(commandStr, "ADD") == 0) return CMD_ADD;
    if (strcmp(commandStr, "DELETE") == 0) return CMD_DELETE;
    if (strcmp(commandStr, "VIEW") == 0) return CMD_VIEW;
    if (strcmp(commandStr, "EXIT") == 0) return CMD_EXIT;

    return CMD_UNKNOWN;
}

// Main program
int main() {
    char input[100];
    CommandType cmd;

    while (1) {
        printf("Enter command (ADD, DELETE, VIEW, EXIT): ");

        if (scanf("%99s", input) != 1) {
            printf("Input error.\n");
            break;
        }

        cmd = get_command_type(input);

        switch (cmd) {
            case CMD_ADD:
                printf("Add command selected.\n");
                break;

            case CMD_DELETE:
                printf("Delete command selected.\n");
                break;

            case CMD_VIEW:
                printf("View command selected.\n");
                break;

            case CMD_EXIT:
                printf("Exiting program.\n");
                return 0;

            default:
                printf("Unknown command.\n");
        }
    }

    return 0;
}
