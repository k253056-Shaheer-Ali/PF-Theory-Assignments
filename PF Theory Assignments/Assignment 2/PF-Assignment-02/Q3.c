#include <stdio.h>

void displayMenu();
void updateSectorStatus(int grid[3][3]);
void querySectorStatus(int grid[3][3]);
void runSystemDiagnostic(int grid[3][3]);

int POWER_ON = 1;       // Bit 0 --> 0001
int OVERLOADED = 2;     // Bit 1 --> 0010
int MAINTENANCE = 4;    // Bit 2 --> 0100

int main() {
    int grid[3][3] = {0};  //assuming 3x3 grid
    int choice;

    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                updateSectorStatus(grid);
                break;
            case 2:
                querySectorStatus(grid);
                break;
            case 3:
                runSystemDiagnostic(grid);
                break;
            case 4:
                printf("Exiting system...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 4);
    return 0;
}


void displayMenu() {
    printf("\n===== IESCO Grid Menu =====\n");
    printf("1. Update Sector Status\n");
    printf("2. Query Sector Status\n");
    printf("3. Run System Diagnostic\n");
    printf("4. Exit\n");
}


void updateSectorStatus(int grid[3][3]) {
    int row, col, flag, action;
    printf("\nEnter sector coordinates (row col): ");
    scanf("%d %d", &row, &col);

    if (row>=3 || col>=3 || row<0 || col<0){
        printf("Invalid coordinates!\n");
        return;
    }

    printf("Select status flag to modify:\n");
    printf("1. Power ON/OFF\n");
	printf("2. Overload Warning\n");
	printf("3. Maintenance Required\n");
    scanf("%d", &flag);
    
    printf("Enter action (1=Set, 0=Clear): ");
    scanf("%d", &action);
    int mask = 1 << (flag-1);
    
    if (action == 1){
    	grid[row][col] |= mask;     //Set bit
	}
    else{
    	grid[row][col] &= ~mask;    //Clear bit
	}
    printf("Sector status updated.\n");
}


void querySectorStatus(int grid[3][3]) {
    int row, col;
    printf("\n--- Query Sector Status ---");
    printf("\nEnter sector coordinates (row col): ");
    scanf("%d %d", &row, &col);

    if (row >=3 || col >= 3 || row < 0 || col < 0) {
        printf("Invalid coordinates!\n");
        return;
    }

    int status = grid[row][col];
    if(status & POWER_ON){
    	printf("Power: ON\n");
	}
    else{
    	printf("Power: OFF\n");
    }
    if(status & OVERLOADED){
    	printf("Overload: WARNING\n");
	}
    else{
    	printf("Overload: Normal\n");
	}
    if(status & MAINTENANCE){
    	printf("Maintenance: Required\n");
	}
    else{
    	printf("Maintenance: Not Required\n");
	}
}


void runSystemDiagnostic(int grid[3][3]) {
    int overloadCount=0, maintenanceCount=0;

    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            if (grid[i][j] & OVERLOADED)
                overloadCount++;
            if (grid[i][j] & MAINTENANCE)
                maintenanceCount++;
        }
    }

    printf("\n--- System Diagnostic Report ---\n");
    printf("Sectors Overloaded: %d\n", overloadCount);
    printf("Sectors Needing Maintenance: %d\n", maintenanceCount);
}





