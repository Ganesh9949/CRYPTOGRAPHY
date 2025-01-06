#include <stdio.h>
#include <string.h>

// Function to perform XOR encryption/decryption
void xor_encrypt_decrypt(char *text, const char *key) {
    int text_len = strlen(text);
    int key_len = strlen(key);

    for (int i = 0; i < text_len; i++) {
        text[i] ^= key[i % key_len];  // XOR each byte of text with the key
    }
}

int main() {
    char text[256];    // Input text
    char key[256];     // Key for encryption and decryption

    // Input plaintext and key
    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';  // Remove newline character from the input

    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';  // Remove newline character from the input

    // Encrypt the text using XOR encryption
    char encrypted_text[256];
    strcpy(encrypted_text, text);   // Copy original text to encrypted_text
    xor_encrypt_decrypt(encrypted_text, key);
    printf("Encrypted text: ");
    for (int i = 0; encrypted_text[i] != '\0'; i++) {
        printf("%02X", (unsigned char)encrypted_text[i]);  // Print as hexadecimal
    }
    printf("\n");

    // Decrypt the encrypted text
    xor_encrypt_decrypt(encrypted_text, key);  // XOR again to decrypt
    printf("Decrypted text: %s\n", encrypted_text);

    return 0;
}

