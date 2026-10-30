
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 50
#define SIZE 200

char backStack[MAX][SIZE];
char forwardStack[MAX][SIZE];

int backTop = -1;
int forwardTop = -1;

char currentPage[SIZE] = "Home";

void push(char stack[MAX][SIZE], int *top, const char page[]) {
    if (*top < MAX - 1) {
        strcpy(stack[++(*top)], page);
    }
}

int pop(char stack[MAX][SIZE], int *top, char page[]) {
    if (*top == -1) {
        return 0;
    }

    strcpy(page, stack[(*top)--]);
    return 1;
}

void visitPage(void) {
    char page[SIZE];

    printf("Enter webpage URL or name: ");
    if (fgets(page, sizeof(page), stdin) == NULL) {
        return;
    }

    page[strcspn(page, "\n")] = '\0';

    if (page[0] == '\0') {
        printf("Page name cannot be empty.\n");
        return;
    }

    if (backTop < MAX - 1) {
        push(backStack, &backTop, currentPage);
        strcpy(currentPage, page);
        forwardTop = -1;
        printf("Page visited successfully!\n");
    } else {
        printf("Back history is full. Cannot visit page.\n");
    }
}

void goBack(void) {
    if (backTop == -1) {
        printf("No previous page available.\n");
        return;
    }

    push(forwardStack, &forwardTop, currentPage);
    pop(backStack, &backTop, currentPage);
    printf("Moved back successfully.\n");
}

void goForward(void) {
    if (forwardTop == -1) {
        printf("No forward page available.\n");
        return;
    }

    push(backStack, &backTop, currentPage);
    pop(forwardStack, &forwardTop, currentPage);
    printf("Moved forward successfully.\n");
}

void displayHistory(void) {
    int i;

    printf("\n--- Back History (oldest to newest) ---\n");
    if (backTop == -1) {
        printf("Empty\n");
    } else {
        for (i = 0; i <= backTop; i++) {
            printf("%s\n", backStack[i]);
        }
    }

    printf("\n--- Current Page ---\n%s\n", currentPage);

    printf("\n--- Forward History (next to farthest) ---\n");
    if (forwardTop == -1) {
        printf("Empty\n");
    } else {
        for (i = forwardTop; i >= 0; i--) {
            printf("%s\n", forwardStack[i]);
        }
    }
}

int main(void) {
    char input[30];
    int choice;

    do {
        printf("\n===== BROWSER NAVIGATION SYSTEM =====\n");
        printf("1. Visit a new page\n");
        printf("2. Go Back\n");
        printf("3. Go Forward\n");
        printf("4. Display History\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");

        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }

        choice = atoi(input);

        switch (choice) {
            case 1:
                visitPage();
                break;
            case 2:
                goBack();
                break;
            case 3:
                goForward();
                break;
            case 4:
                displayHistory();
                break;
            case 5:
                printf("Exiting Browser Navigation System.\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}
