#include <stdio.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/rand.h>

#define AES_KEY_LENGTH 128 // AES key length in bits (128, 192, or 256)
#define AES_BLOCK_SIZE 16  // AES block size in bytes

// Function to encrypt the data using AES in CFB mode
void aes_encrypt_cfb(const unsigned char *input, unsigned char *output, unsigned char *key, unsigned char *iv) {
    AES_KEY encrypt_key;
    
    // Set the encryption key
    AES_set_encrypt_key(key, AES_KEY_LENGTH, &encrypt_key);
    
    // Encrypt the data using CFB mode
    AES_cfb128_encrypt(input, output, strlen((const char *)input), &encrypt_key, iv, NULL, AES_ENCRYPT);
}

// Function to decrypt the data using AES in CFB mode
void aes_decrypt_cfb(const unsigned char *input, unsigned char *output, unsigned char *key, unsigned char *iv) {
    AES_KEY decrypt_key;
    
    // Set the decryption key
    AES_set_decrypt_key(key, AES_KEY_LENGTH, &decrypt_key);
    
    // Decrypt the data using CFB mode
    AES_cfb128_encrypt(input, output, strlen((const char *)input), &decrypt_key, iv, NULL, AES_DECRYPT);
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
    unsigned char input_data[] = "This is a test message for AES encryption in CFB mode!";
    size_t input_len = strlen((const char *)input_data);
    
    // Output buffer for encrypted and decrypted data
    unsigned char encrypted_data[input_len];
    unsigned char decrypted_data[input_len];
    
    // Encrypt the data using CFB mode
    printf("Original Message: %s\n", input_data);
    aes_encrypt_cfb(input_data, encrypted_data, key, iv);
    
    printf("Encrypted Data (in hex): ");
    print_hex(encrypted_data, input_len);
    
    // Decrypt the data using CFB mode
    aes_decrypt_cfb(encrypted_data, decrypted_data, key, iv);
    
    // Null-terminate the decrypted data
    decrypted_data[input_len] = '\0';
    
    // Print decrypted data
    printf("Decrypted Message: %s\n", decrypted_data);
    
    return 0;
}

