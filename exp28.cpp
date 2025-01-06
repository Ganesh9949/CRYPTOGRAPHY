#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to calculate the greatest common divisor (GCD)
long gcd(long a, long b) {
    while (b != 0) {
        long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to calculate the modular inverse of e (mod phi) using the Extended Euclidean Algorithm
long mod_inverse(long e, long phi) {
    long t = 0;
    long new_t = 1;
    long r = phi;
    long new_r = e;
    
    while (new_r != 0) {
        long quotient = r / new_r;
        
        long temp_t = t;
        t = new_t;
        new_t = temp_t - quotient * new_t;
        
        long temp_r = r;
        r = new_r;
        new_r = temp_r - quotient * new_r;
    }
    
    if (r > 1) {
        printf("e is not invertible\n");
        exit(1);
    }
    
    if (t < 0) {
        t = t + phi;
    }
    
    return t;
}

// Function to perform modular exponentiation: (x^y) % p
long mod_exp(long x, long y, long p) {
    long result = 1;
    x = x % p;  // In case x >= p
    while (y > 0) {
        if (y % 2 == 1) {
            result = (result * x) % p;
        }
        y = y / 2;
        x = (x * x) % p;
    }
    return result;
}

// Function to check if a number is prime
int is_prime(long n) {
    if (n <= 1) return 0;
    for (long i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

// Function to generate RSA keys for Bob (public and private keys)
void generate_keys(long *n, long *e, long *d) {
    // Generate two distinct prime numbers (for simplicity, we pick known primes)
    long p = 61;  // A prime number
    long q = 53;  // Another prime number

    *n = p * q;  // n = p * q
    long phi = (p - 1) * (q - 1); // Euler's Totient Function: phi(n) = (p-1)(q-1)

    // Choose e such that e is coprime with phi(n) and 1 < e < phi(n)
    *e = 17;  // A common choice for e

    // Ensure e and phi(n) are coprime
    while (gcd(*e, phi) != 1) {
        (*e)++;
    }

    // Calculate d, the modular multiplicative inverse of e mod phi(n)
    *d = mod_inverse(*e, phi);
}

// Function to encrypt the message using Bob's public key (n, e)
long encrypt(long message, long e, long n) {
    return mod_exp(message, e, n);
}

// Function to decrypt the message using Bob's private key (n, d)
long decrypt(long ciphertext, long d, long n) {
    return mod_exp(ciphertext, d, n);
}

int main() {
    long n, e, d;

    // Generate RSA keys for Bob
    generate_keys(&n, &e, &d);

    // Display the keys
    printf("Bob's Public Key (n, e): (%ld, %ld)\n", n, e);
    printf("Bob's Private Key (n, d): (%ld, %ld)\n", n, d);

    // Simulating a message being sent to Bob (encrypted with Bob's public key)
    long message_from_alice = 65;  // Example plaintext message (message should be a number)
    printf("Message from Alice (plaintext): %ld\n", message_from_alice);

    // Encrypt the message using Bob's public key
    long encrypted_message = encrypt(message_from_alice, e, n);
    printf("Encrypted message (ciphertext): %ld\n", encrypted_message);

    // Now Bob decrypts the message using his private key
    long decrypted_message = decrypt(encrypted_message, d, n);
    printf("Bob's Decrypted message: %ld\n", decrypted_message);

    return 0;
}

