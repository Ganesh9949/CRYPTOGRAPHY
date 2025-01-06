#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE 8 // Block size in bytes (64 bits)

// Function to perform a simple XOR encryption
void xor_encrypt_decrypt(char *block, const char *key) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        block[i] ^= key[i % strlen(key)];
    }
}

// Function to pad the plaintext to a multiple of BLOCK_SIZE
int pad_plaintext(char *plaintext) {
    int len = strlen(plaintext);
    int pad_size = BLOCK_SIZE - (len % BLOCK_SIZE);
    for (int i = len; i < len + pad_size; i++) {
        plaintext[i] = (char)pad_size; // Padding value is the size of padding
    }
    plaintext[len + pad_size] = '\0';
    return len + pad_size; // Return new length
}

// Function to encrypt using ECB mode
void ecb_encrypt(char *plaintext, char *ciphertext, const char *key) {
    char block[BLOCK_SIZE];
    int len = strlen(plaintext);

    for (int i = 0; i < len; i += BLOCK_SIZE) {
        strncpy(block, plaintext + i, BLOCK_SIZE); // Copy a block
        xor_encrypt_decrypt(block, key);          // Encrypt the block
        strncpy(ciphertext + i, block, BLOCK_SIZE); // Write to ciphertext
    }
}

// Function to decrypt using ECB mode
void ecb_decrypt(char *ciphertext, char *decrypted, const char *key) {
    char block[BLOCK_SIZE];
    int len = strlen(ciphertext);

    for (int i = 0; i < len; i += BLOCK_SIZE) {
        strncpy(block, ciphertext + i, BLOCK_SIZE); // Copy a block
        xor_encrypt_decrypt(block, key);           // Decrypt the block
        strncpy(decrypted + i, block, BLOCK_SIZE); // Write to decrypted text
    }
}

int main() {
    char plaintext[256];
    char key[BLOCK_SIZE + 1]; // Key length must be BLOCK_SIZE or less
    char ciphertext[256] = {0};
    char decrypted[256] = {0};

    // Input plaintext and key
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove newline character

    printf("Enter the key (max %d characters): ", BLOCK_SIZE);
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; // Remove newline character

    // Pad plaintext to a multiple of BLOCK_SIZE
    int padded_len = pad_plaintext(plaintext);

    // Encrypt the plaintext
    ecb_encrypt(plaintext, ciphertext, key);
    printf("Ciphertext (hex): ");
    for (int i = 0; i < padded_len; i++) {
        printf("%02X", (unsigned char)ciphertext[i]);
    }
    printf("\n");

    // Decrypt the ciphertext
    ecb_decrypt(ciphertext, decrypted, key);
    printf("Decrypted text: %s\n", decrypted);

    return 0;
}

