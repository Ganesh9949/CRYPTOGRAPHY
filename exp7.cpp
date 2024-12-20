#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

// Function to calculate the greatest common divisor
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

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
    int p, q, n, phi, e, d;
    uint64_t message, encrypted, decrypted;

    // Input two prime numbers
    printf("Enter first prime number (p): ");
    scanf("%d", &p);

    printf("Enter second prime number (q): ");
    scanf("%d", &q);

    // Calculate n and phi(n)
    n = p * q;
    phi = (p - 1) * (q - 1);

    // Choose e such that 1 < e < phi and gcd(e, phi) = 1
    for (e = 2; e < phi; e++) {
        if (gcd(e, phi) == 1) {
            break;
        }
    }

    // Calculate d such that (d * e) % phi = 1
    for (d = 1; d < phi; d++) {
        if ((d * e) % phi == 1) {
            break;
        }
    }

    printf("Public key: (e = %d, n = %d)\n", e, n);
    printf("Private key: (d = %d, n = %d)\n", d, n);

    // Input message to encrypt
    printf("Enter the message to encrypt (as an integer): ");
    scanf("%lu", &message);

    // Encrypt the message
    encrypted = modularExponentiation(message, e, n);
    printf("Encrypted message: %lu\n", encrypted);

    // Decrypt the message
    decrypted = modularExponentiation(encrypted, d, n);
    printf("Decrypted message: %lu\n", decrypted);

    return 0;
}
