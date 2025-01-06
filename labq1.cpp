#include <stdio.h>
#include <string.h>

void caesar_cipher(char* plaintext, int k) {
    int i;
    char ch;
    
    
    for (i = 0; plaintext[i] != '\0'; i++) {
        ch = plaintext[i];

        
        if (ch >= 'A' && ch <= 'Z') {
            ch = ((ch - 'A' + k) % 26) + 'A';
            plaintext[i] = ch;
        }
       
        else if (ch >= 'a' && ch <= 'z') {
            ch = ((ch - 'a' + k) % 26) + 'a';
            plaintext[i] = ch;
        }
        
    }
}

int main() {
    char plaintext[100];
    int k;
    
    
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    
    plaintext[strcspn(plaintext, "\n")] = '\0';
    
    printf("Enter the shift value (k): ");
    scanf("%d", &k);

    
    if (k < 1 || k > 25) {
        printf("Invalid shift value! Please enter a value between 1 and 25.\n");
        return 1;
    }

    
    caesar_cipher(plaintext, k);
    
    
    printf("Encrypted text: %s\n", plaintext);
    
    return 0;
}

