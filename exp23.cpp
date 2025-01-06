#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define BLOCK_SIZE 16 // Block size in bytes (128 bits)

// Function to perform XOR encryption/decryption in CTR mode
void ctr_encrypt_decrypt(char *text, const char *key, uint64_t counter) {
    uint8_t block[BLOCK_SIZE];
    uint8_t keystream[BLOCK_SIZE];
    int text_len = strlen(text);
    int key_len = strlen(key);

    for (int i = 0; i < text_len; i += BLOCK_SIZE) {
        // Generate keystream: Encrypt the counter with the key (simulated by XOR with the key)
        memset(block, 0, BLOCK_SIZE); // Clear block
        for (int j = 0; j < BLOCK_SIZE; j++) {
            block[j] = (counter >> (8 * (BLOCK_SIZE - j - 1))) & 0xFF; // Fill block with counter bytes
        }

        // XOR with the key (simple XOR simulation)
        for (int j = 0; j < BLOCK_SIZE; j++) {
            keystream[j] = block[j] ^ key[j % key_len];
        }

        // XOR the plaintext with the keystream to get ciphertext
        for (int j = 0; j < BLOCK_SIZE && (i + j) < text_len; j++) {
            text[i + j] ^= keystream[j];  // XOR with keystream
        }

        counter++;  // Increment the counter for next block
    }
}

int main() {
    char plaintext[256];   // Input text
    char key[BLOCK_SIZE + 1]; // Key (must be the same length or smaller than BLOCK_SIZE)
    uint64_t counter;      // Counter for CTR mode

    // Input plaintext and key
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';  // Remove newline character from the input

    printf("Enter the key (max %d characters): ", BLOCK_SIZE);
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';  // Remove newline character from the input

    printf("Enter the starting counter value (integer): ");
    scanf("%llu", &counter);  // Read the counter as unsigned long long

    // Encrypt the plaintext using CTR mode
    char encrypted_text[256];
    strcpy(encrypted_text, plaintext);  // Copy plaintext to encrypted text
    ctr_encrypt_decrypt(encrypted_text, key, counter);
    printf("Encrypted text (hex): ");
    for (int i = 0; encrypted_text[i] != '\0'; i++) {
        printf("%02X", (unsigned char)encrypted_text[i]);  // Print as hexadecimal
    }
    printf("\n");

    // Decrypt the ciphertext (CTR is symmetric, so encryption and decryption are the same)
    ctr_encrypt_decrypt(encrypted_text, key, counter);
    printf("Decrypted text: %s\n", encrypted_text);

    return 0;
}

