#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MATRIX_SIZE 3

// Function to perform matrix multiplication and modulo operation
void encrypt(char message[], int key[MATRIX_SIZE][MATRIX_SIZE], int messageLen) {
    int i, j;
    int result[MATRIX_SIZE] = {0};

    printf("Encrypted text: ");

    for (int start = 0; start < messageLen; start += MATRIX_SIZE) {
        // Reset result matrix for this block
        for (i = 0; i < MATRIX_SIZE; i++) {
            result[i] = 0;
        }

        // Perform the matrix multiplication
        for (i = 0; i < MATRIX_SIZE; i++) {
            for (j = 0; j < MATRIX_SIZE; j++) {
                result[i] += key[i][j] * (message[start + j] - 'A');
            }
            result[i] %= 26; // Apply modulo 26
        }

        // Print the encrypted characters
        for (i = 0; i < MATRIX_SIZE; i++) {
            printf("%c", result[i] + 'A');
        }
    }

    printf("\n");
}

int main() {
    char message[100];
    int key[MATRIX_SIZE][MATRIX_SIZE];
    int messageLen;

    printf("Enter the message (only uppercase letters, max length %d): ", 100);
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0'; // Remove newline

    // Convert to uppercase and remove non-alphabet characters
    int cleanLen = 0;
    for (int i = 0; message[i] != '\0'; i++) {
        if (isalpha(message[i])) {
            message[cleanLen++] = toupper(message[i]);
        }
    }
    message[cleanLen] = '\0';
    messageLen = cleanLen;

    // Adjust message length to be a multiple of MATRIX_SIZE by padding with 'X'
    while (messageLen % MATRIX_SIZE != 0) {
        message[messageLen++] = 'X';
    }
    message[messageLen] = '\0';

    printf("Enter the %d x %d key matrix (integers 0-25):\n", MATRIX_SIZE, MATRIX_SIZE);
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            scanf("%d", &key[i][j]);
        }
    }

    encrypt(message, key, messageLen);

    return 0;
}

