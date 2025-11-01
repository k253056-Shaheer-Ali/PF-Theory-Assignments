#include <stdio.h>

void push(int stack[], int *top, int maxSize);
void pop(int stack[], int *top);
void peek(int stack[], int top);
void display(int stack[], int top);


int main() {
    int stack[5];
    int top = -1;
    int choice;

    do {
        printf("\n===== STACK MENU =====\n");
        printf("1. PUSH\n");
        printf("2. POP\n");
        printf("3. PEEK\n");
        printf("4. DISPLAY\n");
        printf("5. EXIT\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                push(stack, &top, 5);
                break;
            case 2:
                pop(stack, &top);
                break;
            case 3:
                peek(stack, top);
                break;
            case 4:
                display(stack, top);
                break;
            case 5:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while(choice != 5);
    return 0;
}


void push(int stack[], int *top, int maxSize) {
    if (*top == maxSize - 1) {
        printf("\nStack Overflow! Cannot push more elements.\n");
    } 
	else{
        int value;
        printf("\nEnter value to push: ");
        scanf("%d", &value);
        (*top)++;
        stack[*top] = value;
        printf("%d pushed to stack.\n", value);
    }
}


void pop(int stack[], int *top) {
    if (*top == -1){
        printf("\nStack Underflow! No elements to pop.\n");
    } 
	else{
        printf("\nPopped element: %d\n", stack[*top]);
        (*top)--;
    }
}


void peek(int stack[], int top) {
    if (top == -1){
        printf("\nStack is empty.\n");
    } 
	else{
        printf("\nTop element: %d\n", stack[top]);
    }
}


void display(int stack[], int top) {
    if (top == -1){
        printf("\nStack is empty.\n");
    } 
	else{
        printf("\nStack elements (top to bottom):\n");
        for (int i = top; i >= 0; i--) {
            printf("%d\n", stack[i]);
        }
    }
}

