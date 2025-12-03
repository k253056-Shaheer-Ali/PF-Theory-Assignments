#include<stdio.h>
#include<string.h>

struct employee{
	int ID;
	char name[50];
    char designation[50];
	float salary;
	
};

void displayEmployees(struct employee emp[], int n);
void findHighestSalary(struct employee emp[], int n);
void searchEmployee(struct employee emp[], int n);
void salaryBonus(struct employee emp[], int n);

int main(){
	int n;
	printf("Enter no. of employees: ");
	scanf("%d", &n);
	
	struct employee emp[n];
	
	for(int i=0; i<n; i++){
		printf("\n==== EMPLOYEE %d ====\n", i+1);
		printf("---------------------\n");
		printf("Enter ID: \n");
		scanf("%d", &emp[i].ID);
		printf("Enter name: \n");
		scanf("%s", emp[i].name);
		printf("Enter designation: \n");
		scanf("%s", emp[i].designation);
		printf("Enter salary: \n");
		scanf("%f", &emp[i].salary);
	}
	
	displayEmployees(emp, n);
    findHighestSalary(emp, n);
    searchEmployee(emp, n);
    salaryBonus(emp, n);
	return 0;
}


void displayEmployees(struct employee emp[], int n){
	for(int i=0; i<n; i++){
		printf("\n==== EMPLOYEE %d ====\n", i+1);
		printf("---------------------\n");
		printf("ID: %d\n", emp[i].ID);
		printf("Name: %s\n", emp[i].name);
		printf("Designation: %s\n", emp[i].designation);
		printf("Salary: %.2f\n", emp[i].salary);
		printf("---------------------\n");
	}
}

void findHighestSalary(struct employee emp[], int n){
	float max = emp[0].salary;
	int index = 0;
	
	for(int i=1; i<n; i++){
		if(max < emp[i].salary){
			max = emp[i].salary;
			index = i;
		}
	}
	
    printf("\nEmployee %d has highest salary\n", index);
    printf("ID: %d\n", emp[index].ID);
    printf("Name: %s\n", emp[index].name);
    printf("Designation: %s\n", emp[index].designation);
    printf("Salary: %.2f\n", emp[index].salary);
}

void searchEmployee(struct employee emp[], int n){
	int choice;
	printf("\n1. Search by ID\n");
	printf("2. Search by name\n");
	printf("Your choice--> ");
	scanf("%d", &choice);
	
	switch(choice){
		case 1:{
			int search;
			int index = 0;
			printf("\nEnter employee ID: ");
			scanf("%d", &search);
			
			for(int i=0; i<n; i++){
				if(search == emp[i].ID){
					index = i;
					printf("Employee exists!");
					break;  //break because ID is unique or primary key
				}
			}
			break;
		}
		
		case 2:{
			char search[50];
			int index = 0;
			printf("\nEnter employee name: ");
			scanf("%s", search);
			
			for(int i=0; i<n; i++){
				if((strcmp(search, emp[i].name) == 0)){
					index = i;
					printf("Employee exists!"); //more than one employee can be of same name so no break
				}
			}
			break;
		}
		
		default:{
			printf("Invalid choice!");
			break;
		}
	}
}

void salaryBonus(struct employee emp[], int n){
	
	for(int i=0; i<n; i++){
		if(emp[i].salary < 50000){
			emp[i].salary += (emp[i].salary * 0.10);
		}
	}
}
