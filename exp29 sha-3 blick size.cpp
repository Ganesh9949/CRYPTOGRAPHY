#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

void sha3_hash(const char *input, unsigned char *output, size_t block_size) {
    // Check block_size and select SHA3 function based on it
    switch (block_size) {
        case 224:
            SHA3_224_CTX ctx_224;
            SHA3_224_Init(&ctx_224);
            SHA3_224_Update(&ctx_224, (const unsigned char*)input, strlen(input));
            SHA3_224_Final(output, &ctx_224);
            break;
        case 256:
            SHA3_256_CTX ctx_256;
            SHA3_256_Init(&ctx_256);
            SHA3_256_Update(&ctx_256, (const unsigned char*)input, strlen(input));
            SHA3_256_Final(output, &ctx_256);
            break;
        case 384:
            SHA3_384_CTX ctx_384;
            SHA3_384_Init(&ctx_384);
            SHA3_384_Update(&ctx_384, (const unsigned char*)input, strlen(input));
            SHA3_384_Final(output, &ctx_384);
            break;
        case 512:
            SHA3_512_CTX ctx_512;
            SHA3_512_Init(&ctx_512);
            SHA3_512_Update(&ctx_512, (const unsigned char*)input, strlen(input));
            SHA3_512_Final(output, &ctx_512);
            break;
        default:
            printf("Unsupported block size: %zu\n", block_size);
            return;
    }
}

void print_hex(unsigned char *output, size_t len) {
    for (size_t i = 0; i < len; i++) {
        printf("%02x", output[i]);
    }
    printf("\n");
}

int main() {
    const char *input_str = "Hello, SHA-3 with block size!";
    size_t block_size = 256; // SHA3-256 as an example
    unsigned char hash_output[SHA3_512_DIGEST_LENGTH]; // The largest size is for SHA3-512

    // Perform the SHA3 hash computation
    sha3_hash(input_str, hash_output, block_size);

    // Print the result
    printf("SHA-3 hash of the input:\n");
    print_hex(hash_output, block_size / 8);  // Print the hash in hexadecimal format

    return 0;
}

