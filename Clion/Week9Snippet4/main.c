#include <stdio.h>
#include <stdlib.h>

// Function to push an integer onto the stack
void push(int *stack, int *stacktop, int maxstack, int value) {
    // Check if stack is full
    if (*stacktop == maxstack - 1) {
        printf("Stack overflow! Cannot push %d.\n", value);
        return;
    }

    // Increment stacktop and add value to stack
    (*stacktop)++;
    stack[*stacktop] = value;
    printf("Pushed %d onto the stack.\n", value);
}

// Function to pop an integer from the stack
int pop(int *stack, int *stacktop) {
    // Check if stack is empty
    if (*stacktop == -1) {
        printf("Stack underflow! Cannot pop from empty stack.\n");
        return -1; // Return -1 to indicate error (stack is empty)
    }

    // Get value at the top of stack and decrement stacktop
    int value = stack[*stacktop];
    (*stacktop)--;
    printf("Popped %d from the stack.\n", value);
    return value;
}

int main() {
    int maxstack = 100; // Maximum size of the stack
    int stack[maxstack]; // Array to be used as stack
    int stacktop = -1; // Initialize stacktop to -1 (empty stack)
    int input;

    printf("Enter integers between 1 and 1000 (negative number to stop):\n");

    // Loop to push values onto the stack
    while (1) {
        scanf("%d", &input);

        // Check if input is negative
        if (input < 0) {
            printf("Negative number encountered. Popping all items...\n");
            break;
        }

        // Check if input is within valid range
        if (input >= 1 && input <= 1000) {
            push(stack, &stacktop, maxstack, input);
        } else {
            printf("Invalid input! Please enter a number between 1 and 1000.\n");
        }
    }

    // Pop all items from the stack
    printf("\nPopping all items from the stack:\n");
    while (stacktop != -1) {
        pop(stack, &stacktop);
    }

    printf("\n--- Now implementing stack with characters ---\n");

    // Implement stack with characters
    char charStack[maxstack];
    stacktop = -1; // Reset stacktop for the character stack
    char name[50];

    printf("\nEnter your name: ");
    scanf("%s", name);

    // Push each character of the name
    for (int i = 0; name[i] != '\0'; i++) {
        if (stacktop < maxstack - 1) {
            stacktop++;
            charStack[stacktop] = name[i];
            printf("Pushed '%c' onto the stack.\n", name[i]);
        } else {
            printf("Stack overflow! Cannot push more characters.\n");
            break;
        }
    }

    // Pop and print each character
    printf("\nPopping characters (name in reverse):\n");
    while (stacktop != -1) {
        char ch = charStack[stacktop];
        stacktop--;
        printf("%c", ch);
    }
    printf("\n");

    return 0;
}