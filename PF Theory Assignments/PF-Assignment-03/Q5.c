#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 5
#define MAX_LINE 1000

//global variale
char **lines = NULL;   
int size = 0;         
int capacity = INITIAL_CAPACITY;
//-------------------------------

void growIfNeeded(){
    if (size < capacity) return;  

    capacity *= 2;
    char **temp = realloc(lines, capacity * sizeof(char*));
    if(!temp){
        printf("ERROR: Memory reallocation failed.\n");
        exit(1);
    }
    lines = temp;
}

void insertLine(int index, const char *text){
    if(index<0 || index>size){
        printf("Invalid index.\n");
        return;
    }

    growIfNeeded();
    for (int i=size; i>index; i--){
        lines[i] = lines[i-1];
    }

    lines[index] = malloc(strlen(text) + 1);
    if(!lines[index]){
        printf("ERROR: Memory allocation failed.\n");
        exit(1);
    }
    strcpy(lines[index], text);
    size++;
}

void deleteLine(int index){
    if(index<0 || index>=size){
        printf("Invalid index.\n");
        return;
    }
    free(lines[index]);
    
    for(int i=index; i<size - 1; i++){
        lines[i] = lines[i + 1];
    }
    size--;
}

void printAllLines(){
    if(size == 0){
        printf("No lines stored.\n");
        return;
    }
    for(int i = 0; i < size; i++){
        printf("%d: %s\n", i, lines[i]);
    }
}

void shrinkToFit() {
    capacity = size;
    char **temp = realloc(lines, capacity * sizeof(char*));
    
    if(!temp && size > 0){
        printf("Shrink failed.\n");
        return;
    }
    lines = temp;
    printf("Memory shrunk to fit exactly %d lines.\n", size);
}

void saveToFile(const char *filename){
    FILE *fp = fopen(filename, "w");
    if(!fp){
        printf("File open failed.\n");
        return;
    }
    for(int i = 0; i < size; i++){
        fprintf(fp, "%s\n", lines[i]);
    }
    fclose(fp);
    printf("Saved to %s\n", filename);
}

void loadFromFile(const char *filename){
    FILE *fp = fopen(filename, "r");
    if(!fp){
        printf("File open failed.\n");
        return;
    }
    for(int i=0; i<size; i++){
        free(lines[i]);
    }

    size = 0;
    capacity = INITIAL_CAPACITY;
    lines = realloc(lines, capacity * sizeof(char*));
    char buffer[MAX_LINE];

    while(fgets(buffer, MAX_LINE, fp)){
        buffer[strcspn(buffer, "\n")] = '\0';  
        insertLine(size, buffer);  
    }
    fclose(fp);
    printf("Loaded from %s\n", filename);
}

void freeAll(){
    for(int i=0; i<size; i++){
        free(lines[i]);
    }
    free(lines);
}

// ===========================================================
int main() {
    lines = malloc(capacity * sizeof(char*));
    if(!lines){
        printf("Initial memory allocation failed.\n");
        return 1;
    }

    int choice, index;
    char input[MAX_LINE];

    while(1){
        printf("\n===== SIMPLE TEXT EDITOR =====\n");
        printf("1. Insert Line\n");
        printf("2. Delete Line\n");
        printf("3. Print All Lines\n");
        printf("4. Shrink To Fit\n");
        printf("5. Save To File\n");
        printf("6. Load From File\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();

        if(choice == 1){
            printf("Enter index (0 to %d): ", size);
            scanf("%d", &index);
            getchar();

            printf("Enter line text: ");
            fgets(input, MAX_LINE, stdin);
            input[strcspn(input, "\n")] = '\0';

            insertLine(index, input);
        }
        else if(choice == 2){
            printf("Enter index to delete: ");
            scanf("%d", &index);
            deleteLine(index);
        }
        else if(choice == 3){
            printAllLines();
        }
        else if(choice == 4){
            shrinkToFit();
        }
        else if(choice == 5){
            saveToFile("output.txt");
        }
        else if(choice == 6){
            loadFromFile("output.txt");
        }
        else if(choice == 7){
            freeAll();
            break;
        }
        else{
            printf("Invalid choice.\n");
        }
    }
    return 0;
}

