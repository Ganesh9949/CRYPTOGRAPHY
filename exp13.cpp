#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to calculate the determinant of a 2x2 matrix
int determinant(int matrix[2][2]) {
    return (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]);
}

// Function to find the modular inverse of a number
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1;
}

// Function to multiply 2x2 key matrix with a 2x1 vector
void multiply(int key[2][2], int vector[2], int result[2]) {
    result[0] = (key[0][0] * vector[0] + key[0][1] * vector[1]) % 26;
    result[1] = (key[1][0] * vector[0] + key[1][1] * vector[1]) % 26;
}

// Function to encrypt a plaintext
void encrypt(char plaintext[], int key[2][2], char ciphertext[]) {
    int vector[2], result[2];
    int len = strlen(plaintext);
    for (int i = 0; i < len; i += 2) {
        vector[0] = plaintext[i] - 'A';
        vector[1] = plaintext[i + 1] - 'A';
        multiply(key, vector, result);
        ciphertext[i] = (result[0] + 'A');
        ciphertext[i + 1] = (result[1] + 'A');
    }
    ciphertext[len] = '\0';
}

// Function to decrypt a ciphertext
void decrypt(char ciphertext[], int key[2][2], char plaintext[]) {
    int det = determinant(key);
    int detInv = modInverse(det % 26, 26);
    if (detInv == -1) {
        printf("Key matrix is not invertible.\n");
        return;
    }

    // Calculate inverse of the key matrix
    int adj[2][2] = {{key[1][1], -key[0][1]},
                     {-key[1][0], key[0][0]}};
    int keyInv[2][2];
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            keyInv[i][j] = (adj[i][j] * detInv) % 26;
            if (keyInv[i][j] < 0)
                keyInv[i][j] += 26;
        }
    }

    int vector[2], result[2];
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i += 2) {
        vector[0] = ciphertext[i] - 'A';
        vector[1] = ciphertext[i + 1] - 'A';
        multiply(keyInv, vector, result);
        plaintext[i] = (result[0] + 'A');
        plaintext[i + 1] = (result[1] + 'A');
    }
    plaintext[len] = '\0';
}

int main() {
    char plaintext[100], ciphertext[100], decryptedtext[100];
    int key[2][2] = {{5, 17}, {4, 15}}; // Example key matrix

    printf("Enter plaintext (even length, uppercase): ");
    scanf("%s", plaintext);

    // Ensure plaintext length is even
    if (strlen(plaintext) % 2 != 0) {
        printf("Plaintext must have an even length.\n");
        return 1;
    }

    encrypt(plaintext, key, ciphertext);
    printf("Encrypted text: %s\n", ciphertext);

    decrypt(ciphertext, key, decryptedtext);
    printf("Decrypted text: %s\n", decryptedtext);

    return 0;
}

