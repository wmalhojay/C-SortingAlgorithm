#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

typedef struct {
    int number;
} Info;

typedef struct node_def {
    Info data;
    struct node_def* next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    int nodeCount;
} Queue;

int dequeue(Queue*);
void initiate(Queue*);
void enqueue(Queue*, int);

void generateArray(int[], int);
int findBiggest(int[], int);
int getNumberOfRuns(int);
void radixSort(Queue[], int[], int, int);
void display(int[], int);

int dequeue(Queue* que) {
    if (que->nodeCount > 0) {
        Node* tmp = que->head;
        que->head = que->head->next;
        int num = tmp->data.number;
        free(tmp);
        que->nodeCount--;
        return num;
    }
    else {
        return -1;
    }
}

void initiate(Queue* que) {
    que->head = que->tail = NULL;
    que->nodeCount = 0;
}

void enqueue(Queue* que, int number) {
    Node* newNode = malloc(sizeof(Node));
    assert(newNode);
    newNode->data.number = number;
    newNode->next = NULL;
    if (que->nodeCount > 0) {
        que->tail->next = newNode;
        que->tail = newNode;
    }
    else {
        que->head = que->tail = newNode;
    }
    que->nodeCount++;
}

void generateArray(int array[], int size) {
    for (int i = 0; i < size; i++) {
        array[i] = rand() % size;
    }
}

int findBiggest(int array[], int size) {
    int max = array[0];
    for (int i = 1; i < size; ++i) {
        if (array[i] > max) {
            max = array[i];
        }
    }
    return max;
}

int getNumberOfRuns(int max) {
    int times = 0;
    int divisor = 10;

    while (max / divisor != 0) {
        times++;
        divisor *= 10;
    }
    return times + 1;
}


void display(int array[], int size) {
    printf("Sorted array is --> [ ");
    for (int i = 0; i < size; i++) {
        printf("%d, ", array[i]);
    }
    printf("]");
}

void radixSort(Queue binQueue[], int array[], int size, int n) {
    int divisor = 1;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < size; ++j) {
            int index = (array[j] / divisor) % 10;
            enqueue(&binQueue[index], array[j]);
        }

        int k = 0;
        for (int j = 0; j < 10; ++j) {
            while (binQueue[j].nodeCount > 0) {
                array[k] = dequeue(&binQueue[j]);
                ++k;
            }
        }
        divisor *= 10;
    }
}

int main(int argc, char** argv) {

    int size = 1000000;
    int array[size];
    generateArray(array, size);

    int max = findBiggest(array, size);
    int n = getNumberOfRuns(max);

    Queue binQueue[10];
    for (int i = 0; i < 10; ++i) {
        initiate(&binQueue[i]);
    }

    radixSort(binQueue, array, size, n);
    display(array, size);

    return 0;
}
