#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Header {
    struct Node *queue_front;
    struct Node *queue_rear;
    int queue_count;
};

void init_queue(struct Header *header) {
    header->queue_front = NULL;
    header->queue_rear = NULL;
    header->queue_count = 0;
}

void ENQUEUE(struct Header *header, int value) {
    struct Node *newpointer;
    newpointer = (struct Node*)malloc(sizeof(struct Node));

    newpointer->data = value;
    newpointer->next = NULL;

    if (header->queue_front == NULL) {
        header->queue_front = newpointer;
        header->queue_rear = newpointer;
    } else {
        header->queue_rear->next = newpointer;
        header->queue_rear = newpointer;
    }

    header->queue_count++;

    printf("Enqueued: %d\n", value);
}

int DEQUEUE(struct Header *header) {
    if (header->queue_front == NULL) {
        printf("Queue is empty!\n");
        return -999;
    }

    int value = header->queue_front->data;

    struct Node *temp = header->queue_front;

    header->queue_front = header->queue_front->next;

    if (header->queue_front == NULL) {
        header->queue_rear = NULL;
    }

    free(temp);

    header->queue_count--;

    return value;
}

void display_queue(struct Header *header) {
    struct Node *current = header->queue_front;

    if (current == NULL) {
        printf("Queue is empty!\n");
        return;
    }

    printf("Queue contents: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    struct Header header;
    int input;

    init_queue(&header);

    printf("Enter positive integers to enqueue (negative to stop):\n");

    while (1) {
        scanf("%d", &input);

        if (input < 0) {
            break;
        }

        ENQUEUE(&header, input);
    }

    printf("\nDequeuing all elements...\n");

    while (header.queue_count > 0) {
        int value = DEQUEUE(&header);
        if (value != -999) {
            printf("Dequeued: %d\n", value);
        }
    }

    return 0;
}