#include<stdio.h>

void mainMenu();
void addBook(int isbn[], char title[][50], float price[], int quantity[], int *bookCount);
void processSale(int isbn[], int quantity[], int *bookCount);
void lowStockReport(int isbn[], char title[][50], float price[], int quantity[], int *bookCount);

int main(){
    int isbn[100];
    char title[100][50];
    float price[100];
    int quantity[100];
    int choice, bookCount = 0;  
	
	do{
		mainMenu();
     	printf("Enter your choice: ");
	    scanf("%d", &choice);
	    printf("================================\n");
	    
		switch(choice){
		case 1: {
			addBook(isbn, title, price, quantity, &bookCount);
			break;
		}
		case 2: {
			processSale(isbn, quantity, &bookCount);
			break;
		}
		case 3: {
			lowStockReport(isbn, title, price, quantity, &bookCount);
			break;
		}
		case 4: {
			printf("Exiting...Good Bye!\n");
			break;
		}
		default:
			printf("Invalid choice! Try again.");
	    }
	} while(choice!=4);
	
	return 0;
}


void mainMenu()
{
	printf("\n====== LIBERTY BOOKS MENU ======\n");
	printf("1. Add new book\n");
	printf("2. Process a sale\n");
	printf("3. Generate low-stock report\n");
	printf("4. Exit\n");
}

void addBook(int isbn[], char title[][50], float price[], int quantity[], int *bookCount)
{
	int newISBN, found=0;
	printf("\nEnter book ISBN: ");
	scanf("%d", &newISBN);
	
	for(int i=0; i<*bookCount; i++){
		if(isbn[i] == newISBN){
			found = 1; 
			break;
		}
	}
	
	if(found==1){
		printf("Duplicate ISBN found! Book not added.\n");
	}
	else{
		isbn[*bookCount] = newISBN;
		
		printf("Enter book title: ");
		while(getchar() != '\n');
	    fgets(title[*bookCount], 50, stdin);
        printf("Enter book price: ");
        scanf("%f", &price[*bookCount]);
    	printf("Enter book quantity: ");
    	scanf("%d", &quantity[*bookCount]);
    	
    	(*bookCount)++;
    	printf("Book added successfully!\n");
	}
	
}

void processSale(int isbn[], int quantity[], int *bookCount)
{
	int searchISBN, copiesSold, found=0;
	printf("\nEnter book ISBN: ");
	scanf("%d", &searchISBN);
	printf("Enter number of copies sold: ");
	scanf("%d", &copiesSold);
	
	for(int i=0; i<*bookCount; i++){
		if(isbn[i] == searchISBN){
			found = 1;
			if(quantity[i] == 0){
		        printf("Book is out of stock!\n");
		    }
		    else if(quantity[i] < copiesSold){
			    printf("Quantity limit exceeded!\n");
		    }
		    else{
			    quantity[i] -= copiesSold;
			    printf("Sale processed successfully! Remaing quantity: %d\n", quantity[i]);
		    }
		    break;	
		}
	}
	if(found==0){
		printf("Book not found! Try again.\n");
	}
}

void lowStockReport(int isbn[], char title[][50], float price[], int quantity[], int *bookCount){
	int found=0;
	printf("\n(Low Stock Report)\n");
	for(int i=0; i<*bookCount; i++){
		if(quantity[i] < 5){
			found = 1;
			printf("ISBN: %d ", isbn[i]);
			printf("\nTitle: %s ", title[i]);
			printf("\nPrice: %.2f ", price[i]);
			printf("\nQuantity: %d ", quantity[i]);
			printf("\n------------------------------\n");
		}
	}
	if(found==0){
		printf("All books have sufficient stock.\n");
		printf("\n------------------------------\n");
	}
}
