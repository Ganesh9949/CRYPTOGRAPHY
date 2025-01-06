#include <stdio.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/rand.h>

#define AES_KEY_LENGTH 128 // AES key length in bits (128, 192, or 256)
#define AES_BLOCK_SIZE 16  // AES block size in bytes

// Function to encrypt the data using AES in CBC mode
void aes_encrypt(const unsigned char *input, unsigned char *output, unsigned char *key, unsigned char *iv) {
    AES_KEY encrypt_key;
    
    // Set the encryption key
    AES_set_encrypt_key(key, AES_KEY_LENGTH, &encrypt_key);
    
    // Encrypt the input data (input must be a multiple of AES_BLOCK_SIZE)
    AES_cbc_encrypt(input, output, strlen((const char *)input), &encrypt_key, iv, AES_ENCRYPT);
}

// Function to decrypt the data using AES in CBC mode
void aes_decrypt(const unsigned char *input, unsigned char *output, unsigned char *key, unsigned char *iv) {
    AES_KEY decrypt_key;
    
    // Set the decryption key
    AES_set_decrypt_key(key, AES_KEY_LENGTH, &decrypt_key);
    
    // Decrypt the data (input must be a multiple of AES_BLOCK_SIZE)
    AES_cbc_encrypt(input, output, strlen((const char *)input), &decrypt_key, iv, AES_DECRYPT);
}

// Function to print the output in hexadecimal format
void print_hex(unsigned char *data, size_t len) {
    for (size_t i = 0; i < len; i++) {
        printf("%02x", data[i]);
    }
    printf("\n");
}

int main() {
    // Key and IV for AES (must be 16 bytes long for AES-128)
    unsigned char key[AES_BLOCK_SIZE] = "1234567890abcdef";  // 128-bit key
    unsigned char iv[AES_BLOCK_SIZE] = "abcdef9876543210";   // Initialization vector
    
    // Sample input data (message)
    unsigned char input_data[] = "This is a test message for AES encryption!";
    size_t input_len = strlen((const char *)input_data);
    
    // Padding the input data to be a multiple of AES_BLOCK_SIZE
    size_t padded_len = ((input_len / AES_BLOCK_SIZE) + 1) * AES_BLOCK_SIZE;
    unsigned char padded_input[padded_len];
    memset(padded_input, 0, padded_len);
    memcpy(padded_input, input_data, input_len);
    
    // Output buffer for encrypted and decrypted data
    unsigned char encrypted_data[padded_len];
    unsigned char decrypted_data[padded_len];
    
    // Encrypt the data
    printf("Original Message: %s\n", input_data);
    aes_encrypt(padded_input, encrypted_data, key, iv);
    
    printf("Encrypted Data (in hex): ");
    print_hex(encrypted_data, padded_len);
    
    // Reset IV for decryption (IV must be the same for both encryption and decryption)
    unsigned char iv_decrypt[AES_BLOCK_SIZE];
    memcpy(iv_decrypt, iv, AES_BLOCK_SIZE);
    
    // Decrypt the data
    aes_decrypt(encrypted_data, decrypted_data, key, iv_decrypt);
    
    // Null-terminate the decrypted data
    decrypted_data[padded_len] = '\0';
    
    // Print decrypted data
    printf("Decrypted Message: %s\n", decrypted_data);
    
    return 0;
}

