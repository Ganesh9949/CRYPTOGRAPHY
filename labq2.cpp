#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

// Function to encrypt using Monoalphabetic Substitution Cipher
void monoalphabetic_substitution(char* plaintext, char* cipher_alphabet) {
    int i;
    char ch;
    
    // Convert plaintext to uppercase and substitute
    for (i = 0; plaintext[i] != '\0'; i++) {
        ch = plaintext[i];
        
        // If the character is a letter, substitute it
        if (isalpha(ch)) {
            ch = toupper(ch);  // Convert to uppercase
            int index = ch - 'A';  // Find index in the alphabet
            plaintext[i] = cipher_alphabet[index];  // Substitute from cipher alphabet
        }
    }
}

int main() {
    char plaintext[100];
    char cipher_alphabet[ALPHABET_SIZE + 1];  // 26 letters + 1 for null-terminator
    
    // Input the plaintext
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    // Remove newline character if present
    plaintext[strcspn(plaintext, "\n")] = '\0';  
    
    // Input the cipher alphabet
    printf("Enter the cipher alphabet (26 unique letters): ");
    fgets(cipher_alphabet, sizeof(cipher_alphabet), stdin);
    // Remove newline character if present
    cipher_alphabet[strcspn(cipher_alphabet, "\n")] = '\0'; 

    // Ensure that the cipher alphabet is exactly 26 characters long
    if (strlen(cipher_alphabet) != ALPHABET_SIZE) {
        printf("Error: The cipher alphabet must be exactly 26 characters long.\n");
        return 1;
    }

    // Ensure all characters in the cipher alphabet are unique
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        for (int j = i + 1; j < ALPHABET_SIZE; j++) {
            if (cipher_alphabet[i] == cipher_alphabet[j]) {
                printf("Error: The cipher alphabet must contain only unique characters.\n");
                return 1;
            }
        }
    }

    // Encrypt the plaintext using the monoalphabetic substitution cipher
    monoalphabetic_substitution(plaintext, cipher_alphabet);

    // Output the encrypted text
    printf("Encrypted text: %s\n", plaintext);

    return 0;
}

