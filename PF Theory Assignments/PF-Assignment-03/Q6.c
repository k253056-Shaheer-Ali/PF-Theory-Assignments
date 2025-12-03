#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[100];
    char batch[20];        // CS, SE, Cyber Security, AI
    char membership[10];   // IEEE / ACM
    char regDate[11];      // YYYY-MM-DD
    char dob[11];          // YYYY-MM-DD
    char interest[10];     // IEEE / ACM / Both
} Student;

Student* studentList = NULL;
int studentCount = 0;


void loadDatabase(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        printf("No database found. Starting new.\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    studentCount = size / sizeof(Student);
    if (studentCount > 0) {
        studentList = (Student*)malloc(studentCount * sizeof(Student));
        fread(studentList, sizeof(Student), studentCount, file);
    }

    fclose(file);
}


void saveDatabase(const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        printf("Error: cannot write to file!\n");
        return;
    }

    if (studentCount > 0)
        fwrite(studentList, sizeof(Student), studentCount, file);

    fclose(file);
}


int isUniqueID(int id) {
    for (int i = 0; i < studentCount; i++) {
        if (studentList[i].id == id) return 0;
    }
    return 1;
}


void addStudent(const char* filename) {
    Student s;
    printf("Enter Student ID: ");
    scanf("%d", &s.id);

    if (!isUniqueID(s.id)) {
        printf("Error: ID already exists!\n");
        return;
    }
    
    printf("Enter Full Name: ");
    getchar();
    fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name, "\n")] = 0;
    printf("Enter Batch (CS/SE/Cyber Security/AI): ");
    scanf("%s", s.batch);
    printf("Enter Membership (IEEE/ACM): ");
    scanf("%s", s.membership);
    printf("Enter Registration Date (YYYY-MM-DD): ");
    scanf("%s", s.regDate);
    printf("Enter Date of Birth (YYYY-MM-DD): ");
    scanf("%s", s.dob);
    printf("Enter Interest (IEEE/ACM/Both): ");
    scanf("%s", s.interest);

    studentList = (Student*)realloc(studentList, (studentCount + 1) * sizeof(Student));
    studentList[studentCount] = s;
    studentCount++;

    saveDatabase(filename);
    printf("Student added successfully!\n");
}


void updateStudent(const char* filename) {
    int id;
    printf("Enter Student ID to update: ");
    scanf("%d", &id);

    for (int i=0; i<studentCount; i++) {
        if (studentList[i].id == id) {
            printf("Update Batch: ");
            scanf("%s", studentList[i].batch);
            printf("Update Membership (IEEE/ACM): ");
            scanf("%s", studentList[i].membership);

            saveDatabase(filename);
            printf("Student updated!\n");
            return;
        }
    }
    printf("Student ID not found.\n");
}


void deleteStudent(const char* filename) {
    int id;
    printf("Enter Student ID to delete: ");
    scanf("%d", &id);

    for (int i=0; i<studentCount; i++) {
        if (studentList[i].id == id) {
            for (int j=i; j<studentCount-1; j++)
                studentList[j] = studentList[j + 1];

            studentCount--;
            studentList = (Student*)realloc(studentList, studentCount * sizeof(Student));

            saveDatabase(filename);
            printf("Student deleted successfully!\n");
            return;
        }
    }

    printf("Student ID not found.\n");
}


void viewAllStudents() {
    if (studentCount == 0) {
        printf("No students registered.\n");
        return;
    }

    for (int i=0; i<studentCount; i++) {
        Student s = studentList[i];
        printf("ID: %d | Name: %s | Batch: %s | Membership: %s | RegDate: %s | DOB: %s | Interest: %s\n", s.id, s.name, s.batch, s.membership, s.regDate, s.dob, s.interest);
    }
}


void generateReport() {
    char batch[20], interest[10];
    printf("Enter Batch (CS/SE/Cyber Security/AI): ");
    scanf("%s", batch);
    printf("Enter Interest filter (IEEE/ACM/Both/All): ");
    scanf("%s", interest);

    int found = 0;
    for (int i=0; i<studentCount; i++) {
        if (strcmp(studentList[i].batch, batch) == 0 &&
            (strcmp(interest, "All") == 0 || strcmp(studentList[i].interest, interest) == 0)) {
            Student s = studentList[i];
            printf("ID: %d | Name: %s | Batch: %s | Membership: %s | RegDate: %s | DOB: %s | Interest: %s\n", s.id, s.name, s.batch, s.membership, s.regDate, s.dob, s.interest);
            found = 1;
        }
    }
    if (!found) printf("No students found for this filter.\n");
}


void menu(const char* filename) {
    int choice;

    while(1) {
        printf("\n--- Membership Registration Menu ---\n");
        printf("1. Register new student\n");
        printf("2. Update student record\n");
        printf("3. Delete student record\n");
        printf("4. View all students\n");
        printf("5. Generate batch-wise report\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(filename); break;
            case 2: updateStudent(filename); break;
            case 3: deleteStudent(filename); break;
            case 4: viewAllStudents(); break;
            case 5: generateReport(); break;
            case 6:
                printf("Exiting...\n");
                saveDatabase(filename);
                free(studentList);
                exit(0);
            default: printf("Invalid choice.\n");
        }
    }
}

int main() {
    const char* filename = "members.dat";
    loadDatabase(filename);
    menu(filename);
    return 0;
}

