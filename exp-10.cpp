#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// Left rotate macro
#define ROTLEFT(a, b) ((a << b) | (a >> (32 - b)))

// Initial SHA-1 hash values
uint32_t h0 = 0x67452301, h1 = 0xEFCDAB89, h2 = 0x98BADCFE, h3 = 0x10325476, h4 = 0xC3D2E1F0;

void sha1(const char *message, size_t len, uint8_t *hash) {
    uint8_t *msg = NULL;
    size_t new_len, offset;
    uint32_t w[80], a, b, c, d, e, temp;

    // Pre-processing
    new_len = len + 1;
    while (new_len % 64 != 56) new_len++; // Ensure the message length mod 512 is 448 bits (56 bytes)

    msg = (uint8_t *)calloc(new_len + 8, 1); // Allocate memory for message + padding + length
    if (!msg) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    memcpy(msg, message, len);
    msg[len] = 0x80; // Append the bit '1'

    uint64_t bit_len = (uint64_t)len * 8; // Message length in bits
    for (int i = 0; i < 8; i++)
        msg[new_len + i] = (bit_len >> (56 - i * 8)) & 0xFF; // Append message length in big-endian

    // Process each 512-bit chunk
    for (offset = 0; offset < new_len; offset += 64) {
        // Break chunk into sixteen 32-bit words (big-endian)
        for (int i = 0; i < 16; i++) {
            w[i] = (msg[offset + i * 4] << 24) | (msg[offset + i * 4 + 1] << 16) |
                   (msg[offset + i * 4 + 2] << 8) | (msg[offset + i * 4 + 3]);
        }

        // Extend the sixteen 32-bit words into eighty 32-bit words
        for (int i = 16; i < 80; i++)
            w[i] = ROTLEFT(w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16], 1);

        // Initialize working variables
        a = h0;
        b = h1;
        c = h2;
        d = h3;
        e = h4;

        // Main loop
        for (int i = 0; i < 80; i++) {
            if (i < 20)
                temp = ((b & c) | ((~b) & d)) + 0x5A827999;
            else if (i < 40)
                temp = (b ^ c ^ d) + 0x6ED9EBA1;
            else if (i < 60)
                temp = ((b & c) | (b & d) | (c & d)) + 0x8F1BBCDC;
            else
                temp = (b ^ c ^ d) + 0xCA62C1D6;

            temp += ROTLEFT(a, 5) + e + w[i];
            e = d;
            d = c;
            c = ROTLEFT(b, 30);
            b = a;
            a = temp;
        }

        // Add this chunk's hash to result
        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
        h4 += e;
    }

    free(msg); // Free allocated memory

    // Produce the final hash value (big-endian)
    hash[0] = (h0 >> 24) & 0xFF;
    hash[1] = (h0 >> 16) & 0xFF;
    hash[2] = (h0 >> 8) & 0xFF;
    hash[3] = h0 & 0xFF;

    hash[4] = (h1 >> 24) & 0xFF;
    hash[5] = (h1 >> 16) & 0xFF;
    hash[6] = (h1 >> 8) & 0xFF;
    hash[7] = h1 & 0xFF;

    hash[8] = (h2 >> 24) & 0xFF;
    hash[9] = (h2 >> 16) & 0xFF;
    hash[10] = (h2 >> 8) & 0xFF;
    hash[11] = h2 & 0xFF;

    hash[12] = (h3 >> 24) & 0xFF;
    hash[13] = (h3 >> 16) & 0xFF;
    hash[14] = (h3 >> 8) & 0xFF;
    hash[15] = h3 & 0xFF;

    hash[16] = (h4 >> 24) & 0xFF;
    hash[17] = (h4 >> 16) & 0xFF;
    hash[18] = (h4 >> 8) & 0xFF;
    hash[19] = h4 & 0xFF;
}

int main() {
    const char *message = "The quick brown fox jumps over the lazy dog";
    uint8_t hash[20];

    sha1(message, strlen(message), hash);

    printf("SHA-1 hash of '%s':\n", message);
    for (int i = 0; i < 20; i++)
        printf("%02x", hash[i]);
    printf("\n");

    return 0;
}

