#include <stdio.h>
#include <string.h>

struct Book {
    int ID;
    int pScore;
    int lastAccess;  // Add this to track access order
};

int addXY(struct Book b[], int *size, int capacity, int x, int y, int *timeCounter);
int accessX(struct Book b[], int size, int x, int *timeCounter);

int main() {
    int capacity, Q;
    scanf("%d %d", &capacity, &Q);

    struct Book shelf[capacity];
    int size=0;
    int timeCounter=0;  // To track access order

    for (int i=0; i<Q; i++) {
        char ot[10];
        int x, y;
        scanf("%s", ot);

        if (strcmp(ot, "ADD") == 0) {
            scanf("%d %d", &x, &y);
            addXY(shelf, &size, capacity, x, y, &timeCounter);
        } else if (strcmp(ot, "ACCESS") == 0) {
            scanf("%d", &x);
            int result = accessX(shelf, size, x, &timeCounter);
            printf("%d\n", result);
        }
    }
    return 0;
}


int addXY(struct Book b[], int *size, int capacity, int x, int y, int *timeCounter) {
    for (int i = 0; i < *size; i++) {
        if(b[i].ID == x){
            b[i].pScore = y;
            b[i].lastAccess = (*timeCounter)++;
            return 1;
        }
    }

    if(*size == capacity){
        int lruIndex=0;
        for(int i = 1; i < *size; i++){
            if(b[i].lastAccess < b[lruIndex].lastAccess){
                lruIndex = i;
            }
        }
        b[lruIndex].ID = x;
        b[lruIndex].pScore = y;
        b[lruIndex].lastAccess = (*timeCounter)++;
        return 1;
    }

    b[*size].ID = x;
    b[*size].pScore = y;
    b[*size].lastAccess = (*timeCounter)++;
    (*size)++;
    return 1;
}

int accessX(struct Book b[], int size, int x, int *timeCounter){
    for(int i = 0; i < size; i++){
        if(b[i].ID == x){
            b[i].lastAccess = (*timeCounter)++;
            return b[i].pScore;
        }
    }
    return -1;
}
