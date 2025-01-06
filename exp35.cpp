#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Function to generate a random OTP key of the same length as the message
void generate_otp_key(char *key, int length) {
    srand(time(NULL));  // Seed the random number generator
    for (int i = 0; i < length; i++) {
        key[i] = 'A' + (rand() % 26);  // Generate a random uppercase letter (A-Z)
    }
    key[length] = '\0';  // Null-terminate the key
}

// Function to encrypt a message using the One-Time Pad (Vigenère Cipher)
void otp_encrypt(char *plaintext, char *ciphertext, char *key, int length) {
    for (int i = 0; i < length; i++) {
        ciphertext[i] = ((plaintext[i] - 'A') + (key[i] - 'A')) % 26 + 'A';  // Vigenère encryption
    }
    ciphertext[length] = '\0';  // Null-terminate the ciphertext
}

// Function to decrypt a message using the One-Time Pad (Vigenère Cipher)
void otp_decrypt(char *ciphertext, char *plaintext, char *key, int length) {
    for (int i = 0; i < length; i++) {
        plaintext[i] = ((ciphertext[i] - 'A') - (key[i] - 'A') + 26) % 26 + 'A';  // Vigenère decryption
    }
    plaintext[length] = '\0';  // Null-terminate the plaintext
}

int main() {
    char plaintext[] = "HELLOTHISISATEST";  // The message to encrypt
    int length = strlen(plaintext);

    // Generate a One-Time Pad (OTP) key of the same length as the plaintext
    char otp_key[length + 1];
    generate_otp_key(otp_key, length);
    
    // Print the OTP key
    printf("OTP Key: %s\n", otp_key);

    // Encrypt the plaintext using the OTP and Vigenère Cipher
    char ciphertext[length + 1];
    otp_encrypt(plaintext, ciphertext, otp_key, length);

    // Print the ciphertext
    printf("Ciphertext: %s\n", ciphertext);

    // Decrypt the ciphertext using the same OTP key
    char decryptedtext[length + 1];
    otp_decrypt(ciphertext, decryptedtext, otp_key, length);

    // Print the decrypted message
    printf("Decrypted Message: %s\n", decryptedtext);

    return 0;
}

