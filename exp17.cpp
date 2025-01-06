#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define BLOCK_SIZE 8 // 8 bytes (64 bits)

// Simplified permutation tables
const int INITIAL_PERMUTATION[64] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};

const int FINAL_PERMUTATION[64] = {
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25
};

// Simplified round key
const uint64_t ROUND_KEY = 0x1A2B3C4D5E6F7081;

// Function to perform permutation
uint64_t permute(uint64_t input, const int *table, int n) {
    uint64_t output = 0;
    for (int i = 0; i < n; i++) {
        output |= ((input >> (64 - table[i])) & 0x1) << (n - 1 - i);
    }
    return output;
}

// Simplified Feistel function
uint32_t feistel(uint32_t half_block, uint64_t round_key) {
    // XOR with the round key (simplified operation)
    return (half_block ^ (uint32_t)(round_key & 0xFFFFFFFF));
}

// DES encryption function
uint64_t des_encrypt(uint64_t plaintext) {
    // Initial Permutation (IP)
    uint64_t permuted = permute(plaintext, INITIAL_PERMUTATION, 64);

    // Split into left and right halves
    uint32_t left = (permuted >> 32) & 0xFFFFFFFF;
    uint32_t right = permuted & 0xFFFFFFFF;

    // Perform 16 rounds (simplified to 1 round here for brevity)
    for (int i = 0; i < 1; i++) {
        uint32_t temp = right;
        right = left ^ feistel(right, ROUND_KEY); // XOR left with Feistel output
        left = temp;
    }

    // Combine left and right
    uint64_t combined = ((uint64_t)right << 32) | left;

    // Final Permutation (FP)
    uint64_t ciphertext = permute(combined, FINAL_PERMUTATION, 64);

    return ciphertext;
}

// DES decryption function
uint64_t des_decrypt(uint64_t ciphertext) {
    // Initial Permutation (IP)
    uint64_t permuted = permute(ciphertext, INITIAL_PERMUTATION, 64);

    // Split into left and right halves
    uint32_t left = (permuted >> 32) & 0xFFFFFFFF;
    uint32_t right = permuted & 0xFFFFFFFF;

    // Perform 16 rounds (simplified to 1 round here for brevity)
    for (int i = 0; i < 1; i++) {
        uint32_t temp = left;
        left = right ^ feistel(left, ROUND_KEY); // XOR right with Feistel output
        right = temp;
    }

    // Combine left and right
    uint64_t combined = ((uint64_t)right << 32) | left;

    // Final Permutation (FP)
    uint64_t plaintext = permute(combined, FINAL_PERMUTATION, 64);

    return plaintext;
}

int main() {
    uint64_t plaintext = 0x1234567890ABCDEF;
    printf("Plaintext: 0x%016lX\n", plaintext);

    // Encrypt the plaintext
    uint64_t ciphertext = des_encrypt(plaintext);
    printf("Ciphertext: 0x%016lX\n", ciphertext);

    // Decrypt the ciphertext
    uint64_t decrypted = des_decrypt(ciphertext);
    printf("Decrypted Text: 0x%016lX\n", decrypted);

    return 0;
}

