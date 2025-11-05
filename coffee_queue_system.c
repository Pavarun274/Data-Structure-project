#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define SIZE 5
char queue[SIZE][30];  // store customer names
int front = -1, rear = -1;

void enqueue(char name[]) {
    // Queue full when next position of rear meets front
    if ((front == 0 && rear == SIZE - 1) || (front != -1 && ((rear + 1) % SIZE) == front)) {
        printf("Queue is full — please wait\n");
    } 
    else {
        if (front == -1) {
            // first element
            front = rear = 0;
        } 
        else {
            rear = (rear + 1) % SIZE;
        }
        strncpy(queue[rear], name, sizeof(queue[rear]) - 1);
        queue[rear][sizeof(queue[rear]) - 1] = '\0';
        printf("%s has been added to the queue\n", name);
    }
}

void dequeue() {
    if (front == -1) {
        printf("The queue is empty — no customers waiting\n");
    } 
    else {
        printf("Now serving: %s — please collect your coffee!\n", queue[front]);
        if (front == rear) {
            // the queue becomes empty after removing the last element
            front = rear = -1;
        } 
        else {
            front = (front + 1) % SIZE;
        }
    }
}

void show() {
    if (front == -1) {
        printf("No customers in the queue\n");
    } 
    else {
        printf("Current customers in queue:\n");
        int i = front;
        while (1) {
            printf(" %s\n", queue[i]);
            if (i == rear) {
                break;
            }
            i = (i + 1) % SIZE;
        }
    }
}

int main() {
    int choice;
    char name[30];

    do {
        printf("\n====== COFFEE QUEUE SYSTEM ======\n");
        printf("1. Enqueue customer\n");
        printf("2. Dequeue (call customer)\n");
        printf("3. Show queue\n");
        printf("4. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        getchar(); // clear buffer
        sleep(1);
        system("clear"); // clear screen each loop

        switch (choice) {
            case 1:
                printf("Enter customer name: ");
                if (fgets(name, sizeof(name), stdin)) {
                    name[strcspn(name, "\n")] = '\0'; // remove newline
                }
                enqueue(name);
                sleep(1); // pause for a seconds
                break;
            case 2:
                dequeue();
                sleep(1);
                break;
            case 3:
                show();
                sleep(1);
                break;
            case 4:
                printf("Thank you for using the service!\n");
                break;
            default:
                printf("Please choose a valid option\n");
                sleep(1);
                break;
        }
    } while (choice != 4);

    return 0;
}