#include <stdio.h>
#include <string.h>

void encodeMessage(char message[]);
void decodeMessage(char message[]);
void reverseString(char str[]);
char toggleBits(char ch);

int main() {
    char message[1000];
    int choice;

    do {
        printf("\n===== TCS Secure Messaging =====\n");
        printf("1. Encode Message\n");
        printf("2. Decode Message\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); 

        switch(choice){
            case 1:{
            	printf("Enter message to encode: ");
                fgets(message, sizeof(message), stdin);
                message[strcspn(message, "\n")] = '\0';
                encodeMessage(message);
				break;
			}
            case 2:{
            	printf("Enter message to decode: ");
                fgets(message, sizeof(message), stdin);
                message[strcspn(message, "\n")] = '\0'; 
                decodeMessage(message);
                break;
			}
                
            case 3:{
            	printf("Exiting program...\n");
				break;
			}
                
            default:{
            	printf("Invalid choice! Try again.\n");
				break;
			}        
        }
    } while (choice != 3);
    return 0;
}


void encodeMessage(char message[]) {
    reverseString(message);

    for(int i=0; message[i] != '\0'; i++){
        message[i] = toggleBits(message[i]);
    }
    printf("\nEncoded Message: %s\n", message);
}


void decodeMessage(char message[]) {
    for(int i=0; message[i] != '\0'; i++){
        message[i] = toggleBits(message[i]); // untoggle
    }
    reverseString(message);
    printf("\nDecoded Message: %s\n", message);
}


void reverseString(char str[]) {
    int len = strlen(str);
    for (int i=0; i<len/2; i++) {
        char temp = str[i];
        str[i] = str[len-1 - i];
        str[len-1 - i] = temp;
    }
}


char toggleBits(char ch) {
    ch ^= (1 << 1); 
    ch ^= (1 << 4); 
    return ch;
}

