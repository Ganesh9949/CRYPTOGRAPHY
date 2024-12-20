#include <stdio.h>
#include <math.h>
#include <stdint.h>

// Function to compute modular exponentiation
uint64_t modularExponentiation(uint64_t base, uint64_t exp, uint64_t mod) {
    uint64_t result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

int main() {
    uint64_t p, g; // Public prime number (p) and primitive root (g)
    uint64_t a, b; // Private keys for Alice and Bob
    uint64_t A, B; // Public keys for Alice and Bob
    uint64_t sharedKeyAlice, sharedKeyBob;

    // Input public values p and g
    printf("Enter a prime number (p): ");
    scanf("%lu", &p);

    printf("Enter a primitive root of %lu (g): ", p);
    scanf("%lu", &g);

    // Input private keys for Alice and Bob
    printf("Enter private key for Alice: ");
    scanf("%lu", &a);

    printf("Enter private key for Bob: ");
    scanf("%lu", &b);

    // Calculate public keys
    A = modularExponentiation(g, a, p);
    B = modularExponentiation(g, b, p);

    // Display public keys
    printf("Public key for Alice (A): %lu\n", A);
    printf("Public key for Bob (B): %lu\n", B);

    // Calculate shared keys
    sharedKeyAlice = modularExponentiation(B, a, p);
    sharedKeyBob = modularExponentiation(A, b, p);

    // Display shared keys
    printf("Shared key computed by Alice: %lu\n", sharedKeyAlice);
    printf("Shared key computed by Bob: %lu\n", sharedKeyBob);

    // Verify that shared keys match
    if (sharedKeyAlice == sharedKeyBob) {
        printf("Key exchange successful! Shared secret key: %lu\n", sharedKeyAlice);
    } else {
        printf("Key exchange failed!\n");
    }

    return 0;
}
