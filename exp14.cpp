#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Function to generate a random key
void generateKey(char *key, int length) {
    for (int i = 0; i < length; i++) {
        key[i] = 'A' + rand() % 26; // Random character between A and Z
    }
    key[length] = '\0';
}

// Function to encrypt the plaintext using the key
void encrypt(const char *plaintext, const char *key, char *ciphertext) {
    int len = strlen(plaintext);
    for (int i = 0; i < len; i++) {
        ciphertext[i] = ((plaintext[i] - 'A') + (key[i] - 'A')) % 26 + 'A';
    }
    ciphertext[len] = '\0';
}

// Function to decrypt the ciphertext using the key
void decrypt(const char *ciphertext, const char *key, char *plaintext) {
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i++) {
        plaintext[i] = ((ciphertext[i] - 'A') - (key[i] - 'A') + 26) % 26 + 'A';
    }
    plaintext[len] = '\0';
}

int main() {
    char plaintext[100], ciphertext[100], decryptedText[100], key[100];

    // Input plaintext
    printf("Enter plaintext (uppercase only): ");
    scanf("%s", plaintext);

    // Validate plaintext
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (plaintext[i] < 'A' || plaintext[i] > 'Z') {
            printf("Error: Plaintext must be uppercase letters only.\n");
            return 1;
        }
    }

    // Generate random key
    srand(time(0)); // Seed random number generator
    generateKey(key, strlen(plaintext));

    printf("Generated Key: %s\n", key);

    // Encrypt the plaintext
    encrypt(plaintext, key, ciphertext);
    printf("Encrypted Text: %s\n", ciphertext);

    // Decrypt the ciphertext
    decrypt(ciphertext, key, decryptedText);
    printf("Decrypted Text: %s\n", decryptedText);

    return 0;
}

