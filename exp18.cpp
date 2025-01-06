#include <stdio.h>
#include <stdint.h>

#define BLOCK_SIZE 24 // Only process 24 bits

// Simplified permutation tables (24 bits)
const int INITIAL_PERMUTATION[BLOCK_SIZE] = {
    2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24,
    1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23
};

const int FINAL_PERMUTATION[BLOCK_SIZE] = {
    12, 10, 8, 6, 4, 2, 24, 22, 20, 18, 16, 14,
    1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23
};

// Simplified round key for the 24-bit block
const uint32_t ROUND_KEY = 0x5A5A5A; // Example 24-bit key (binary pattern: 01011010...)

// Function to perform a permutation
uint32_t permute(uint32_t input, const int *table, int size) {
    uint32_t output = 0;
    for (int i = 0; i < size; i++) {
        output |= ((input >> (size - table[i])) & 0x1) << (size - 1 - i);
    }
    return output;
}

// Simplified Feistel function
uint32_t feistel(uint32_t half_block, uint32_t round_key) {
    // XOR operation with the round key
    return half_block ^ round_key;
}

// Encrypt 24-bit block
uint32_t des_encrypt(uint32_t plaintext) {
    // Initial Permutation (IP)
    uint32_t permuted = permute(plaintext, INITIAL_PERMUTATION, BLOCK_SIZE);

    // Split into left and right halves (12 bits each)
    uint16_t left = (permuted >> 12) & 0xFFF;  // Top 12 bits
    uint16_t right = permuted & 0xFFF;         // Bottom 12 bits

    // Perform 1 encryption round
    uint16_t temp = right;
    right = left ^ feistel(right, ROUND_KEY); // XOR left with Feistel output
    left = temp;

    // Combine left and right halves
    uint32_t combined = ((uint32_t)right << 12) | left;

    // Final Permutation (FP)
    uint32_t ciphertext = permute(combined, FINAL_PERMUTATION, BLOCK_SIZE);

    return ciphertext;
}

// Decrypt 24-bit block
uint32_t des_decrypt(uint32_t ciphertext) {
    // Initial Permutation (IP)
    uint32_t permuted = permute(ciphertext, INITIAL_PERMUTATION, BLOCK_SIZE);

    // Split into left and right halves (12 bits each)
    uint16_t left = (permuted >> 12) & 0xFFF;  // Top 12 bits
    uint16_t right = permuted & 0xFFF;         // Bottom 12 bits

    // Perform 1 decryption round
    uint16_t temp = left;
    left = right ^ feistel(left, ROUND_KEY); // XOR right with Feistel output
    right = temp;

    // Combine left and right halves
    uint32_t combined = ((uint32_t)right << 12) | left;

    // Final Permutation (FP)
    uint32_t plaintext = permute(combined, FINAL_PERMUTATION, BLOCK_SIZE);

    return plaintext;
}

int main() {
    uint32_t plaintext = 0xABCDEF; // Example 24-bit plaintext (binary: 101010111100110111101111)
    printf("Plaintext: 0x%06X\n", plaintext);

    // Encrypt the plaintext
    uint32_t ciphertext = des_encrypt(plaintext);
    printf("Ciphertext: 0x%06X\n", ciphertext);

    // Decrypt the ciphertext
    uint32_t decrypted = des_decrypt(ciphertext);
    printf("Decrypted Text: 0x%06X\n", decrypted);

    return 0;
}

