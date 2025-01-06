#include <stdio.h>
#include <string.h>
#include <ctype.h>


void encrypt_vigenere(char* plaintext, char* key, char* ciphertext) {
    int i, j = 0;
    int key_length = strlen(key);
    
    
    for (i = 0; plaintext[i] != '\0'; i++) {
       
        if (isalpha(plaintext[i])) {
            char current_char = toupper(plaintext[i]);  
            char key_char = toupper(key[j % key_length]); 
            
            
            ciphertext[i] = ((current_char - 'A') + (key_char - 'A')) % 26 + 'A';
            
           
            j++;
        } else {
            
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[i] = '\0';  
}

int main() {
    char plaintext[100], key[100], ciphertext[100];
    
   
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';  
    
   
    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';  

    
    encrypt_vigenere(plaintext, key, ciphertext);

  
    printf("Encrypted text: %s\n", ciphertext);
    
    return 0;
}

