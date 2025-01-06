#include <stdio.h>
#include <string.h>
#include <ctype.h>
void encrypt(char *message, int k) 
{
    k = k % 26;
 for (int i = 0; message[i] != '\0'; i++) 
 {
        char ch = message[i];
        if (isupper(ch)) {
            message[i] = 'A' + (ch - 'A' + k) % 26;
        }
        else if (islower(ch)) {
            message[i] = 'a' + (ch - 'a' + k) % 26;
        }
    }
}

int main() {
    char message[100];
    int k;

    printf("Enter a message to encrypt: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0'; 
    printf("Enter the shift value (1-25): ");
    scanf("%d", &k);

    if (k < 1 || k > 25) {
        printf("Invalid shift value. Please enter a value between 1 and 25.\n");
        return 1;
    }

    encrypt(message, k);

    printf("Encrypted message: %s\n", message);

    return 0;
}
