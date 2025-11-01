#include<stdio.h>

void menuOptions();
void credentials(char name[], int *cnic);
void displayInventory(int productCode[], int quantity[], int price[]);
void updateQuantity(int productCode[], int quantity[]);
void addToCart(int productCode[], int quantity[], int cart[][2], int *cartCount);
float displayTotalBill(int productCode[], int price[], int cart[][2], int *cartCount, float *total_bill);
void showInvoice(char name[], int cnic, float total_bill, float final_bill);

int main(){
	int productCode[4] = {001, 002, 003, 004};
	int quantity[4] = {50, 10, 20, 8};
	int price[4] = {100, 200, 300, 150};
	
	int cart[4][2]; //[][0] productcode, [][1] quantity
	int cartCount = 0; 
	
	int option;
	char name[50];
	int cnic;
	float total_bill=0, final_bill=0;
	
	do{
		menuOptions();
		printf("Select your option: ");
	    scanf("%d", &option);
		switch(option){
			case 1:{
				credentials(name, &cnic);
				break;
			}
			case 2:{
				displayInventory(productCode, quantity, price);
				break;
			}
			case 3:{
				updateQuantity(productCode, quantity);
				break;
			}
			case 4:{
				addToCart(productCode, quantity, cart, &cartCount);
				break;
			}
			case 5:{
				final_bill = displayTotalBill(productCode, price, cart, &cartCount, &total_bill);
				
				printf("Total bill: %.2f", final_bill);
				break;
			}
			case 6:{
				showInvoice(name, cnic, total_bill, final_bill);
				break;
			}
			case 7:{
				printf("Exit successfully! Good Bye.\n");
				break;
			}
			default:{
				printf("Invalid option! Try again.\n");
				break;
			}
		}
	}while(option != 7);
	
	return 0;
}


void menuOptions(){
	printf("\n========== Supermarket ==========\n");
	printf("1. Customer information\n");
	printf("2. Display inventory\n");
	printf("3. Update inventory\n");
	printf("4. Add items to cart\n");
	printf("5. Display total bill\n");
	printf("6. Display invoice\n");
	printf("7. Exit\n");
}


void credentials(char name[], int *cnic){
	printf("\nEnter customer name: ");
	while(getchar() != '\n');
	fgets(name, 50, stdin);
	printf("Enter customer CNIC: ");
	scanf("%d", cnic);
}


void displayInventory(int productCode[], int quantity[], int price[]){
	printf("\nProduct Code    Quantity     Price\n");
	printf("------------------------------------\n");
	for(int i=0; i<4; i++){
		printf("00%d\t\t%d\t\t%d", productCode[i], quantity[i], price[i]);
		printf("\n");
	}	
}


void updateQuantity(int productCode[], int quantity[]){
	int code, qty;
	printf("\nEnter product code to update: ");
	scanf("%d", &code);
	printf("Enter product(00%d) quantity purchased: ", code);
	scanf("%d", &qty);
	
	int found = 0;
	for(int i=0; i<4; i++){
		if(productCode[i] == code){
			found = 1;
			if(quantity[i] >= qty){
				quantity[i] -= qty;
	            printf("Purchased successfully! Quantity updated.\n");
	            printf("Remaining product(%d) quantity: %d\n", code, quantity[i]);
			}
			else if(quantity[i] < qty){
				printf("Quantity limit exceeded!\n");
			}
			else if(quantity[i]==0){
				printf("Out of stock!\n");
			}
			break;
		}
	}
	if(found==0){
		printf("Invalid product code!\n");
	}
}


void addToCart(int productCode[], int quantity[], int cart[][2], int *cartCount){   
	int code, qty;
	printf("\nEnter product code to add to cart: ");
	scanf("%d", &code);
	printf("Enter product(%d) quantity", code);
	scanf("%d", &qty);
	
	int found = 0;
	for(int i=0; i<4; i++){
		if(productCode[i] == code){
			found = 1;
			if(quantity[i]==0){
				printf("Out of stock!\n");
			}
			else if(quantity[i] < qty){
				printf("Quantity limit exceeded!\n");
			}
			else if(quantity[i] >= qty){
				cart[*cartCount][0] = code;
				cart[*cartCount][1] = qty;
	            printf("Added to cart successfully!.\n");
	            (*cartCount)++;
			}
			break;
		}
	}
	if(found==0){
		printf("Invalid product code!\n");
	}
}


float displayTotalBill(int productCode[], int price[], int cart[][2], int *cartCount, float *total_bill){
    *total_bill = 0;

    for (int i = 0; i<*cartCount; i++){
        int code = cart[i][0];
        int qty = cart[i][1];

        for (int j=0; j<4; j++){
            if (productCode[j] == code){
                *total_bill += price[j] * qty;
            }
        }
    }

    char yn;
    printf("We are offering a promocode of Eid2025!\n");
    printf("Do you have a voucher? (y/n): ");
    scanf(" %c", &yn);

    if(yn == 'y' || yn == 'Y'){
        float discounted = (*total_bill) * 0.75; // 25% off
        return discounted;
    }
	else{
        printf("Sorry, you can't avail Eid discount.\n");
        return *total_bill;
    }
}


void showInvoice(char name[], int cnic, float total_bill, float final_bill){
	printf("\n======== Invoice ========\n");
	printf("Customer name: %s", name);
	printf("Customer CNIC: %d", cnic);
	printf("Bill (initial): %.2f", total_bill);
	printf("Bill (after discount): %.2f", final_bill);
	printf("\n=========================\n");
}


